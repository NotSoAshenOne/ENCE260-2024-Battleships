#	File: Makefile
#	Authors: Morgan Lee (mle150) and Kaden Adlington (kad112)
#	Date: 12/10/2024
#	Decr: Makefile for our battleships game.


# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Default target.
all: game.out

# Compile: create object files from C source files.
game.o: game.c setup.h attack.h defend.h winlose.h ship.h ../../drivers/avr/system.h ../../utils/tinygl.h ../../utils/pacer.h ../../drivers/button.h ../../drivers/led.h ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

ship.o: ship.c ship.h game.h ../../drivers/avr/system.h ../../utils/tinygl.h ../../drivers/navswitch.h ../../drivers/button.h ../../utils/pacer.h

setup.o: setup.c ship.h setup.h game.h ../../utils/tinygl.h ../../utils/pacer.h ../../drivers/button.h ../../drivers/led.h ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

attack.o: attack.c attack.h game.h ship.h ../../drivers/avr/ir_uart.h ../../utils/tinygl.h ../../utils/pacer.h ../../drivers/led.h ../../drivers/navswitch.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

defend.o: defend.c defend.h ship.h game.h ../../drivers/avr/ir_uart.h ../../utils/tinygl.h ../../drivers/button.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

winlose.o: winlose.c winlose.h game.h ../../utils/tinygl.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o ship.o setup.o attack.o defend.o winlose.o pio.o system.o led.o timer.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o ir_uart.o prescale.o usart1.o timer0.o timer.o button.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex

# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start