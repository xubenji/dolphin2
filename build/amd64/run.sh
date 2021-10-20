

#ld -nostdlib -T link_x86.lds -o kernel.elf print_amd64.o kernel.o init.o trapa.o trap.o
#ld -nostdlib -T link_x86.lds -o kernel.elf kernel.o main.o trapa.o trap.o print_amd64.o
#ld -nostdlib -T link_x86.lds -o kernel8.elf kernel.o main.o trapa.o trap.o liba.o print.o debug.o memory.o


#objcopy -O binary kernel.elf kernel.bin

dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc

qemu-system-x86_64 -cpu Skylake-Server -m 512 -hda boot.img -boot d

