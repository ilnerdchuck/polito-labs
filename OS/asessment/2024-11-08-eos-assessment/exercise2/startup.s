// The .word directive allocates a 32-bit value in the memory. In this case it allocates in memory
// the address of the stack_top (value in the linker.ld file) and _Reset.
.word stack_top     // Address of the stack_top
.word _start        // Address of the _start function

// The thumb_func is used to make sure the function is in thumb mode,
// which is required for the Cortex-M0+.
.thumb_func 

.global _start

_start:
    BL main
    B .
