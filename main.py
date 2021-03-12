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
from machine import Pin

import i2c 

#Creacion del objeto para 
adress_i2c = i2c.com_i2c().scan_i2c()
i2c_bus    = i2c.com_i2c().i2c_bus
oled       = i2c.lcd(adress_i2c,i2c_bus)


async def blink(led, period_ms):
    while True:
        led.on()
        await uasyncio.sleep_ms(5)
        led.off()
        await uasyncio.sleep_ms(period_ms)


async def print_test(period_ms):

    while True:
        posiciones = [ (0,0), (10,0),(15,0)]
        templates = ["hola 10", "hola 11", "hola 12"]
        oled.text_template(posiciones,templates)

        await uasyncio.sleep_ms(period_ms)


def print_infos(PinNumber):
    pass

#####################3
######
async def main(led,ms):
    uasyncio.create_task(blink(led,700))
    uasyncio.create_task(print_test(ms))
    await uasyncio.sleep_ms(10_000)

uasyncio.run(main(0,400))
    
    

    



    