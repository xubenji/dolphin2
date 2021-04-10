all:
	dd if=boot.bin of=../boot.img bs=512 count=1 conv=notrunc
	dd if=load.bin of=../boot.img bs=512 count=5 seek=1 conv=notrunc