#include <p30f4011.h>
#include <stdio.h>

#include "delay.h"
#include "Keyblib.h"
#include "LCDlib.h"
#include "CADlib.h"

#include "TIMERlib.h"


////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////

volatile unsigned char key = 0;

double prods[12] = {
    0.5, // 0
    1.0, // 1
    2.0, // 2
    0.0, // 3
    0.0, // 4
    0.0, // 5
    0.0, // 6
    0.0, // 7
    0.0, // 8
    0.0, // 9
    0.0, // 10
    0.0 // 11
};

////////////////////////////////////////////////
// Timer 1 ISR
////////////////////////////////////////////////

void _ISR _T1Interrupt(void) {

    char buffer1[40];
    char buffer2[40];
    double weight;
    /////////

    if (CADReadyValue()) {

        // Get value from CAD and request new value
        weight = CADGetValue() * 0.004887585;
        CADRequestValue();

        // Update text at LCD
        printValue(buffer1, buffer2, weight);
    }

    IFS0bits.T1IF = 0;
}


////////////////////////////////////////////////
// ADC ISR
////////////////////////////////////////////////

void _ISR _ADCInterrupt(void) {
    char buffer1[40];
    char buffer2[40];
    double weight;

    // Get value
    weight = CADGetValue() * 0.004887585;

    printValue(buffer1, buffer2, weight);

    // Clear interrupt
    IFS0bits.ADIF = 0;
}


////////////////////////////////////////////////
// Programa principal
////////////////////////////////////////////////

int main() {

    unsigned char i;

    // Initialize keyboard
    KeybInit();
    
    // Initialize LEDs
    initLEDs();

    // Initialize LCD
    LCDInit();

    // Initialize and start CAD
    CADInit(CAD_INTERACTION_BY_INTERRUPT);
    CADStart(CAD_INTERACTION_BY_INTERRUPT);
    
    Timer1Init(TIMER_PERIOD_FOR_500ms, TIMER_PSCALER_FOR_500ms); // Timer expires every 500 ms

    while (1) {
        key = getKey();

        switch (key) {
            case 11: // Set to polling
                CADStop();
                CADInit(CAD_INTERACTION_BY_POLLING);
                CADStart(CAD_INTERACTION_BY_POLLING);
                CADRequestValue();
                Timer1ReInitialize(TIMER_PERIOD_FOR_500ms,TIMER_PSCALER_FOR_500ms);
                Timer1Start();
                onLED(1);
                break;

            case 10: // Set to interrupts
                Timer1Stop();
                CADStop();
                CADInit(CAD_INTERACTION_BY_INTERRUPT);
                CADStart(CAD_INTERACTION_BY_INTERRUPT);
                offLED(1);
                break;

            default: break;
        }
        // 300 ms delay so the keys are not oversampled
        //for (i = 0; i < 60; i++) Delay5ms();

    }
    return 0;
}

int printValue(char buffer1[40], char buffer2[40], double weight) {
    sprintf(buffer1, "Prod.%i - %.2f E/Kg", key + 1, prods[key]);
    sprintf(buffer2, "%.2f Kg %.2f E", weight, weight * prods[key]);

    //LCDClear();
    LCDMoveFirstLine();
    LCDPrint(buffer1);
    LCDMoveSecondLine();
    LCDPrint(buffer2);

    // Clear interrupt
    IFS0bits.ADIF = 0;

    return 0;
}