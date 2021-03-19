"""
Modulo para comunicación I2C con el
controlador del oled y rtc. 
Implemetanción de funciones de exibición
avanzadas. 

Autor: Eng. Francis Benjamin
Fecha: 09/03/2021
"""
from machine import I2C, Pin
from sys import exit
#drivers de los dispositivos
from ssd1306 import SSD1306_I2C
from DS3231 import DS3231

#definiciones importantes

SCL = 5   #Cable de pulsos de clock (GPIO5)
SDA = 4   #Cable de datos  (GPIO4)
LX  = 128 #ancho de el lcd
LY  = 64  #Altura del lcd

class com_i2c():

    def __init__(self):
        self.i2c_bus = I2C(scl=Pin(SCL), sda=Pin(SDA))
    
    def scan_i2c(self):
        devices = self.i2c_bus.scan()
        

        if devices == []:
            exit("No han sido encontrados dispositivos en el barramento I2C")

        else:
            for dev in devices:
                print("Dispositivo encontrando en {addss}".format(addss = hex(dev)))
            return devices

class lcd(object):

    def __init__(self,com,i2c):
        self.com  = com
        self.i2c  = i2c
        self.oled = SSD1306_I2C(LX, LY, i2c, com )

    def simple_text(self, posx:int,posy:int,texto:str):
        self.oled.fill(0) #Limpiando la pantalla
        self.oled.text(texto, posx, posy)
        self.oled.show()

    def text_template(self,pos:list,text_template:list):
        self.oled.fill(0)

        if len(pos) != len(text_template):
            exit("Las coordenadas no coinciden con la cantidad de templates")

        else:
            for coordxy in pos:
                n = pos.index(coordxy)
                self.oled.text(text_template[n], coordxy[0], coordxy[1])
        
        self.oled.show()

   
class rtc(object):

    def __init__(self,i2c):

        self.i2c = i2c
        self.ds3231 = DS3231(i2c)

    def time(self):
        return self.ds3231.get_time()

    
        


        


            