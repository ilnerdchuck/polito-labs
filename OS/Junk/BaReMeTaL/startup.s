.word stack_top     
.word _start        
.thumb_func 

# .syntax unified
.global _start

_start:
    BL _yourcode
    B .

