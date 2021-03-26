"""
Módulo de tratamiento de pulsos
digitales y analógicos, de botones
y sensores

Autor: Eng. Francis Benjamin
Fecha: 15/03/2021
"""
from machine import ADC
from machine import Pin

#IO pins

IO_ANG  = 0   #Sensor de luminocidad, fijo en el esp8266
IO_SENT = 13  #Boton de envio de datos



class io():

    def __init__(self):
        self.analog = ADC(IO_ANG)
        self.sendbutton = Pin(IO_SENT, Pin.IN, Pin.PULL_UP)

    def read_lumin(self):
        return  self.analog.read()

    def digital_sendbutton(self):
        return self.sendbutton.value()

    
        