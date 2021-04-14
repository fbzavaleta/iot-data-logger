"""
Módulo de tratamiento de pulsos
digitales y analógicos, de botones, sensores
y escrita en disco

Autor: Eng. Francis Benjamin
Fecha: 15/03/2021
"""
from machine import ADC
from machine import Pin
import sdcard
from os import mount

#IO pins

IO_ANG  = 0   #Sensor de luminocidad, fijo en el esp8266
IO_SENT = 13  #Boton de envio de datos
SD_ISP  = 1   #Número de la Interface
SD_HC   = 15  #Selector del dispositivo en el ISP bus

#Definiciones Importantes

SD_DIR  = "/sd"

class io():

    def __init__(self):
        self.analog = ADC(IO_ANG)
        self.sendbutton = Pin(IO_SENT, Pin.IN, Pin.PULL_UP)

    def read_lumin(self):
        return  self.analog.read()

    def digital_sendbutton(self):
        return self.sendbutton.value()

class disco():
    """API para escrita de archivos"""
    def __init__(self):
        
        self.sd = sdcard.SDCard(machine.SPI(SD_ISP), Pin(SD_HC))
        self.mount = mount(self.sd, SD_DIR)
        self.count = 0


    def sd_write(self, data:list):
        
        file = open( SD_DIR+"/data.txt", "w")

        

    
        