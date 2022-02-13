OUTPUT_FORMAT("elf64-x86-64")
ENTRY(start)

SECTIONS
{
    . = 0x400000;

    .text.entry : {
        /home/parallels/Desktop/dolphin2/build/amd64/start.o(.text)
    }

    .text : {
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