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

#Objetos i2c
adress_i2c = i2c.com_i2c().scan_i2c()
i2c_bus    = i2c.com_i2c().i2c_bus
oled       = i2c.lcd(adress_i2c[0],i2c_bus) #primer adress i2c
rtc        = i2c.rtc(i2c_bus)


async def blink(led, period_ms):

    led_ = Pin(led, Pin.OUT)
    while True:

        led_.on()
        await uasyncio.sleep_ms(500)
        led_.off()
        await uasyncio.sleep_ms(period_ms)


async def print_test(period_ms):
    
    while True:
        posiciones = [ (0,0), (10,0),(15,0)]
        templates = ["1", "2", "3"]
        oled.text_template(posiciones,templates)
        await uasyncio.sleep_ms(500)
        
        oled.simple_text(0,0,"teste")

        await uasyncio.sleep_ms(period_ms)


def print_infos(PinNumber):
    pass

#####################3
######
async def main(led,ms):
    uasyncio.create_task(blink(led,500))
    uasyncio.create_task(print_test(500))
    await uasyncio.sleep_ms(10000)


uasyncio.run(main(2,500))
sleep(1)

    


    
    

    



    