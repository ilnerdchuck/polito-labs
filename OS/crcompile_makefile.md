### Cross compilation

´´´ #DEFINE N=5
    #include<stdio>

    void main(){
        int a,b=5
        
        a += b;
        
        return 0 
    }
´´´
- header files: we simply declare the interfaces of objects and functions
- c files: we include the header file and specify what the funcion does (implementation)
    - Remember that a file can be included multiple times so use something like ´ #pragma once ´ or the example of the 
      professor 


Develop code for an another machine in my machine with different architecture

#### gcc command:
    
    - preprocessor: processes all preprocessor directives, like #INCLUDE, #DEFINE etc...
        -  ´ gcc -E -o main.i main.c ´ generates the preprocessor file
    
    - Generate assembly:
        - ´ gcc -S -o main.s main.c´ this will generate the assembly for the current machine 
    
    - Generate readable machine code:
        - gcc -c -o main.o main.c generates the assembly in binary format for the machine (obj file)
        - we can analyze the object with 'objdmp -d [main.o]' (-d is disassemble, maybe we need to speecify the arch)

    - linker: after the preprocessor and machine code we need to link all object files of my code (main and external functions) 
              to the elf file to generate an executable
        - with a <stdio.h> the preprocessor adds all the files from the standard libraries
### extra commands

- 'size' shows the size of the section of your program
    -
### extra

generate Memory map file

## cross 

- bare metal: means no OS is running on the arch wich i'm using 
    -   ´arm-nono-eabi-gcc [COMMANDS]´ (on fedora:) 
    -   i need to specify all the parts to run my program (!it's a bare metal application) with the 
        linker file and a 'startup.s' to give the starting point of my program

### Makefiles

- add the Makefile to the dependencies, so if the filechanges (EX change in the compiler) it reruns the command

    
