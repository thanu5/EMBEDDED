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
void lcd_output(unsigned int );
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned char s , n,k[10], j;
unsigned int m ;
unsigned long value, voltage;

void main()
{
    init();
    while(1)
    {
        ADCON0 = 0x81;
      ADCON0|=  0x04;// Go_done ==1
      
      while(ADCON0&0x04);
      ADRESH;
      ADRESL;
      value = ((unsigned int)ADRESH<<8) + (unsigned int)ADRESL;
      voltage = (value*338)/1023;
      lcd_command(0x80);
      lcd_output(voltage);
     CCPR1L = (voltage)>>2;
     CCP1CON = (CCP1CON&0x0C) + ((voltage&0x03)<<4); 
       __delay_ms(1000);     
    }
}

void init()
{
    TRISA = 0x01;
    TRISC = 0x00;
    TRISD = 0x00;
    
    ADCON0 = 0x81;
    ADCON1 = 0x8E;
   CCP1CON = 0x0C;
    T2CON = 0x06;
   PR2 = 0x5E;
    lcd_command(0x30);
    __delay_ms(100);
     lcd_command(0x30);
     __delay_ms(100);
     lcd_command(0x30);
    __delay_ms(100);
     lcd_command(0x38);
    __delay_ms(100);
    lcd_command(0x14);
    __delay_ms(100);
    lcd_command(0x0C);
    __delay_ms(100);
    lcd_command(0x01);
    __delay_ms(100);
    
}
void lcd_output(unsigned int i)
{ 
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
    PORTC&=0xF7;//Rs=1
    PORTD=i;
    PORTC|=0x01;//EN=1
    PORTC&=~0x01;//EN =0
    __delay_ms(100);
}

void lcd_data(unsigned char i)
{
    PORTC|=0x08;//RS =0
    PORTD=i;
    PORTC|=0x01;//en=1
    PORTC&=~0x01;//en=0
    __delay_ms(100);
}
