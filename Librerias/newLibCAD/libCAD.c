
#include "libCAD.h"
#include <p30F4011.h>

///////////////////////////////////////////////////////////////////
///////////// Privat variables /////////////////////

unsigned char currentInteractionType = CAD_INTERACTION_BY_POLLING;


///////////////////////////////////////////////////////////////////
///////////// Prototypes of private functions /////////////////////

void CADinitSimpleConfiguration(unsigned char interactionType);



///////////////////////////////////////////////////////////////////
///////////// Implementation of public functions //////////////////
///////////////////////////////////////////////////////////////////


void CADInit(unsigned char interactionType, unsigned char intPriority){

	currentInteractionType = interactionType;

	CADinitSimpleConfiguration(interactionType);

	if (interactionType == CAD_INTERACTION_BY_INTERRUPT){
		/*
			TAD = Tcy = 33.9 ns
			Duration of sampling  (clocked conversion trigger) = 31 TADs = 31 * 33.9 = 1050.9 ns
			Duration of conversion (it is irrelevant for the rate at which interrupts will be generated)
			Generate interrupt after 16 sequences of sampling/conversion
			-> generate interrupt each 16 * 1050.9 ns = 16814.4 ns = 16.8144 ms 
	
		*/
		T2CON = 0x0000; // Stop any timers operation
		T3CON = 0x0000;

		// Cambiamos para que el trigger del fin de muestreo e inicio de conversion sea manual 
		ADCON1bits.SSRC = 0b000;	//0b010; // dirigido automaticamente por 32-timer timer3/timer2 (TMR3:TMR2)

		/////////////////////////////////////////////
		// Ahora configuramos timers 3 y 2 para que realicen el trigger del fin de sampling e inicio de conversion

		///////////
		// Timer 2
		///////////

		TMR2 = 0x0000;			// Clear timer 2 timer register
		PR2 = ADC_PERIOD;		// Set timer 2 period register to LSW of 32-bit value to count X ms

		// bit 15 TON (Timer on bit) = 0, Stops 32-bit TMR3:TMR2 timer pair (T32=1)
		// bit 14 unimplemented
		// bit 13 TSIDL = 0, continue timer operation in idle mode
		// bits <12:7> unimplemented
		// bit 6 TGATE (Timer Gated Time Accumulation Enable bit) = 0, disabled
		// bits <5:4> TCKPS (Timer Input Clock Prescale Select bits) = 11, 1:256 prescale value <-- Revisar
		// bit 3 T32 (32-bit Timer Mode Select bits) = 1, TMR3 and TMR2 form a 32-bit timer
		// bit 2 Unimplemented
		// bit 1 TCS (Timer Clock Source Select bit) = 0, Internal clock (FOSC/4)
		// bit 0 unimplemented 
		// valor resultante registro = 0 0 0 000000 0 11 1 0 0 0

		//T2CON = 0b0000000000111000;
		T2CONbits.T32 = 1;		// Set 32-bit timer mode
		T2CONbits.TCKPS = ADC_PSCALER;	// Set timer 2 PSCALER to LSW of 32-bit value to count X ms
										// Note that we set TCKPS after writting in TMR2, since writin TMR2 may reset TCKPS)

		///////////
		// Timer 3
		///////////

		TMR3 = 0x0000;
		PR3 = 0;	// Set timer 3 period register to MSW of 32-bit value to count

		// bit 15 TON (Timer on bit) = 0, Stops 16-bit, aunque es irrelevante por que T2CON.T32 = 1 (32-bit timer mode)
		// bit 14 unimplemented
		// bit 13 TSIDL = 0, continue timer operation in idle mode
		// bits <12:7> unimplemented
		// bit 6 TAGE (Timer Gated Time Accumulation Enable bit) = 0, disabled
		// bits <5:4> TCKPS (Timer Input Clock Prescale Select bits) = 00 <-- es irrelevante porque T2CON.T32 = 1 (32-bit timer mode)
		// bits <3:2> Unimplemented
		// bit 1 TCS (Timer Clock Source Select bit) = 0, Internal clock (FOSC/4), aunque es irrelevante por que T2CON.T32 = 1 (32-bit timer mode)
		// bit 0 unimplemented 

		// valor resultante registro = 0 0 0 000000 0 00 0 0 0 


		// Configurar interrupcion 32-bit timer (timer 3 genera interrupcion)
		IPC1bits.T3IP = intPriority;	// Set timer interrupt priority = 5 (7 highest)
		IFS0bits.T3IF = 0;  		// Clear timer 3 interrupt
 		IEC0bits.T3IE = 1;  	// Enable timer 3 interrupt


		/////////////////////////////////////////////

		// Set up interrupts for CAD
		IPC2bits.ADIP = intPriority;	// Set ADC ISR priority
		IFS0bits.ADIF = 0; 		// Clear ADC interrupt
		IEC0bits.ADIE = 1; 		// Enable ADC interrupt
	}
	else {
		// Disable and clear interrupts for CAD
		IEC0bits.ADIE = 0; // Disable interrupt
		IFS0bits.ADIF = 0; // Clear ADC interrupt
		IPC2bits.ADIP = 0; // Reset ADC ISR priority
	}
}


