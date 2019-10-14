all:
	avr-gcc -std=c99 -Wall -g -Os -mmcu=attiny85 -I. -DF_CPU=1000000UL -o main.o main.c lib/i2c.c lib/ssd1306xled.c lib/ssd1306xledtxm.c lib/si5351.c
	avr-ld -o main.elf main.o
	avr-objcopy -j .text -j .data -O ihex main.o main.hex
	avr-size -C --mcu=attiny85 main.elf

#write flash:
#avrdude -c usbasp -P usb -b 115200 -p attiny85 -e -F -U flash:w:main.hex
#read fuses:
#avrdude -c usbasp -P usb -b 115200 -p attiny85 -U lfuse:r:-:i -v
#write low fuse:
#avrdude -c usbasp -P usb -b 115200 -p attiny85 -U lfuse:w:0x6A:m -v