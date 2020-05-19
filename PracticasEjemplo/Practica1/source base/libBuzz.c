#include <p30f4011.h>
#include "libBuzz.h"
#include "delay.h"
#include <math.h>

float round(float a) {
    float aux = a - (int) a;
    if (aux < 0.5f) return (float) (int)a;
    else return (float) ((int)a + 1);
}

// Inicializar buzzer
void initBuzzer() {
	// Set el TRISB como salida
	BUZZ_TRIS = 0;
}

// Toca una frecuencia
void playBuzzer(unsigned int freq, unsigned int duration) {
	// Crear vibración con frecuencia especificada
	// Emplear Delay3Tcy(), que permite tener un delay de 3 ciclos (407 ns)
	
	float periodo = (1/(float)freq)*1000000; // en us
    float numPeriodos = round((((float)duration * 1000)/periodo));
	float numSemiperiodos = round(numPeriodos * 2);
    

	printf("Frecuencia %d, Duration %d, Periodo %f\n", freq, duration, periodo);
    //printf("numPeriodos %f, numSemiperiodos %f\n", numPeriodos, numSemiperiodos);
    //printf("Despues de casting: %d, %d\n", (unsigned int) numPeriodos, (unsigned int) numSemiperiodos);
    //printf("Milisegundos calculados: %d\n", (unsigned int)(numPeriodos*periodo));
	
    unsigned int i = 0; unsigned int j = 0;
    
	for (i=0; i<(unsigned int) numSemiperiodos; i++) {
		BUZZ = 1;
		for (j=0; j<(unsigned int)((periodo/2)/100); j++) { // * 100 para compensar el hecho de que
            Delay10us();                                       // el Delay es de 10 us
        }
		BUZZ = 0;
        for (j=0; j<(unsigned int)((periodo/2)/100); j++) { // * 100 para compensar el hecho de que
            Delay10us();                                       // el Delay es de 10 us
        }
	}
}

// Toca una nota
// DO = 1, RE = 3, MI = 5, FA = 6, SOL = 8, LA = 10, SI = 12
void playNote(unsigned char note, unsigned char octave, unsigned int duration) {

	if (note == -1) {
		playBuzzer(0, duration);
	} else {

		float aux1 = (float) (note - 10 + (octave * 12));
	    //float aux2 = (float) ((12 + octave - 4));
	    //float aux = aux1/aux2;
		//unsigned int frecuencia = (unsigned int)(440 * pow(2.0, aux));
		float aux = aux1/12;
		unsigned int frecuencia = (unsigned int)(440 * pow(2.0, aux));
	    //printf("Aux1: %f, Aux2: %f\n", aux1, aux2);
	    //printf("Aux: %f, frecuencia: %d\n", aux, frecuencia);
		playBuzzer(frecuencia, duration);
	}
}
