export PROJECT_DIR		 = $(shell pwd)
export HEAD_PATH 	 	 = $(PROJECT_DIR)/include
export BUILD_PATH	 	 = $(PROJECT_DIR)/build
export AARCH 	  		 = aarch/amd64
export DEPS_PATH  	 	 = $(PROJECT_DIR)/link
export MKFILE_PATH   	 = $(PROJECT_DIR)/source/main
export MKFILE_PATH_BOOT  = $(PROJECT_DIR)/source/boot
export MKFILEFLAGS 		 += --no-print-directory

all:
	@make -C $(PROJECT_DIR)/boot/
	@make -C $(PROJECT_DIR)/kernel/drives/audio
	@make -C $(PROJECT_DIR)/kernel/drives/hardisk
	@make -C $(PROJECT_DIR)/kernel/drives/usb
	@make -C $(PROJECT_DIR)/kernel
	@make -C $(PROJECT_DIR)/build

run:all
	qemu-system-x86_64 -cpu Skylake-Server -m 1024 -hda ./build/boot.img -boot d

s:all
	qemu-system-x86_64 -cpu Skylake-Server -m 1024 -hda ./build/boot.img -boot d -s -S

clean:
	rm -rf build/*.o build/*.bin link/*.d build/boot/*.bin
	