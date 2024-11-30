# Define the toolchain and flags
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CPU = -mcpu=cortex-m4
THUMB = -mthumb
CFLAGS = -c $(CPU) $(THUMB)
LDFLAGS = -T linker.ld

# Object files
OBJ = startup.o library.o main.o 

# Output file
TARGET = main.elf

# Default target to build the ELF file
all: $(TARGET)

# Rule to create startup.o from startup.s
startup.o: startup.s
	$(AS) $(CPU) startup.s -o startup.o

# Rule to create main.o from main.c
main.o: main.c
	$(CC) $(CFLAGS) main.c math_utils.h -o main.o

# Rule to create library.o from library.c
library.o: library.c
	$(CC) $(CFLAGS) library.c -o library.o

# Rule to link the object files and create the final ELF
$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)

# Clean up the generated files
clean:
	rm -f $(OBJ) $(TARGET)

