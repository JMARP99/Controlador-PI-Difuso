
#define _XTAL_FREQ 16000000UL
#include "lib_pic/config_mcu.h"
#include "lib_pic/lcd.h"
#include "lib_pic/keypad_4x4.h"
#include "lib_pic/eusart.h"
#include "lib_pic/Control_velocidad_difuso.h"

//Definir estado de la aplicacion
#define ESTADO_INICIAL               0
#define ESTADO_REINICIAR_TIMER_0     1
#define ESTADO_SELECCION_REFERENCIA  2
#define ESTADO_ADQUISICION           3
#define ESTADO_CONTROL_DIFUSO        4
#define ESTADO_ENVIAR_DATOS_LCD      5
#define ESTADO_ENVIAR_DATOS_UART     6

//Declarar la funcion
void Hardware_Init (void);
void LCD_imprimir_Datos (void);
void TIMER1_Stop(void);
void TIMER1_Start(void);
//Variables de estado
uint8_t APPState;

//Variables
volatile bool  flagTimer0 = false;
volatile uint16_t RPM=0;
volatile uint16_t tiempo=0;
char   SP[20];
char   strsetpoint[20], strRPM[20], strpwm[20],strtiempo[20];
float  setpoint , error = 0.0, error_ = 0.0, salida = 0.0, salida_ = 0.0;
float  Cambio_error = 0.0;
uint8_t contador = 0;

//Teclado
char tecla;
uint8_t indice = 0;
uint8_t columna = 11;

//Tiempo de muestreo
//float Ts = 1.0;

//Constante
//Mientras mas rapido sea el tiempo de establecimiento, disminuir el valor de la constante
//Para evitar sobre-impulsos en el sistema

//Recomendacion, que la constante sea como maximo el 10% del valor maximo que puede tomar el PWM
//En este caso 249 (24.9)

float  constante=23.5;


//Salida sistema
float   salida_sistema = 0.0;
    
