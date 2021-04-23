#include "main.h"

#include <avr/io.h>
#include <util/delay.h>

/*
https://create.arduino.cc/editor/ProfeGarcia/94423536-718b-49c8-8268-de791fae0b6d/preview
*/


void setup_RGB()
{

    DDRB |= S0 | S1 | S2 | S3 ;
    
    DDRE &= SOUT;

    //Escala de frecuencia en 20%

    PORTB &= 0x80; //S0 5v y S1 low

}



int main(int argc)
{
    setup_RGB();

    do
    {
        /* code */
    } while (1);
    
}