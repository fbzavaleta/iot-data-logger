#include "VirtualSerial.h"
#include "main.h"
/*
calculador de timer:
https://eleccelerator.com/avr-timer-calculator/
https://www.electronicwings.com/avr-atmega/ultrasonic-module-hc-sr04-interfacing-with-atmega1632
*/

/*
S0  --> PB7 (PIN)
S1  --> PB6
S3  --> PB0
S2  --> PB4
OUT --> PB2
*/

int Rojo_Frec  = 0;
int Verde_Frec = 0;
int Azul_Frec  = 0;

int TimerOverflow = 0;

void RGB_Setup()
{
    //Configurando salidas y entradas
    DDRB = 0b11010001;
    DDRD = 0b00000000;

    //Configurando las frecuencias en 20% s0 high s1 low
    PORTB = 0b01000000;
}



/*
Habilita interrupciones por overflow
*/
void ConfigInterr_Overflow_InputCapture()
{
    /*
    Configuracion del timer1- interrupcion por overflow
    */
    TIMSK1 = (1 << TOIE0); // interrupcion por overflow
    TCCR1A = 0; //Operacion normal pag 131
    
}


long Pulse_Messure()
{
    long pulse_ms;
    /*Limpieza*/
    TCNT1 = 0; // Limpieza del contador
    TCCR1B = (0<< ICES1) | (1 << CS10); // rising (positive) edge | clk I/O /1 (No prescaling pag134
    TIFR1 = (1 << ICF1); //Limpiando el input capture flag pag 138 PD4
    TIFR1 = (1 << TOV1); //Limpienado el flag de overflow pag 138

    while (TIFR1 & (1 << ICF1) == 0) // esperando al falling edge

    TCNT1 = 0; // Limpieza del contador
    TCCR1B = (1 << CS10); // no preescaler  fallind edge
    TIFR1 = (1 << ICF1); //Limpiando el input capture flag pag 138
    TIFR1 = (1 << TOV1); //Limpienado el flag de overflow pag 138

    TimerOverflow = 0;/* Clear Timer overflow count */
    
    while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */

    pulse_ms = ICR1 + (256 * TimerOverflow);


    return pulse_ms;
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
Cuando ocurre una interrupción- Overflow
*/
ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1<<PB5);
    TimerOverflow++;
}



int main()
{
    RGB_Setup();
    USB_Init_Handle();
    sei();

    ConfigInterr_Overflow_InputCapture();

    DDRB |= 0b00100000;
    
    
    char sensor_salida[8];


    do
    {   
        
        PORTB &= 0b11101110; //s2 low s3 low
        sprintf(sensor_salida,"%li", Pulse_Messure());
        USB_Device_write_Com("-");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(100);
        

        PORTB &= ((1 << PB4) | (1 << PB0)); //s2 y s3 high
        sprintf(sensor_salida,"%li", Pulse_Messure());
        USB_Device_write_Com("-");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(100);
     

        PORTB |= 0b00000001; // s2 low s3 high
        sprintf(sensor_salida,"%li\n", Pulse_Messure());
        USB_Device_write_Com("-");
        USB_Device_write_Com(sensor_salida);
        Precise_delay(500);

        
       
    } while (1);
        
    
}

