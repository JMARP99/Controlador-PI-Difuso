
#include "adc.h"

//Desarrollo de funciones
void ADC_Init(void)
{
    //VREF Interno
    ADCON1bits.PVCFG = 0b00; // VREF+ = VDD interno
    ADCON1bits.NVCFG = 0b00; // VREF- = VSS interno
    //Justificacion del resultado a la derecha
    ADCON2bits.ADFM = 1;
    //Configuracion de la FclockADC = 500Kz
    ADCON2bits.ADCS = 0b010; //Prescaler x32
    //Configuracion del TADQ = 4TAD = 8us 
    ADCON2bits.ACQT = 0b010;
    /*
     * Fosc = 16Mhz
     * 
     * TAD = Tclock_ADC
     * Fclock_ADC = ?
     * 
     * Configuracion con prescaler x2
     * Fclock_ADC = Fosc/2
     * Fclock_ADC = 16Mhz/2 = 8Mhz
     * Tclock_ADC(TAD) = 1/8Mhz
     * Tclock_ADC(TAD) = 0.125 us
     * 
     * Configuracion con prescaler x32 (Correcto)
     * Fclock_ADC = 16Mhz/32
     * Fclock_ADC = 500Kz
     * Tclock_ADC(TAD) = 1/500Khz
     * Tclock_ADC(TAD) = 2 us
     */
}

void ADC_Enable(void)
{
    ADCON0bits.ADON = 1;
}

void ADC_Disable(void)
{
    ADCON0bits.ADON = 0;
}

void ADC_StartConversion(void)
{
    ADCON0bits.GO_DONE = 1;
}

bool ADC_StateConversion(void)
{
    return (ADCON0bits.GO_DONE);
}

uint16_t ADC_GetConversion (uint8_t channel)
{
    uint16_t resultADC = 0;
    
    //Paso 1
    ADCON0bits.CHS = channel; //Seleccion de canal
    //Paso 2
    ADC_Enable(); //Habilitar el ADC
    ADC_StartConversion(); //Inciar conversion
    //Paso 3
    while(ADC_StateConversion() == true); //Esperar mientras se completa la conversion
    //Paso 4
    ADC_Disable();
    resultADC = (ADRESH << 8) + ADRESL;
    
    return (resultADC);
}
