export DEPS_PATH  	 			 = $(PROJECT_DIR)/link
export MKFILE_PATH_COMMON  		 = $(PROJECT_DIR)/source/common.mk
export MKFILE_PATH_BOOT 		 = $(PROJECT_DIR)/source/boot.mk
export MKFILEFLAGS 				 += --no-print-directory
export HEAD_PATH 		      	 = $(PROJECT_DIR)/include
include config.mk

ifeq ($(ARCH),x86)
	AARCH					= aarch/amd64
	BUILD_PATH				= $(PROJECT_DIR)/build/amd64
	SUFFIX					= asm
	RUNNING_INSTURCTION     = qemu-system-x86_64 -cpu Skylake-Server -m 512 -hda $(BUILD_PATH)/boot.img -boot d
	DEBUG					= qemu-system-x86_64 -cpu Skylake-Server -m 512 -hda $(BUILD_PATH)/boot.img -boot d -s -S 
endif
ifeq ($(ARCH),arm)
	AARCH					= aarch/arm
	BUILD_PATH				= $(PROJECT_DIR)/build/arm
	SUFFIX					= S
	RUNNING_INSTURCTION		= qemu-system-aarch64 -M raspi3 -kernel $(BUILD_PATH)/kernel8.img -serial stdio 
	DEBUG					= qemu-system-aarch64 -M raspi3 -kernel $(BUILD_PATH)/kernel8.img -serial stdio -s -S 
endif

export AARCH
export BUILD_PATH
export SUFFIX

all:
	@for dir in $(BUILD_DIR);	\
	do	\
		make -C $$dir;	\
	done

run:all
	$(RUNNING_INSTURCTION)

debug:all
	$(DEBUG)

clean:
	rm -rf link/*.d \
	$(PROJECT_DIR)/build/*/*.bin \
	$(PROJECT_DIR)/build/*/*.elf \
	$(PROJECT_DIR)/build/*/*.o \
	$(PROJECT_DIR)/build/*/boot/*.bin \
	$(PROJECT_DIR)/build/*/*.d \
	$(PROJECT_DIR)/build/*/kernel8.img \
	$(PROJECT_DIR)/file/* 
	