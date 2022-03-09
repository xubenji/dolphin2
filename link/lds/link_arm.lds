ENTRY(start)
SECTIONS
{
    . = 0xffff000000080000;

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

    end = .;
}