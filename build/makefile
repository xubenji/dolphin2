BIN			= kernel.bin

dd:bootdd
	dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc 

bootdd:all
	make -C boot
	
include $(MKFILE_PATH)/makefile