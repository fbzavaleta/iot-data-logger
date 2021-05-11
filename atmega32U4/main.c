#include "VirtualSerial.h"
#include "main.h"


/*
calculador de timer:
https://eleccelerator.com/avr-timer-calculator/
*/

char teste [] = "Teste final 2\r\n";

int cicle = 0;


int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;

void RGB_Setup()
{
    //Configurando salidas 
    DDRB |= (S0 | S3 | S2) ;
    DDRE |=  S1;

    //Configurando entradas
    DDRD &= (SOUT ^ 0xFF);

    //S0 y S1 en estado alto
    PORTB |= S0;
    PORTE |= S1;
}

void COUNTER_setup(int t_ticks)
{
    //Encontrar el registrador conteo TCCR0A(pag 104)

    TCCR0A = (1 << WGM01); //set CTC: cuando numero de ticks math, genera una interrupcion pag106
    OCR0A  = t_ticks; // El valor total de ticks que sera comparado, pag 109
    TIMSK0 = (1 << OCIE0A); //checkea la interrupcion pag 109
    sei();
    TCCR0B = (1<<CS02) | (1<<CS00); //preescaler en 1024  pag 108
}

int main()
{
    USB_Init_Handle();
    COUNTER_setup(156); //intervalos de 0.01 segundos(ciclo de máquina)


    for (;;)
    {
        //loop
    }
    
    
}

/*
Esto funciona en paralelo
*/

ISR(TIMER0_COMPA_vect)
{
    cicle++;

    if (cicle > 100) // 0.01s * 100 = 1 segundo
    {
        USB_Device_write_Com(teste);
        EVENT_USB_Device_Release();
        cicle = 0;
    }
    
}