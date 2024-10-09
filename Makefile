# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Default target.
all: game.out

# Compile: create object files from C source files.
main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

game.o: game.c game.h
	$(CC) -c $(CFLAGS) $< -o $@

setup.o: setup.c setup.h
	$(CC) -c $(CFLAGS) $< -o $@

attack.o: attack.c attack.h
	$(CC) -c $(CFLAGS) $< -o $@

defend.o: defend.c defend.h
	$(CC) -c $(CFLAGS) $< -o $@

winlose.o: winlose.c winlose.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: main.o game.o setup.o attack.o defend.o winlose.o system.o
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