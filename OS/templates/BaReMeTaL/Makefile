# Makefile for ARM Cortex-M4
# Author: Tzamn Melendez Carmona, Alessio Carpegna

# GNU ARM Embedded Toolchain
ARM_GNU ?= arm-none-eabi

# Compiler flags
AARCH = -mcpu=cortex-m4
CFLAGS = -c -Wall $(AARCH) -mthumb 
ASFLAGS = $(AARCH)
LDFLAGS = -T $(ld_script).ld
DEBUG_FLAGS = -g

# Default target
.DEFAULT_GOAL := all

# Files
ld_script = linker
startup = startup
dly_lib = delay
main = main

# QEMU Configuration
QEMU_FLAGS = -M netduinoplus2 -nographic
qemu_exec = qemu-system-arm $(QEMU_FLAGS) -kernel $(main).elf

# Object files
OBJS = $(startup).o $(dly_lib).o $(main).o
OBJS_DBG = $(startup)_dbg.o $(dly_lib)_dbg.o $(main)_dbg.o

# Rules
# Compile and link
all: $(OBJS) link 

# Compile and link with debug information
debug: $(OBJS_DBG) link_dbg 

# Run QEMU 
qemu_start:
	$(qemu_exec)

# Run QEMU to stop at the first instruction and open the localhost:1234
qemu_debug:
	$(qemu_exec) -s -S

# Pattern rules for object files 
# Compile all the .c files to .o files
%.o: %.c
	$(ARM_GNU)-gcc $(CFLAGS) $< -o $@
	
# Compile all the .c files to _dbg.o files (debug information)
%_dbg.o: %.c
	$(ARM_GNU)-gcc $(DEBUG_FLAGS) $(CFLAGS) $< -o $@

# Assemble all the .s files to .o files
%.o: %.s
	$(ARM_GNU)-as $(ASFLAGS) $< -o $@

# Assemble all the .s files to _dbg.o files (debug information)
%_dbg.o: %.s
	$(ARM_GNU)-as $(ASFLAGS) $(DEBUG_FLAGS) $< -o $@

# Linking
# Link all the files defined in OBJS (.o files) to the main.elf file
link:
	$(ARM_GNU)-ld $(LDFLAGS) $(OBJS) -o $(main).elf

# Link all the files defined in OBJS_DBG (_dbg.o files) to the main.elf file
link_dbg:
	$(ARM_GNU)-ld $(LDFLAGS) $(OBJS_DBG) -o $(main).elf

# GDB
gdb_start:
	gdb-multiarch $(main).elf

# Clean up all the .o and .elf files
clean:
	rm -f *.o *.elf

