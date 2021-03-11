"""
Firmware de dispositivo de colecta de dados 
y storage em SSD. Enviando a la nuve segun
jerarquia de filas definidas.

Autor: Eng. Francis Benjamin
Fecha: 09/03/2021
"""

import uasyncio
import btree
from time import sleep

import i2c 



def run():

    adress_i2c = i2c.com_i2c().scan_i2c()
    i2c_bus    = i2c.com_i2c().i2c_bus

    oled = i2c.lcd(adress_i2c,i2c_bus)

    oled.write(0,0,"temperatura 10")
    oled.write(0,0,"humedad     11")
    sleep(1)
    oled.write(0,0,"teste 2")
    sleep(1)
    oled.write(0,0,"teste 3")