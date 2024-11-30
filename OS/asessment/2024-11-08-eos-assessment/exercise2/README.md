# Exercise 2 - baremetal C programming and inline assembly

Write a baremetal C programm `main.c`that can be executed using qemu on ARM V7 to be executed on qemu-arm. The program is based on the following project:

```
├── Makefile
├── README.md
├── library.c
├── linker.ld
├── main.c
└── startup.s
```

The program must have the following specifications:

* It contains only the main function that defines an array of integers `v` of 10 integers
* Two integer variables `min` and `max`
* An inline assembly block that computes the min and max of the array and store the values into `min` and `max`
* The result must be printed using the provided  `my_printf` function


Use the ARM v7 ISA reference list: [https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions](https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions)