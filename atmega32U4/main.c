#include "main.h"

#include <avr/io.h>
#include <util/delay.h>


/*
https://create.arduino.cc/editor/ProfeGarcia/94423536-718b-49c8-8268-de791fae0b6d/preview
*/
 /*
 https://www.youtube.com/watch?v=cAui6116XKc
 */

void setup_RGB()
{

    DDRB |= S0 | S1 | S2 | S3 ;
    
    DDRE &= SOUT;

    //Escala de frecuencia en 20%

    PORTB &= 0x80; //S0 5v y S1 low

}

void usart_init(unsigned int baud)
{
    /*Baud rate*/
    UBRR1H = (unsigned char)(baud >> 8);
    UBRR1L = (unsigned char)baud;

    /*Activando el receptor/transmisor*/
    UCSR1B = (1<<RXEN1) | (1<<TXEN1);
    UCSR1C = (1<<USBS1) | (3<<UCSZ10);
}

void usart_trasnmit(unsigned char data)
{
    while (!(UCSR1A & (1<< UDRE1))){}

    UDR1 = data;
    
}

void usart_recive( void)
{
    while(UCSR1A & (1<< RXC1)){}
    return UDR1;
}


int main(int argc)
{
    setup_RGB();

    do
    {
        /* code */
    } while (1);
    
}