
#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define ADC_VREF        5.0f
#define ADC_RESOLUCION  1023.0f

#define ADC_AN0   0b00000
#define ADC_AN1   0b00001
#define ADC_AN2   0b00010
#define ADC_AN3   0b00011
#define ADC_AN4   0b00100
#define ADC_AN5   0b00101
#define ADC_AN6   0b00110
#define ADC_AN7   0b00111
#define ADC_AN8   0b01000
#define ADC_AN9   0b01001
#define ADC_AN10  0b01010
#define ADC_AN11  0b01011
#define ADC_AN12  0b01100

//Prototipos de funciones
void ADC_Init(void);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_StartConversion(void);
bool ADC_StateConversion(void);
uint16_t ADC_GetConversion (uint8_t channel);


#endif	/* ADC_H */

