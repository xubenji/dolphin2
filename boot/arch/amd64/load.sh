nasm -f elf load.o load.asm

ld -m elf_i386  -N  -o ../kernel8.elf load.o -Map kernel.map
