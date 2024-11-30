ENTRY(_start)

SECTIONS
{
    .text : { *(.text*) } 		
    .data : { *(.data) }
    .bss : { *(.bss*) }
    stack_top = 0x2001ffff;
}


