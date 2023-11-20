
#define _XTAL_FREQ 16000000UL
#include "lib_pic/config_mcu.h"
#include "lib_pic/lcd.h"
#include "lib_pic/keypad_4x4.h"
#include "lib_pic/adc.h"
#include "lib_pic/eusart.h"
#include "lib_pic/Control_temperatura_difuso.h"

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
void Tomar_muestra_temperatura(void);

//Variables de estado
uint8_t APPState;

//Variables
volatile bool  flagTimer0 = false;
float  voutMCP9700A = 0.0;
float  tempMCP9700A = 0.0;
char   SP[20];
char   strMCP9700A[20], strsetpoint[20], strTemp[40], strpwm[40], strtiempo[40];
float  setpoint , error = 0.0, error_ = 0.0, salida = 0.0, salida_ = 0.0;
float  Cambio_error = 0.0;
uint8_t contador = 0, tiempo = 0;

//Teclado
char tecla;
uint8_t indice = 0;
uint8_t columna = 11;

//Tiempo de muestreo
float Ts = 1.0;

//Constante
//Mientras mas rapido sea el tiempo de establecimiento, disminuir el valor de la constante
//Para evitar sobre-impulsos en el sistema

float  constante = 2;

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
                
                //Cambio de estado
                APPState = ESTADO_SELECCION_REFERENCIA;
                
            break;
            
            //****************************************    
            case ESTADO_SELECCION_REFERENCIA:
                //Imprimir en LCD
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Elegir referencia");
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Rango [0-100]");
                
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
                            
                        if(setpoint > 100)
                        {
                            //Limpiar LCD
                            Lcd_Clear();
                            
                            //Imprimir mensaje
                            Lcd_Set_Cursor(1,1);
                            Lcd_Write_String("  Referencia fuera");

                            Lcd_Set_Cursor(2,1);
                            Lcd_Write_String("  del Rango [0-100]");

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
                
                //Leer dato del sensor
                Tomar_muestra_temperatura();     
                
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
                
                
                
                //Calcular error
                error = setpoint - tempMCP9700A;

                //Saturar error con universo de discurso de <-200,200>
                if(error > 199.9)
                {
                    error = 199.9;
                }
                else if(error < -199.9)
                {
                    error = 199.9;
                }

                //Calcular Cambio del error
                Cambio_error = (error - error_)/Ts;

                //Calcular Cambio error con universo de discurso de <-4,4>
                if(Cambio_error > 3.9999999)
                {
                    Cambio_error = 3.9999999;
                }
                else if(Cambio_error < 0.0)
                {
                    Cambio_error = 0.0;
                }

                //Controlador difuso
                Control_temperatura_difusoInferenceEngine(error,Cambio_error,&salida);

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
                __delay_ms(500);
                
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
                
                //Mandar por UART           
                sprintf(strTemp, "%01.02f,", tempMCP9700A);
                sprintf(strpwm,  "%01.02f,", salida_sistema);
                sprintf(strtiempo,"%01u\r\n",tiempo);
                
                EUSART_WriteString(strTemp);
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
        //Recargar el Timer0 para contar 1000ms nuevamente
        TMR0 = 34286;
        
        //Ejecutar la tarea
        flagTimer0 = true;
        
        //Contador del tiempo por actual por muestra
        tiempo++;
        
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

//Tomar datos y mostrar
void Tomar_muestra_temperatura(void)
{
    int i;
    
    tempMCP9700A = 0.0;
    
    for(i=0;i<20;i++)
    {
        //Obtener muestra del canal AN1  del ADC
        voutMCP9700A = (((float)ADC_GetConversion(ADC_AN1))*(ADC_VREF/ADC_RESOLUCION));
    
        //Calcular temperatura para sensores
        tempMCP9700A += ((voutMCP9700A)/ 0.01f);
    }
    
    tempMCP9700A = tempMCP9700A/20.0;
    
}

void LCD_imprimir_Datos (void)
{
    sprintf(strsetpoint, "SetPoint   :%03.02fC",setpoint);
    sprintf(strMCP9700A, "Temperatura:%03.02fC",tempMCP9700A);
    
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Control PI-Difuso");
    
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(strsetpoint);
    
    Lcd_Set_Cursor(3, 1);
    Lcd_Write_String(strMCP9700A);
    
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
    //Inicializar el ADC
    ADC_Init();
    //Inicializar LCD
    Lcd_Init();
    //Inicializar Interrupciones
    INTERRUPT_Init();
    //Configurar Timer0 como temporizador
    TIMER0_ModoTemporizador_Init();
    //Configurar interrupciones del Timer0
    TIMER0_Interrupt_Init();
    //Configurar el Timer2 para PWM
    TIMER2_ModoPWM_Init();
    //Configurar el CCPR2 modo comparador para PWM
    CCPR2_ModoPWM_Init();
    //EUSART
    EUSART_SerialBegin(9600);
}
