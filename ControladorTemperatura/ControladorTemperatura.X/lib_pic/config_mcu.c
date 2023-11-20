
#include "config_mcu.h"

//Desarrollo de funciones
void OSCILADOR_Init(void)
{
    OSCCONbits.IRCF = 0b111; //Configura el Osc interno a 16Mhz
    OSCCONbits.SCS  = 0b10;  //Selecion el OsC interno como reloj principal del sistema
}