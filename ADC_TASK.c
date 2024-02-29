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
void init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_output(unsigned int);
void lcd_output1(unsigned int);
unsigned char s,j,x,n,k[10];
unsigned char volt[30] =("VOLTAGE:");
unsigned char orig[30] = ("ORIGINAL:");
unsigned int m;
void lcd_display(unsigned int);
unsigned long value,voltage ;
void main()
{
    init();
    while(1)
    {
        ADCON0 = 0x91;
        ADCON0|= 0x04;
        while(ADCON0&0x04);
        ADRESL ;
        ADRESH ;
        value =((unsigned int ) ADRESH<<8) + (unsigned int)ADRESL;
        lcd_output1(value);
        voltage  = (value*100)/1023;
        lcd_command(0xC0);
        __delay_ms(100);
          lcd_output(voltage);
        __delay_ms(100);
        
    }
}
void init()
{
    TRISA =0x04;
    TRISC = 0x00;
    TRISD = 0x00;
    ADCON0 = 0x91;
    ADCON1 =0x80;
    lcd_command(0x30);
    __delay_ms(100);
     lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
     lcd_command(0x38);
    __delay_ms(100);
     lcd_command(0x14);// left to right shift command
    __delay_ms(100);
     lcd_command(0x0C);// display cursor on and off
    __delay_ms(100);
     lcd_command(0x01);  // clear  display
    __delay_ms(100);
   
}
void lcd_output1(unsigned int i){// digital value
        lcd_command(0x80);
        for(x=0;x<9;x++)
        {
            lcd_data(orig[x]);
           
        }
    if (i < 10)
    {
        lcd_data(0x30); 
        lcd_data(0x30 + i); 
         lcd_data(0x20);
          lcd_data(0x20);
           lcd_data(0x20);
    }
    else if (i < 100)
    {
        lcd_data(0x30 + i / 10);
        lcd_data(0x30 + i % 10); 
         lcd_data(0x20);
          lcd_data(0x20);
    }
    else if (i < 1000)
    {
        lcd_data(0x30 + i / 100);    
        lcd_data(0x30 + (i / 10) % 10);  
        lcd_data(0x30 + i % 10); 
         lcd_data(0x20);
    }
    else
    {
        lcd_data(0x30 + i / 1000);
        lcd_data(0x30 + (i / 100) % 10);
        lcd_data(0x30 + (i / 10) % 10);
        lcd_data(0x30 + i % 10);
    }
}
void lcd_output(unsigned int i)//calibrated value
{   
    for(x=0;x<8;x++)
    {
        lcd_data(volt[x]);
     }
    if (i < 10)
    {
             
        lcd_data(0x30 + i);
        lcd_data(0x56);
        lcd_data(0x20);
        lcd_data(0x20);
    }
    else if (i < 100)
    {
        lcd_data(0x30 + i / 10);  
        lcd_data(0x30 + i % 10); 
        lcd_data(0x56);
        lcd_data(0x20);
    }
    else
    {
        lcd_data(0x30 + i / 100);
        lcd_data(0x30 + (i / 10) % 10);
        lcd_data(0x30 + i % 10);
         lcd_data(0x56);
    }
}
 void lcd_command(unsigned char i)
{
    PORTC&=0xF7;// RS-- RC3 =1
    PORTD=i;
    PORTC|=0x01;//ENABLE=1
    PORTC&=~0x01;//ENABLE =0
    __delay_ms(100);
}
void lcd_data(unsigned char i)
{
    PORTC|=0x08;//RS =0
    PORTD=i;
    PORTC|=0x01;//enable =1
    PORTC&=~0x01;//enable=0
    __delay_ms(100);
}