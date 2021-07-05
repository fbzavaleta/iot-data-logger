#include "VirtualSerial.h"
#include "main.h"
/*
calculador de timer:
https://eleccelerator.com/avr-timer-calculator/
*/

/*
S0  --> PB7 (PIN)
S1  --> PB6
S3  --> PB0
S2  --> PB4
OUT --> PB2
*/
int logic = 0;
int Rojo_Frec  = 0;
int Verde_Frec = 0;
int Azul_Frec  = 0;

int TimerOverflow = 0;

void RGB_Setup()
{
    //Configurando salidas y entradas
    DDRB = 0b11010001;

    //Configurando las frecuencias en 20% s0 high s1 low
    PORTB = 0b01000000;
}

/*
Habilita  interrupciones por
comparacion de la variable de estoro
*/

void ConfigInterr_Compare(int t_ticks)
{
    //Encontrar el registrador conteo TCCR0A(pag 104)

    TCCR0A = (1 << WGM01); //set CTC: cuando numero de ticks math, genera una interrupcion pag106
    OCR0A  = t_ticks; // El valor total de ticks que sera comparado, pag 109
    TIMSK0 = (1 << OCIE0A); //habilita la interrupcion pag 109
    sei();
    TCCR0B = (1<<CS02) | (1<<CS00); //preescaler en 1024  pag 108 
}


/*
Habilita  un determinado PIN, cuando este cambia
de estado, genera una interrupcion
*/
void ConfigInterr_Changestate()
{
    /*
    Configuracion del timer0 - interrupcion por cambio de estado
    */
    PCICR = (1<<PCIE0); // Habilitando change interrupt control pag91 11.1.5
    PCMSK0 = (1 << PCINT2);//HAbilitando el PB2 pag 91 11.1.7


}

/*
Habilita interrupciones por overflow
*/
void ConfigInterr_Overflow()
{
    /*
    Configuracion del timer1- interrupcion por overflow
    */
    TIMSK1 = (1 << TOIE0); // interrupcion por overflow
    TCCR1A = 0; //Operacion normal pag 131
    
}

void Precise_delay(int seconds)
{
    /*
    Para un overflow de 10 ms
    TCTNT0 = 255 - CPUFREQ * delya/preescaleer
    TCTNT0 =255 - 16MHz * 10ms/1024 ~= 100 
    */
    TCNT0 = 100;
    TCCR0B = (1<<CS02) | (1<<CS00); //preescaler en 1024  pag 108 

    int counter = 0;

    while ((counter*10) < seconds)
    {
        while ((TIFR0 & 0x01) == 0x00); // caso ocurra una interrupcion
        TIFR0 = 0x01;
        counter++;
    } 
}

/*
Cuando ocurre una interrupción- cambio de estado
*/
ISR(PCINT0_vect)
{
    PORTB ^= (1<<PB5);
    logic++;
}

/*
Cuando ocurre una interrupción- Overflow
*/
ISR(TIMER1_OVF_vect)
{
    TimerOverflow++;
}

int main()
{
    RGB_Setup();
    USB_Init_Handle();
    ConfigInterr_Changestate();
    sei();
    ConfigInterr_Overflow();

    DDRB |= 0b00100000;
    
    char sensor_salida[8];
    /*
    No tengo que fijarme en el sincornismo, unicamente en un flag que diga si detecto 
    interrupcion para ir al siguiente
    */

    do
    {   
        sprintf(sensor_salida,"%i\n", logic);

        PORTB &= 0b11101110; //s2 low s3 low
        USB_Device_write_Com("Activado1\n");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(10);

        PORTB &= ((1 << PB4) | (1 << PB0)); //s2 y s3 high
        USB_Device_write_Com("Activado2\n");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(10);

        PORTB |= 0b00000001; // s2 low s3 high
        USB_Device_write_Com("Activado3\n");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(10);
        
       
    } while (1);
        
    
}

/*
Primero habilitar la funcion de comparacion
*/

/*
Cuando ocurre una interrupción- Comparacion

ISR(TIMER0_COMPA_vect)
{
    cicle++;

    if (cicle > 1000) //0.01s * 500 = 5 segundo
    {
        cicle = 0;
    }

}
*/