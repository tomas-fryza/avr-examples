########################################################################
# 
# AVR project Makefile.
#
# Copyright (c) 2018-2019 Wykys, Tomas Fryza
# Dept. of Radio Electronics, Brno University of Technology, Czechia
# This work is licensed under the terms of the MIT license.
#
# Usage:
#    make        # Compile all binary
#    make all    # Same as make
#    make clean  # Remove ALL binaries and object files from the directory
#    make flash  # Write compiled file to the Flash memory
#    make list   # Generate extended listing file
#    make size   # Display the sizes of sections inside binary file
#
########################################################################

SHELL = /bin/sh
include ../firmware.in

LIBRARY_DIR = ../library

# The result of wildcard is a space-separated list of the names of
# existing files that match the pattern.
SRCS := $(wildcard *.c)
# Add or comment libraries you are using in the project
#SRCS += $(LIBRARY_DIR)/source/lcd.c
#SRCS += $(LIBRARY_DIR)/source/uart.c
#SRCS += $(LIBRARY_DIR)/source/twi.c
ASSRC := $(wildcard *.S)



##
## You should not have to change anything below here
##

# This is called as substitution reference. In this case, if SRCS has
# values 'foo.c bar.c', OBJS variable will have 'foo.o bar.o'.
OBJS := $(SRCS:%.c=%.o)
OBJS += $(ASSRC:%.S=%.o)
# One of the functions for filenames. For example $(notdir src/foo.c hacks)
# produces the result 'foo.c hacks'.
# https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html
OBJS := $(notdir $(OBJS))

## Default rule executed
# target : prerequisites
#	recipe
all : $(TARGET).hex

## Generic compilation rule
# $@...The file name of the target of the rule
# $<...The name of the first prerequisite
# $^...The names of all the prerequisites, with spaces between them
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables
# '%' is a pattern for matching file names
%.o : %.c
	@echo "Compiling \t$< --> $@"
	@$(CC) -c $(CFLAGS) $< -o $@

## Rule for object files from libraries
%.o : $(LIBRARY_DIR)/source/%.c
	@echo "Compiling \t$< --> $@"
	@$(CC) -c $(CFLAGS) $< -o $@

## Rule for object files from assembler
%.o : %.S
	@echo "Assembling \t$< --> $@"
	@$(AS) -c $(ASFLAGS) $< -o $@

## Rule for making the actual target
$(TARGET).elf : $(OBJS)
	@echo "Linking \t$^ --> $@"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

## Rule for Intel Hex file
$(TARGET).hex : $(TARGET).elf
	@echo "Generating Intel Hex \t$< --> $@"
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@

## Rule for extended listing file
list : $(TARGET).lss
$(TARGET).lss : $(TARGET).elf
	@echo "Generating listing file\t$< --> $@"
	@$(OBJDUMP) -h -S $< > $@

## Rule for printing the actual program size
# Displays the sizes of sections inside binary file
size : $(TARGET).elf
	@$(SIZE) --format=avr --mcu=$(MCU) --radix=16 $<

## Rule for program flashing
# https://www.nongnu.org/avrdude/user-manual/avrdude_4.html
flash : $(TARGET).hex
	@echo "Flashing program memory\t$<"
	@$(AVRDUDE) -p $(MCU_DUDE) -c arduino -D -V -u -q -U flash:w:$(TARGET).hex:i -P $(USBPORT) -b 57600

## Clean rule
clean :
	@echo "Cleaning project files \t$(RMFILES)"
	@$(RM) $(RMFILES)
