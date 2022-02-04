BIN			= kernel.bin

cp:dd
	cp boot.img ../../file/ 
	cp kernel8.elf ../../file/
	$(OBJDUMP) $(DISASSEMBLY) > $(PROJECT_DIR)/file/debug.asm
dd:bootdd
	dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc 

bootdd:all
	make -C boot
	
include $(MKFILE_PATH_COMMON)

