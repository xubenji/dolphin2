BIN = kernel8.img

disassembly:cp
	$(OBJDUMP) $(DISASSEMBLY) > $(PROJECT_DIR)/file/debug.S

cp:all
	cp kernel8.elf $(PROJECT_DIR)/file/
	cp kernel8.img $(PROJECT_DIR)/file/

include $(MKFILE_PATH_COMMON)