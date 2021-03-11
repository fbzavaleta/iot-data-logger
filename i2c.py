"""
Modulo para comunicación I2C con el
controlador del oled. 
Implemetanción de funciones de exibición
avanzadas. 

Autor: Eng. Francis Benjamin
Fecha: 09/03/2021
"""
from machine import I2C, Pin
from sys import exit
from ssd1306 import SSD1306_I2C

#definiciones importantes

SCL = 5
SDA = 4
LX  = 128 #largura de el lcd
LY  = 64  #Altura del lcd

class com_i2c():

    def __init__(self):
        self.i2c_bus = I2C(scl=Pin(SCL), sda=Pin(SDA))
    
    def scan_i2c(self):
        devices = self.i2c_bus.scan()

        if devices == []:
            exit("No han sido encontrados dispositivos en el barramento I2C")

        else:
            print("Dispositivo encontrando en {addss}".format(addss = hex(devices[0])))
            device_adress = devices[0]
            return device_adress

class lcd(object):

    def __init__(self,com,i2c):
        self.com  = com
        self.i2c  = i2c
        self.oled = SSD1306_I2C(LX, LY, i2c, com )

    def simple_text(self, posx:int,posy:int,texto:str):
        self.oled.fill(0) #Limpiando la pantalla
        self.oled.text(texto, posx, posy)
        self.oled.show()

    def text_template(self,pos:dict,text_template:str,values:list):
        pass

        


            