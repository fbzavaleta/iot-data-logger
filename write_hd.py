import machine, sdcard, os

sd = sdcard.SDCard(machine.SPI(1), machine.Pin(15))
os.mount(sd, '/sd')
os.listdir('/sd')

#myfile = open("/sd/myfile.txt", "w")
#myfile.write(“test data2”)
#myfile.close()
#myfile = open(‘/sd/myfile.txt’, ‘r’)
#myfile.read()