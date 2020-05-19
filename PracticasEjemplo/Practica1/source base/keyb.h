#define BLOQUEANTE 1
#define NO_BLOQUEANTE 0
#define TECLA_NO_PULSADA 255

// Inicializar teclado
void initKeyb();

// Determinar la tecla que se ha pulsado
unsigned char getKey(unsigned char block);
