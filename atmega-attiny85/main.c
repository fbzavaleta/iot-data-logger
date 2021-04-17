/*
Algunas definicions del hardware
*/
#include "tiny.h"

/*
libs del toolchain avr
*/

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  //Sentido output, registrador de datos
  DDRB |= (1 << PB0);
  
  // event loop
  while (1)
 {
    PORTB ^= (1 << PB0);   // xor en el bit 0 del PORTB
    _delay_ms(400);        // delay 500 ms
  }                                                
  return (0);         
}