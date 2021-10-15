OUTPUT_FORMAT("elf64-x86-64")
ENTRY(start)

SECTIONS
{
    . = 0x200000;
#貌似是要使用绝对路径不知道为啥
    .text.entry : {
        /root/benjixu/dolphin2/build/amd64/start.o(.text)
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