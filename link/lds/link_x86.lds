OUTPUT_FORMAT("elf64-x86-64")
ENTRY(start)

SECTIONS
{
    . = 0xffff800000400000;

    .text : {
        KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*)
       *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    . = ALIGN(16);
    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}