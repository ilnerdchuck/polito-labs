# Makefile for multi-file progra
# set as default compiler gcc
# set a gcc flags -Wall
# 
# Compiles main.c and math_utils.c into object files (main.o and math_utils.o).
# Links the object files into an executable named math_program.elf.
# Includes a rule that recompiles math_utils.c if math_utils.h is modified.
# Has a clean rule to remove the executable and any object files.

CC = gcc
CFLAGS = -Wall

# Object files
OBJ = main.o main_utils.o 

# Output file
TARGET = math_program.elf

# Default target to build the ELF file
all: $(TARGET)

math_utils.o: math_utils.h
	$(CC) $(CFLAGS) math_utils.c -o math_utils.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

# Rule to link the object files and create the final ELF
$(TARGET): $(OBJ)
	$(LD) $(OBJ) -o $(TARGET)

# Clean up the generated files
clean:
	rm -f $(OBJ) $(TARGET)