int main (void)
{
    //Configuracion del hardware
    Hardware_Init();
    
    //Imprimir datos en LCD
    LCD_imprimir_Datos();
    
    //Inicializar la variable de estado
    APPState = ESTADO_INICIAL;
    
    while(1)
    {   
        switch(APPState)
        {
            case ESTADO_INICIAL:
                
                //Limpiar LCD
                Lcd_Clear();
                
                //Imprimir en LCD
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Iniciando Sistema");
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Espere 3 segundos");
                __delay_ms(1000);
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Espere 2 segundos");
                __delay_ms(1000);
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Espere 1 segundo");
                __delay_ms(1000);
                
                //Limpiar LCD
                Lcd_Clear();
                
                //Cambio de estado
                APPState = ESTADO_REINICIAR_TIMER_0;
                
            break;
            
            //****************************************
            case ESTADO_REINICIAR_TIMER_0:
                //Deshabilitar el Timer0
                T0CONbits.TMR0ON  = 0;        //Timer0 off
                
                //Reiniciar el Timer0
                TMR0 = 0;
                
                //Reiniciar contador del tiempo
                tiempo = 0;
                
                //Cambio de estado
                APPState = ESTADO_SELECCION_REFERENCIA;
                
            break;
            
            //****************************************    
            case ESTADO_SELECCION_REFERENCIA:
                //Imprimir en LCD
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Elegir referencia");
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Rango [0-500]");
                
                Lcd_Set_Cursor(3,1);
                Lcd_Write_String("SetPoint: ");
                
                Lcd_Set_Cursor(4,1);
                Lcd_Write_String("Iniciar control (*)");
                
                tecla = Key_Read(); //Leer teclado
                
                if(tecla != '\0')
                {
                    if (tecla != '*')
                    {
                        //Establecer SetPoint
                        Lcd_Set_Cursor(3,columna);
                        Lcd_Write_Char(tecla);
                        SP[indice] = tecla;
                        indice++;
                        columna ++;
                        
                        //Para limitar a 3 digitos
                        //y empezar denuevo
                        
                        if (columna>13)
                        {
                            SP[indice] = '\0';
                            
                            //Reinicio a la posicion inicial 
                            indice = 0;
                            columna = 11;
                        }
                    }
                    else if (tecla == '*')
                    {
                        
                        //Reiniciar la posicion de la pantalla para la siguiente vez
                        //que se introduzca el SP
                        indice = 0;
                        columna = 11;
                            
                        //Limpiar LCD
                        Lcd_Clear();
                        
                        //SetPoint
                        //Convertir char a numero entero
                        setpoint = (atol(SP));
                        
                        //Limpiar SP
                            SP[0] = '\0';
                            SP[1] = '\0';
                            SP[2] = '\0';
                            
                        if(setpoint > 500)
                        {
                            //Limpiar LCD
                            Lcd_Clear();
                            
                            //Imprimir mensaje
                            Lcd_Set_Cursor(1,1);
                            Lcd_Write_String("  Referencia fuera");

                            Lcd_Set_Cursor(2,1);
                            Lcd_Write_String("  del Rango [0-500]");

                            Lcd_Set_Cursor(3,1);
                            Lcd_Write_String("      Volver a");
                            
                            Lcd_Set_Cursor(4,1);
                            Lcd_Write_String("  Elegir Referencia");
                            
                            //Esperar 5 segundos
                            __delay_ms(3000);
                            
                            //Limpiar LCD
                            Lcd_Clear();
                            
                            //Cambio de estado
                            APPState = ESTADO_SELECCION_REFERENCIA;
                        }
                        else
                        {
                            //Limpiar LCD
                            Lcd_Clear();
                            //Habilitar el Timer0
                            T0CONbits.TMR0ON  = 1;        //Timer0 on
                        
                            //Cambio de estado
                            APPState = ESTADO_ADQUISICION;
                        }
                    }                   
                }
                
            break;
            
            //****************************************
                
            case ESTADO_ADQUISICION:

                if(flagTimer0 == true)
                {
                    flagTimer0 = false;
                    
                    //Cambio de estado
                    APPState = ESTADO_CONTROL_DIFUSO;
                }
                else if(flagTimer0 == false)
                {
                    //Cambio de estado 
                    APPState = ESTADO_ENVIAR_DATOS_LCD;
                }
                
            break;
            
            //*****************************************

            case ESTADO_CONTROL_DIFUSO:
                //Para calcular el error y cambio de error, es necesario dividir
                //la operacion entre el tiempo de la muestra, pero como Ts=1
               //Entonces se descarta el Ts
                
                
                //Calcular error
                error = setpoint - RPM;

                //Saturar error con universo de discurso de <-120,120>
                if(error > 119.9)
                {
                    error = 119.9;
                }
                else if(error < -119.9)
                {
                    error = -119.9;
                }

                //Calcular Cambio del error
                
                Cambio_error = (error - error_);

                //Calcular Cambio error con universo de discurso de <-8,8>
                if(Cambio_error > 7.999999)
                {
                    Cambio_error = 7.999999;
                }
                else if(Cambio_error < -7.999999)
                {
                    Cambio_error = -7.999999;
                }

                //Controlador difuso
                Control_velocidad_difusoInferenceEngine(error,Cambio_error,&salida);

                //Integral Salida del sistema
                salida_sistema = salida*constante + salida_;

                //Saturar salida del sistema [0,249]
                if(salida_sistema > 249.0)
                {
                    salida_sistema = 249.0;
                }
                else if(salida_sistema < 0.0)
                {
                    salida_sistema = 0.0;
                }
                
                //PWM
                CCPR2 = salida_sistema;

                //Guardar error
                error_ = error;

                //Guardar salida del sistema
                salida_ = salida_sistema;
                
                //Cambio_de estado
                APPState = ESTADO_ENVIAR_DATOS_UART;
                    
            break;
            //**********************************************************
                    
            case ESTADO_ENVIAR_DATOS_LCD:
                 
                
                //Imprimir datos
                LCD_imprimir_Datos();
                __delay_ms(100);
                
                tecla = Key_Read(); //Leer teclado
                
                if(tecla != '\0')
                {
                    if (tecla == '*')
                    {
                        //Limpiar LCD
                        Lcd_Clear();
                        
                        //Cambio de estado
                        APPState = ESTADO_REINICIAR_TIMER_0;
                    }
                }
                else
                {
                //Cambio de estado
                APPState = ESTADO_ADQUISICION;
                }
            break;
            
            //**********************************************************
            
            case ESTADO_ENVIAR_DATOS_UART:
                //Tomar muestras
               
                //Mandar por UART           
                sprintf(strRPM,   "%01u,",RPM);
                sprintf(strpwm,   "%01.02f,",salida_sistema);
                sprintf(strtiempo,"%01u\r\n",tiempo);

                EUSART_WriteString(strRPM);
                EUSART_WriteString(strpwm);
                EUSART_WriteString(strtiempo);
                
                //Cambio de estado
                APPState = ESTADO_ADQUISICION;           
            break;
        }
    }
}

