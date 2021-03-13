export PROJECT_DIR = $(shell pwd)
export HEAD_PATH   = $(PROJECT_DIR)/include
export BUILD_PATH  = $(PROJECT_DIR)/build
export AARCH 	   = aarch/amd64
export DEPS_PATH   = $(PROJECT_DIR)/link

all:
	make -C $(PROJECT_DIR)/kernel/drives/audio
	make -C $(PROJECT_DIR)/kernel/drives/hardisk
	make -C $(PROJECT_DIR)/kernel/drives/usb
	make -C $(PROJECT_DIR)/kernel
	make -C $(PROJECT_DIR)/build

run:
	./build/kernel.bin

clean:
	rm -rf build/*.o build/kernel.bin