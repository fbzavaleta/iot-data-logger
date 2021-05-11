#
#             LUFA Library
#     Copyright (C) Dean Camera, 2021.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.

#Modify by Francis Zavaleta :
#-AVRDUDE support
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u4
ARCH         = AVR8
BOARD        = LEONARDO
SERIAL_PORT = /dev/ttyACM0
BAUD_RATE = 9600 
AVR_PROGRAMER = avr109
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
#TARGET       = VirtualSerial
TARGET       = main
SRC          = $(TARGET).c Descriptors.c VirtualSerial.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = ../../../../LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =

# Default target
all:

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk

##########################-UPLOAD-######################
upload: VirtualSerial.hex
	avrdude -p $(MCU) -c $(AVR_PROGRAMER) -P $(SERIAL_PORT) -b $(BAUD_RATE) -U flash:w:${TARGET}.hex:i
