// Libreria para variables y structs comunes

// Inicializa las variables antes de empezar la ejecucion
void initVars();

// Datos comunes a las dos placas sobre inhabitantes y luces (internas y externa)
struct datos_luz {
    volatile unsigned int lumenes;
    volatile unsigned int hab1, hab2, hab3;
    volatile unsigned int luz1, luz2, luz3;
    volatile unsigned int luz1_man, luz2_man, luz3_man;
};

// Variables necesarias para los mailboxes
static unsigned char mensaje_mbox_LEDs;
static unsigned char mensaje_mbox_LCD;
OStypeMsgP msg_recibido;

