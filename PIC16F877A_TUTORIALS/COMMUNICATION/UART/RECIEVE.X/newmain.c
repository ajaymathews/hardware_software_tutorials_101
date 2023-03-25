
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 16000000  // defining the frequency as _Xtal_Freq becuase __delay() uses this name
#include <xc.h>   // defining compiler fuctions 
char UART_Recieve()
{
    while(RCIF==0); // checking if the reception complete or not 1=complete,0=not-complete
    return(RCREG);  //the data that comes to the rcreg register is returned to the function

}
int UART_Init(long int baudrate)    // 
    { 
    long int x;
    x=(_XTAL_FREQ - baudrate*64)/(baudrate*64);   // finding the spbrg,initially taken baudrate as low  value of x for 9600 baudrate is 25
                                                  // then if the baudrate high becomes x>255(max value of a 8 byte is 255)
    if(x>255)
    {
        x=(_XTAL_FREQ - baudrate*16)/(baudrate*16); // setting the spbrg for the high baudrate
        BRGH=1;                                     // setting brgh=1 means it is a high baudrate
    }
    if(x<256)                                 // if the baudrate a low value
    {
    SPBRG=x;                                 //setting the spbrg always need to done
    //SPBRG=25;                              // or we can set the spbrg as 25, no above calculation required
    TXEN=1;                                 // setting this bit as 1 only enables the transmission if not no transmission
    SPEN=1;                                 //enabling the serial port,then only rs&tx work instead of rc6&rc7
    CREN=1;                                 //enables continuos transmission, if not stops after one byte
    TRISC6=0;
    TRISC7=1;
    TRISC1=0; 
    return 1;       // sucessful completion of block initialization
    }
 //   SPBRG=25;
    return 0;      //initialization not sucessful 
}
void main(void) 
{
    char re;
    UART_Init(9600);
    re=UART_Recieve();
    if(re=='o')
    {
        RC1=1;
    }
    else if(re=='x')
    {
        RC1=0; 
    }
    
}
