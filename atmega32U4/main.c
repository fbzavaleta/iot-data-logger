#include "VirtualSerial.h"
#include "main.h"



/*
calculador de timer:
https://eleccelerator.com/avr-timer-calculator/
*/

char teste [] = "Teste final 2\r\n";
char msg_1 [] = "Setado A\r\n";
int period;

int cicle = 0;
int flag_status=1;
int flag_cicle = 0;

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

/*
La variable se tiene que cerada en otra funcion
externa, nunca en la misma funcion de interrupciones
*/
void precise_delay()
{
if(flag_cicle ==1)
{
flag_cicle=0;
return; 
}
}

int main()
{
    RGB_Setup();
    USB_Init_Handle();
    COUNTER_setup(156); //intervalos de 0.01 segundos(ciclo de máquina)
    
    char sensor_salida[8];

    do
    {

        switch (flag_status)
        {
        case 1:
            PORTB &= ( (S2 | S3) ^ 0xFF); // Setando S2 y S3 en LOW
            sprintf(sensor_salida,"%i\n",(PIND & 0x40));
            USB_Device_write_Com(sensor_salida);

            break;

        case 2:
            USB_Device_write_Com("segundo\n");

            break;
        
        default:
            break;
        }
        EVENT_USB_Device_Release();
        
        precise_delay();

    } while (1);
        
    
}



ISR(TIMER0_COMPA_vect)
{
    cicle++;

    if (cicle > 1000) //0.01s * 500 = 5 segundo
    {
        if (flag_status == 1)
        {
            flag_status = 2;
        }
        else if (flag_status == 2)
        {
            flag_status = 1;
        }
        
        cicle = 0;
        flag_cicle = 1;
    }

}