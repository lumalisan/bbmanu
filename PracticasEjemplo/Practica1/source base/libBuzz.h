// Registros de I/O para el zumbador

#define BUZZ_TRIS 	TRISBbits.TRISB7
#define BUZZ		LATBbits.LATB7

// Implementación chapuza de round()
float round(float a);

// Inicializar buzzer
void initBuzzer();

// Toca una frecuencia
void playBuzzer(unsigned int freq, unsigned int duration);

// Toca una nota
void playNote(unsigned char note, unsigned char octave, unsigned int duration);