void CADStart(unsigned char interactionType){


	if (interactionType == CAD_INTERACTION_BY_INTERRUPT){
		// Timer triggers end sample & start conversion by hardware
		/*
		ADCON1bits.SSRC = 0b010;
		ADCSSL = 0;
		ADCON3 = 0x0000;	//0b0000000100000010;	// 0x0000;
		ADCON2 = 0x0004;	//0x0000;	//	0x0004;
		PR2 = 0x3FFF; 
		T2CON = 0x8010;
 	 	ADCON1bits.ADON = 1; // Enable CAD. Must be done AFTER configuration
		ADCON1bits.ASAM = 1; // Habilitar inicio de muestreo automatico;
		*/

		// Timer ISR is used to trigger end sample & start conversion by software
		
		ADCON1bits.ADON = 1; // Enable CAD. Must be done AFTER configuration
		ADCON1bits.ASAM = 1; // Habilitar inicio de muestreo automatico;
		T2CONbits.TON = 1; // Start TMR3:TMR2 32-bit timer by starting T2 timer;
		
	}
	else
	{
		ADCON1bits.ADON = 1; // Enable CAD. Must be done AFTER configuration
	}
}



void CADStop(){
	if (currentInteractionType == CAD_INTERACTION_BY_INTERRUPT)
	{
		T2CONbits.TON = 0; // Stop TMR3:TMR2 32-bit timer by starting T2 timer
		T2CONbits.TCKPS = ADC_PSCALER;	// Set again timer 2 PSCALER to LSW of 32-bit value to count X ms (it is reset when TON is cleared)
	}
   	ADCON1bits.ADON = 0;
}


void CADRequestValue(){
	   ADCON1bits.SAMP = 1;
}


unsigned char CADReadyValue(){

    return ADCON1bits.DONE;
}


unsigned int CADGetValue(){

    return ADCBUF0;
}


void CADClearInt()
{
	IFS0bits.ADIF = 0;
}


///////////////////////////////////////////////////////////////////
///////////// Implementation of private functions /////////////////
///////////////////////////////////////////////////////////////////



////////////////////////////////////////////////
// Timer 3 ISR - necessary to support ADC periodic triggering
////////////////////////////////////////////////

void _ISR _T3Interrupt(void){
	ADCON1bits.SAMP = 0; // Ordenamos fin de muestreo e inicio de conversion
    IFS0bits.T3IF = 0;	// Limpiamos flag interrupcion
}




