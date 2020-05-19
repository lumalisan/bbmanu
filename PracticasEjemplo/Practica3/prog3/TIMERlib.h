/*
 * Timer library
 *
 * Timer is fed with system clock which runs at 29.491.200 Hz (almost 30 MHz).
 * The timer clock can be slowed by means of the prescaler.
 * 
 */

//////////////////////////////////////////////////////////////////////////////////
// Calculo del valor del preescaler y del periodo para diferentes velocidades
//////////////////////////////////////////////////////////////////////////////////

#define TIMER_PSCALER_1_1   0b00
#define TIMER_PSCALER_1_8   0b01
#define TIMER_PSCALER_1_64  0b10
#define TIMER_PSCALER_1_256 0b11


// La frecuencia del ciclo de instrucción (FCY) es 29.491.200 Hz
// Queremos que el Timer cuente 500ms
//
// Con pre-escalador a 1:1
// FclkTimer = 29.491.200 Hz -> TclkTimer = 33,9084 ns
// TclkTimer * numeroTicksAContar = 500 ms -> numeroTicksAContar = 14.745.608,76
// Como el timer es de 16 bits, solo puede contar hasta 65535
// Por tanto, numeroTicksAContar no cabría en el registro
// del timer que se utiliza para programar su periodo
//
// Configuración para contar 500 ms
//
//		¿Cual crees que debería ser el valor del Pre-escalador para que
//		el numeroTicksAContar sea un numero lo suficientemente bajo como para
//		poder programar el timer con el?
//		Una vez hayas decidido que valor de Pre-escalador necesitas
//			¿Cual es el valor de TclkTimer en milisegundos (ms)?
//			¿Cual es el numeroTicksAContar con el que se debe programar el timer?
//
#define TIMER_PSCALER_FOR_500ms		TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_500ms		57600



#define TIMER_PSCALER_FOR_250ms		TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_250ms		28800

#define TIMER_PSCALER_FOR_125ms		TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_125ms		14400

#define TIMER_PSCALER_FOR_62_5ms	TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_62_5ms		7200

#define TIMER_PSCALER_FOR_1_25ms	TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_1_25ms		144

#define TIMER_PSCALER_FOR_10ms		TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_10ms		1152

#define TIMER_PSCALER_FOR_50ms		TIMER_PSCALER_1_256
#define TIMER_PERIOD_FOR_50ms		5760



void Timer1Init(unsigned int period, unsigned char pscaler);

void Timer1Start();
void Timer1Stop();

void Timer1ReInitialize(unsigned int period, unsigned char pscaler);
