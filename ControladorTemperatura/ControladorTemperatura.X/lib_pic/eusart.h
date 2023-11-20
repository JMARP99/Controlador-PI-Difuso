
#ifndef EUSART_H
#define	EUSART_H

#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 16000000UL
#endif

#include <xc.h>
#include <stdint.h>

//Prototipos de funciones
void EUSART_SerialBegin(uint32_t baudios);
void EUSART_WriteChar(char data);
void EUSART_WriteString(char *ptrString);
char EUSART_ReadChar(void);
void EUSART_RxInterruptEnable(void);
void EUSART_RxInterruptDisable(void);
void putch(char c);




#endif	/* EUSART_H */