void CADinitSimpleConfiguration(unsigned char interactionType){

	// Set PIN B7 (AN7) as input
	TRISBbits.TRISB7 = 1;

	///////////////////////////////////
	// AD PORT CONFIGURATION REGISTER
	///////////////////////////////////
	// (1 paso)
	// Configurar los pines analógicos como entradas analógicas o como I/O digitales
	// En este caso solo se va a utilizar el pin AN7 como entrada analógica
	// Por tanto, solo configuramos AN7 como dicho tipo de entrada
	// 111 111 0111 1111
	ADPCFG = 0xFF7F;	 // all PORTB = Digital; RB7/AN7 = analog


	///////////////////////////////////
	// AD CONFIGURATION REGISTER 1
	///////////////////////////////////

	// bit 15 ADON = 0, AD converter off
	// bit 14 unimplemented
	// bit 13 ADSIDL = 0, continue operation in idle mode
	// bit 12 unimplemented
	// bit 11 unimplemented
	// bit 10 unimplemented

	// (paso 8)
	// bits <9:8> FORM = 00, data output format = (unsigned) integer

	// (paso 7)
	// bits <7:5> SSRC (conversion trigger source)

	//	= 111, Internal counter ends sampling and starts conversion (auto convert) <-- para polling, pero usar 010 para interrupt!
	//	= 000, End of sampling and start of conversion is triggered by setting SAMP=0 (manual convert)
	//	= 010, End of sampling and start of conversion is triggered when match between the 32-bit timer TMR3/TMR2 and the 32-bit Combined Period register PR3/PR2 (timer convert)

	// bit 4 unimplemented

	// paso(5)
	// bit 3 SIMSAM (Simultaneous Sample Select bit, only applicable when CHPS = 01 or 1x)
	//	= 0, samplea multiples canales S/H de forma individual secuencialmente <- da igual el valor porque CHPS = 00

	// (paso 7)
	// bit 2 ASAM (A/D sample autostart) = 0, no automatic start of sampling. SAMP = 1 inicia el muestreo <-- configurado para polling, cambiar para interrupt
	// bit 1 SAMP = 0, holding (not sampling)
	// bit 0 DONE = 0, es un bit de status, esta escritura se descarta

	// valor resultante registro = 0 0 0 000 00 111 0 0 0 0 0

	ADCON1 = 0x0000;
	ADCON1 = 0b0000000011100000;


	///////////////////////////////////
	// AD CONFIGURATION REGISTER 2
	///////////////////////////////////

	// (2 paso)
	// bits <15:13> VCFG (voltage reference configuration pins) ->  = 000, ADVRefH = AVdd, ADVRefL = AVss
	// bit 12 reserved
	// bit 11 unimplemented
	// bit 10 CSCNA (Scan Input Selections for CH0+)
	//	Used to scan across a number (SMPI) of selected (ADCSSL) analog inputs of the MUX A group of CH0 channel
	//	SMPI bit specifies number of scans per interrupt
	//	ADCSSL register specifies the inputs to be scanned
	//	When CSCNA is set, the CH0SA<3:0> bits (which are used to select just one input for CH0 MUX A) are ignored
	//
	//	= 0, do not alternately scan inputs for CH0

	// (4 paso)	
	// bits <9:8> CHPS (Selects Channels Utilized bits) = 00, use CH0

	// bit 7 BUFS (buffer fill status, only valid if BUFM = 1) = 0
	// bit 6 unimplemented

	// (paso 9)
	// bits <5:2> SMPI (sample/convert sequences per interrupt) = 0000, interrupt at each sample/covert sequence <-- CAMBIAR para reducir overhead

	// bit 1 BUFM (buffer mode) = 0, one 16-words buffer: ADCBUF(15...0)
	// bits 0 ALTS (alternate input sample MUXs) = 0, use always MUXA input multiplexer

	// valor resultante registro = 000 0 0 0 00 0 0 0000 0 0

	ADCON2 = 0x0000;



	///////////////////////////////////
	// AD CONFIGURATION REGISTER 3
	///////////////////////////////////

	// bits <15:13> unimplemented

	// (paso 7)
	// bits <12:8> SAMC (autosample time bits)
	//	Applicable if SSRC=111 (auto conversion trigger)
	//	SAMC must be >= 1 if using only 1 S/H channel or simultaneous sampling

	//	= 00001, 1 TAD <- optimizado para polling, aumentar para reducir overhead para interrupts si se utiliza el modo autoconvert (SRC=111).

	// bit 7 ADRC = 0, AD conversion clock derived from system clock

	// bit 6 unimplemented	

	// (3 paso)
	// bits <5:0> ADCS (AD conversion clock select bits)

	//	= 000010, TAD = (TCY/2)*(ADCS + 1) = 3TCY/2 <- optimizado para polling, aumentar para reducir overhead para interrupts si se utiliza el modo autoconvert (SRC=111).

	// valor resultante registro = 000 00001 0 0 000010

	//ADCON3 = 0b0000000100000010;
	ADCON3 = 0b0000000100000111;

	///////////////////////////////////
	// ADCSSL: A/D Input Scan Select Register
	///////////////////////////////////
	// (5 paso)
	// Seleccionar los pines de entrada a scanear
	// En este caso solo se va a utilizar el pin AN7 como entrada analógica
	// Por tanto, solo sleccionamos AN7 <-- de todas formas como no vamos a hacer scanning secuencial, da igual el valor
	// 0000 0000 1000 0000
	ADCSSL = 0b0000000010000000;


	///////////////////////////////////
	// AD INPUT SELECT REGISTER
	///////////////////////////////////
	// (paso 6)
	// Especifica como se conectan los pines de entrada
	// a cada canal H/S
	// ADCHS<15:8> determine the settings for MUX B
	// ADCHS<7:0> determine the settings for MUX A.
	// Both sets of control bits function identically.
	// En este caso solo vamos a utilizar el MUX A de CH0
	// Por tanto, hacemos:
	//
	//	bits <7:6> CH123NA (Channel 1, 2, 3 Negative Input Select for MUX A Multiplexer Setting bits)
	//		= 00 = Negative input para CH1, CH2 y CH3 = VREF-
	//	bit 5 CH123SA Channel 1, 2, 3 Positive Input Select for MUX A Multiplexer Setting bit)
	//		= 0 = Positive input para CH1, CH2 y CH3 = AN0, AN1 y AN2 respectivamente
	//	bit 4 CH0NA (Channel 0 Negative Input Select for MUX A Multiplexer Setting bit)
	//		= 0 = Negative input para CH0 = VREF-
	//	bits <3:0> CH0SA (Channel 0 Positive Input Select for MUX A Multiplexer Setting bits)
	//		= 0111 = Positive input para CH0 = AN7
	//
	//	Los bits <15:8> son análogos pero para configurar el MUX B de cada canal.
	//	Da igual su valor, porque no usamos MUX B: los ponemos todos a '0'
	//
	// valor resultante registro = 0000 0000 0000 0111

	ADCHS = 0x0007;


}


