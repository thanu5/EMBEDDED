
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
#include <xc.h>
#define _XTAL_FREQ 6000000
// declaring the function
void init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned char x,i;
// array initilization.... 
unsigned char a[7] = ("THANUSH");
unsigned char b[7] = {0x82,0x83,0x84,0x85,0x86,0x87,0x88};
unsigned char c[7] = {0xCD,0xCC,0xCB,0xCA,0xC9,0xC8,0xC7};
void main()
{
   init(); //Calling the init function
   
   // lcd command and data for left to right
   for (x = 0; x <7; x++) {
        lcd_command(b[x]); 
        lcd_data(a[x]);
   }
   // lcd command and data for right to left
    for (x = 0; x<7;x++)  
    {
        lcd_command(c[x]);
        lcd_data(a[x]);   
    }
   while(1);
}
void init()
{  // configuring output
    TRISC = 0x00;
    TRISD = 0x00;
    // initiliaze the LCD
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
   __delay_ms(100);
    lcd_command(0x38);//16x2 row and column and 5x7 matrix
    __delay_ms(100); 
    lcd_command(0x0C); // cursor on and off
    __delay_ms(100);
    lcd_command(0x01); // clear the display
    __delay_ms(100); 
}
void lcd_data(unsigned char i)
{
    RC2= 1; // RS=1
    PORTD = i; // send data
    RC0 = 1;// EN=1
    RC0= 0;// En =0
    __delay_ms(100); 
}
void lcd_command(unsigned char i)
{
    RC2= 0; // RS=0
    PORTD = i; // send command
    RC0 = 1;// EN=1
    RC0= 0;// En =0
    __delay_ms(100);
}