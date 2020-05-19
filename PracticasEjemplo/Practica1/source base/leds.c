

#include <p30f4011.h>
#include "leds.h"


// El registro TRIS por cada puerto sirve para configurar si es I/O
#define LED0_TRIS	TRISEbits.TRISE0
#define LED1_TRIS	TRISEbits.TRISE1
#define LED2_TRIS	TRISEbits.TRISE2
#define LED3_TRIS	TRISEbits.TRISE3
#define LED4_TRIS	TRISEbits.TRISE4
#define LED5_TRIS	TRISEbits.TRISE5

// El registro LAT por cada puerto es para escribir un valor
#define LED0		LATEbits.LATE0
#define LED1		LATEbits.LATE1
#define LED2		LATEbits.LATE2
#define LED3		LATEbits.LATE3
#define LED4		LATEbits.LATE4
#define LED5		LATEbits.LATE5

// El registro PORT por cada puerto es para leer un valor


void initLEDs()
{
	LED0_TRIS = 0;	// Configuramos el pin 0 del puerto E (LEDs) como salida
	LED1_TRIS = 0;
	LED2_TRIS = 0;
	LED3_TRIS = 0;
	LED4_TRIS = 0;
	LED5_TRIS = 0;
}


void onLED(unsigned char numLED)
{
	switch (numLED)
	{
		case 0 : LED0 = 1; break;
		case 1 : LED1 = 1; break;
		case 2 : LED2 = 1; break;
		case 3 : LED3 = 1; break;
		case 4 : LED4 = 1; break;
		case 5 : LED5 = 1; break;
		default:;
	}
}


void offLED(unsigned char numLED)
{
	switch (numLED)
	{
		case 0 : LED0 = 0; break;
		case 1 : LED1 = 0; break;
		case 2 : LED2 = 0; break;
		case 3 : LED3 = 0; break;
		case 4 : LED4 = 0; break;
		case 5 : LED5 = 0; break;
		default:;
	}
}
