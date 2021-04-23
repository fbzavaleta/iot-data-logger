######################################
#PROGRAMA PARA COMPILACIÓN Y UPLOAD DE
#MCUs AVR EN LINUX.
#
#1.MODIFICAR LAS VARIABLES SEGUN LA 
#PLATAFORMA.
#
#2.COMPILAR --> make all
#
#3.PROGRAMAR--> make upload
#
#AUTOR: Francis Zavaleta
#

######################-VARIABLES-#######################
AVR_MCU = atmega328p
SERIAL_PORT = /dev/ttyACM0
BAUD_RATE = 115200
AVR_PROGRAMER = arduino
########################################################

##########################-COMPILADOR-##################
CC=avr-gcc
CFLAGS= -g -Os -mmcu=$(AVR_MCU)
LDFLAGS= -Wl,-Map=main.map
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump

all: msg main.hex 

msg: 
	@echo '1- Inicio de compilación'
####################################################

##########################-OBJETOS-######################
main.elf: main.o atmega32U4.o uart.o
	@echo '3- Genera main.elf'
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
########################################################

##########################-SOURCES-######################
main.o: main.c main.h 
	@echo '1- Genera main.o'
	$(CC) $(CFLAGS) -c $< -o $@ 

atmega32U4.o: atmega32U4.c atmega32U4.h
	@echo '2- Genera atmega32U4.o'
	$(CC) $(CFLAGS) -c $< -o $@ 

uart.o: uart.c uart.h
	@echo '2- Genera uart.o'
	$(CC) $(CFLAGS) -c $< -o $@ 	
########################################################

########################-EJECUTABLES AVR-####################
main.lst: main.elf
	$(OBJDUMP) -d $< > $@

main.hex: main.elf
	@echo '4 - Genera main.hex'
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

########################################################

##########################-UPLOAD-######################
upload: main.hex
	avrdude -p $(AVR_MCU) -c $(AVR_PROGRAMER) -P $(SERIAL_PORT) -b $(BAUD_RATE) -U flash:w:main.hex:i

########################################################

clean:
	rm -rf main.o atmega32U4.o main.elf main.hex main.map uart.o
