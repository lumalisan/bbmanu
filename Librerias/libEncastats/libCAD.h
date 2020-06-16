
/*
 * Analog to digital converter library
 *
 * It works with the first potentiometer, which is connected to the 10-bit ADC.
 * Consequently the values that can be obtained are between 0 and 1023.
 *
 */

// Types of interaction

#define CAD_INTERACTION_BY_POLLING			0
#define CAD_INTERACTION_BY_INTERRUPT		1


// Parameters to configure ADC sample/conversion period when interaction
// is via interrupt

	// Define the two following macros as the desired
	// value pairs listed just bellow.
	// Note that by default these two macros are defined
	// so that the ADC period is 125 ms

#define ADC_PSCALER ADC_PSCALER_FOR_125ms;
#define ADC_PERIOD ADC_PERIOD_FOR_125ms;

	//  Value pair list for ADC_PSCALER and ADC_PERIOD

	#define ADC_PSCALER_FOR_500ms		0b11
	#define ADC_PERIOD_FOR_500ms		57600

	#define ADC_PSCALER_FOR_250ms		0b11
	#define ADC_PERIOD_FOR_250ms		28800

	#define ADC_PSCALER_FOR_125ms		0b11
	#define ADC_PERIOD_FOR_125ms		14400

	#define ADC_PSCALER_FOR_62_5ms		0b11
	#define ADC_PERIOD_FOR_62_5ms		7200

	#define TIMER_PSCALER_FOR_50ms		0b11
	#define TIMER_PERIOD_FOR_50ms		5760

	#define ADC_PSCALER_FOR_10ms		0b11
	#define ADC_PERIOD_FOR_10ms			1152

	#define ADC_PSCALER_FOR_1_25ms		0b11
	#define ADC_PERIOD_FOR_1_25ms		144


//////////////////////////////
// Public function prototypes
//////////////////////////////

void CADInit(unsigned char interactionType, unsigned char intPriority);

void CADStart(unsigned char interactionType);

void CADStop();

void CADRequestValue();

unsigned char CADReadyValue();

unsigned int CADGetValue();

void CADClearInt();

