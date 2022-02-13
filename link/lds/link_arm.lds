ENTRY(start)
SECTIONS
{
    . = 0x80000;

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
        bss_start = .;
        *(.bss)
        bss_end = .;
    }
}