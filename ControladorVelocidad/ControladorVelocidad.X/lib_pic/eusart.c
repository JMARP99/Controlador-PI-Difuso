
#include "eusart.h"

//Desarrollo de funciones
void EUSART_SerialBegin(uint32_t baudios)
{
    uint16_t n = 0;
    
    //Configuracion de pines Tx (RC6) y Rx (RC7)
    ANSELCbits.ANSC6 = 0;
    TRISCbits.TRISC6 = 0; // Tx (RC6) -> Salida digital
    ANSELCbits.ANSC7 = 0;
    TRISCbits.TRISC7 = 1; // Rx (RC7) -> Entrada digital
    
    //configuracion de la transmision serial
    TXSTA1 = 0b00100100; 
    //configuracion de la recepcion serial
    RCSTA1 = 0b10010000; 
    //configuracion de alta velocidad
    BAUDCON1 = 0b00001000; 
    
    //Calcular el baud rate
    n = (uint16_t)(((_XTAL_FREQ/baudios)/4UL)-1UL);
    //Cargar el baud rate
    SPBRG1 = (uint8_t)n;
    SPBRGH1 = (uint8_t)(n >> 8);
}

void EUSART_WriteChar(char data)
{
    while(TXSTA1bits.TRMT == 0); //Esperar que se transmitan todos los bits
    TXREG1 = data;
}

void EUSART_WriteString(char *ptrString)
{
    while(*ptrString != '\0')
    {
        EUSART_WriteChar(*ptrString);
        ptrString++;
    }
}

char EUSART_ReadChar(void)
{
    char datoError;
    
    while(PIR1bits.RCIF == 0); //Esperar que se reciba un byte
    
    //Evalua el error
    if(RCSTA1bits.FERR == 1 || RCSTA1bits.OERR == 1)
    {
        datoError = RCREG1; //Leer el error
        (void)datoError;
        RCSTA1bits.CREN = 0;
        asm("nop"); //Tiempo de 1 ciclo maquina
        RCSTA1bits.CREN = 1;
    }
    
    return (RCREG1);
}

void EUSART_RxInterruptEnable(void)
{
    PIE1bits.RCIE = 1; //Habilitar la interrupcion por Rx
}

void EUSART_RxInterruptDisable(void)
{
    PIE1bits.RCIE = 0; //Desabilitar la interrupcion por Rx
}

void putch(char c)
{
    while(TXSTA1bits.TRMT == 0); //Esperar que se transmitan todos los bits
    TXREG1 = c;
}
