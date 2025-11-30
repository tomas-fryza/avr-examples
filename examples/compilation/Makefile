# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -std=c11
# Source files
SRCS    = main.c utils.c
# Object files
OBJS    = main.o utils.o
# Output executable
EXEC    = myprogram
# Files to be clean up
RMFILES = $(OBJS) $(EXEC) *.s *.i

## Default target
# target: prerequisites
#     recipe
all: $(EXEC)

## Generic compilation rules
# @....Do not print the actual command, just the result of the command
# $@...Target name
# $<...The name of the first prerequisite
# $^...The names of all the prerequisites, with spaces between them
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables
# Link the object files to create the executable
$(EXEC): $(OBJS)
	@printf "Linking: $^ --> $@\n\t"
	$(CC) $(OBJS) -o $(EXEC)

## Compile main.c into main.o
main.o: main.c utils.h
	@printf "Compiling: $^ --> $@\n\t"
	$(CC) $(CFLAGS) -c main.c

## Compile utils.c into utils.o
utils.o: utils.c utils.h
	@printf "Compiling: $^ --> $@\n\t"
	$(CC) $(CFLAGS) -c utils.c

## Preprocess source files *.c to *.i
preprocess: $(SRCS)
	@printf "Preprocessing \t$^... "
	@$(CC) $(CFLAGS) -E main.c > main.i
	@$(CC) $(CFLAGS) -E utils.c > utils.i
	@printf "\x1b[32;1mDone\x1b[0m\n"

## Compile source files *.c to assembly *.s
assembly: $(SRCS)
	@printf "Assembling \t$^... "
	@$(CC) $(CFLAGS) -S $(SRCS)
	@printf "\x1b[32;1mDone\x1b[0m\n"

## Clean up generated files
clean:
	@printf "Cleaning project files... "
	rm -f $(RMFILES)
	@printf "\x1b[32;1mDone\x1b[0m\n"

version:
	$(CC) --version

# Phony targets (not real files just labels for commands to be executed)
# This prevents make from confusing these names with files in the directory.
.PHONY: all preprocess assembly clean version