//Rutinas de interrupcion
void __interrupt (high_priority) InterruptHighPriority (void)
{
    //Consultar por la interrupcion de desbordamiento en Timer0
    //Si se encuentra habilitado y se prende la bandera
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {    
        //Recargar el Timer0 para contar 1seg nuevamente
        TMR0 = 34286;
        
        //Ejecutar la tarea
        flagTimer0 = true;
        
        //El encoder da 20 pulsos por 1 giro
        //RPM = TMR1*60/20 (pero si se simplifica)
        /*Tener en cuenta que si se emplea el Timer1 como contador
          entonces como el valor maximo del timmer1 a 16 bits es de 65535,
          con un encoder de 20 pulsos de resolucion   
        */
        
        //Apagar el timer1 para realizar la lectura de su valor
        TIMER1_Stop();       //Timer1 off
        //Aun asi el valor maximo de las RPM debe ser como maximo 65535 para evitar errores en 
        
        //la lectura
        RPM = TMR1;
        
        //Contador del tiempo por actual por muestra
        tiempo++;
        
        //Reiniciar Timer1 para que cuando se encienda el Timer1, empieze la cuenta desde 0
        TMR1 = 0; 
        
        TIMER1_Start();       //Timer1 on
        
        //Apagar la bandera de interrupcion del Timer0 (se debe apagar manualmente por codigo)
        INTCONbits.TMR0IF = 0;
    }
}

//Desarrollo de funciones

//Configuracion de los puertos
void PORT_Init(void)
{
    //Puerto A
    ANSELAbits.ANSA0 = 1; //Pin analogico
    TRISAbits.TRISA0 = 1; //Entrada
    
    //Puerto B
    ANSELB = 0x00;        //Puerto B como digital
    
    //Habilitar Pull-up
    INTCON2bits.RBPU = 0;
    
    //Pull-up en los pines empleados como columna
    WPUBbits.WPUB4 = 1;
    WPUBbits.WPUB5 = 1;
    WPUBbits.WPUB6 = 1;
    WPUBbits.WPUB7 = 1;
   
    //Config Puerto D
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
    
    //Puerto C
    TRISCbits.TRISC0 = 1;   //PIN RC0 COMO ENTRADA
    TRISCbits.TRISC1 = 0;   //PIN RC1 COMO SALIDA
    
    //Config Puerto D
    ANSELD = 0x00;    
}

//Configuracion del TIMER1 para activarse cada 1000ms
void TIMER0_ModoTemporizador_Init (void)
{
    //Inicio el TMR0 apagado
    T0CONbits.TMR0ON  = 0;       //Timer0 off
    T0CONbits.T0CS    = 0;       //Timer0 modo Temporizador, usar el ciclo maquina (Fosc/4)
    T0CONbits.PSA     = 0;       //Habilitar el prescaler   
    T0CONbits.T0PS    = 0b110;   //Prescaler 1:128
    T0CONbits.T08BIT  = 0;       //Timer0 a 16 bits
    
    //Resetear el Timer0
    TMR0=0;
    
    //Carga Inicial
    TMR0= 34286;                 // para 1000ms
    
    //Permanecer deshabilitado el Timer0
    T0CONbits.TMR0ON  = 0;        //Timer0 off
}

