# Exercise 1 - bare metal assembly program

Write an ARM assembly program that computes the product of the elements of an array of 32bit integers stored in memory. Store the result in a specific memory location.

Specifications:

* The array of integers is stored in memory at an address identified by the label `v_int`.
* The number of elements in the array is stored in memory at an address identified by the label `n`
* The result is stored in memory at an address identified by the label `res`

Test your code using the online emulator: [https://cpulator.01xz.net/?sys=arm](https://cpulator.01xz.net/?sys=arm)

Use the ARM v7 ISA reference list: [https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions](https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions)

Save your code in `startup.s`