//Configuracion de las interrupciones
void TIMER0_Interrupt_Init (void)
{
    INTCONbits.TMR0IE  = 1;       //Habilitiar interrupcion por desbordamiento del Timer0
    INTCONbits.TMR0IF  = 0;       //Iniciar con la bandera de la interrupcion Apagada
    INTCON2bits.TMR0IP = 1;       //Interrupcion de Alta Prioridad
}

void INTERRUPT_Init (void)
{
    //Habilitar niveles de prioridad para las interrupciones
    RCONbits.IPEN      = 1;
    //Habilitar interrupciones de alta prioridad
    INTCONbits.GIEH    = 1;
    //Habilitar interrupciones de baja prioridad
    INTCONbits.GIEL    = 1;
}

void TIMER1_ModoContador_Init  (void)
{
    //Inicio el TMR1 apagado
    T1CONbits.TMR1ON  = 0;       //Timer1 off
    T1CONbits.SOSCEN  = 0;       //Oscilador secundario desactivado
    T1CONbits.TMR1CS  = 10;      //Leer pin externo (si SOSCEN = 0)
    T1CONbits.T1CKPS  = 0b00;    //Prescaler 1:1
    T1CONbits.T1SYNC  = 1;       //Sincronizar con la salida del prescaler (Asincrono al oscilador)
    T1CONbits.RD16    = 1;       //TMR1 registro de 16 bits
    
    //Resetear el Timer1
    TMR1 = 0;
    
    //Habilitar el Timer1
    T1CONbits.TMR1ON  = 1;       //Timer0 ON
}

void TIMER1_Start (void)
{
    //Habilitar el Timer0
    T1CONbits.TMR1ON = 1; //Timer0 on
}

void TIMER1_Stop (void)
{
    //Desabilitar el Timer0
    T1CONbits.TMR1ON = 0; //Timer0 off
}


//Configuracion del PWM por comparacion con TIMER2
void TIMER2_ModoPWM_Init (void)
{
    T2CONbits.TMR2ON  = 0;       //Timer2 off
    T2CONbits.T2OUTPS = 0b0000;  //postcaler relacion 1:1
    T2CONbits.T2CKPS  = 0b11;    //prescaler del timer2 a 16
    
    //Iniciar Timer2 en 0 
    TMR2 = 0;
}

void CCPR2_ModoPWM_Init (void)
{
    PR2 = 0xF9;                  //PR2 = 249 para un periodo de 1khz
    CCPR2L = 0;                  //Iniciar el CCP2 en 0
    CCP2CONbits.CCP2M = 0b1100;  //CCP2M en modo PWM       
    //Habilitar timer2
    T2CONbits.TMR2ON = 1;       //Timer2 on
}


void LCD_imprimir_Datos (void)
{
    sprintf(strsetpoint, "SetPoint   :%03.02f",setpoint);
    sprintf(strRPM,      "Velocidad  :%03u   ",RPM);
    
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Control PI-Difuso");
    
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(strsetpoint);
    
    Lcd_Set_Cursor(3, 1);
    Lcd_Write_String(strRPM);
    
    Lcd_Set_Cursor(4, 1);
    Lcd_Write_String("Configuracion (*)");
}

//Configuracion del hardware
void Hardware_Init (void)
{
    //Inicializar el Oscilador
    OSCILADOR_Init();
    //Inicializar GPIO
    PORT_Init();
    //Inicializar teclado 4x4
    Key_Init();
    //Inicializar LCD
    Lcd_Init();
    //Inicializar Interrupciones
    INTERRUPT_Init();
    //Configurar Timer0 como temporizador
    TIMER0_ModoTemporizador_Init();
    //Configurar interrupciones del Timer0
    TIMER0_Interrupt_Init();
    //Configurar el Timer1
    TIMER1_ModoContador_Init();
    //Configurar el Timer2 para PWM
    TIMER2_ModoPWM_Init();
    //Configurar el CCPR2 modo comparador para PWM
    CCPR2_ModoPWM_Init();
    //EUSART
    EUSART_SerialBegin(9600);
}
