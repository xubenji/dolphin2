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
	RUNNING_INSTURCTION     = qemu-system-x86_64 -cpu Skylake-Server -m 1024 -hda $(BUILD_PATH)/boot.img -boot d
	DEBUG					= qemu-system-x86_64 -cpu Skylake-Server -m 1024 -hda $(BUILD_PATH)/boot.img -boot d -s -S
endif
ifeq ($(ARCH),arm)
	AARCH					= aarch/arm
	BUILD_PATH				= $(PROJECT_DIR)/build/arm
	SUFFIX					= S
	RUNNING_INSTURCTION		= qemu-system-aarch64 -M raspi3 -kernel $(BUILD_PATH)/kernel8.img -serial null -serial stdio
	DEBUG					= qemu-system-aarch64 -M raspi3 -kernel $(BUILD_PATH)/kernel8.img -serial null -serial stdio -s -S
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

d:all
	$(DEBUG)

clean:
	rm -rf link/*.d \
	$(PROJECT_DIR)/build/amd64/*.bin \
	$(PROJECT_DIR)/build/arm/*.bin \
	$(PROJECT_DIR)/build/amd64/*.elf \
	$(PROJECT_DIR)/build/arm/*.elf \
	$(PROJECT_DIR)/build/amd64/*.o \
	$(PROJECT_DIR)/build/arm/*.o \
	$(PROJECT_DIR)/build/amd64/boot/*.bin \
	$(PROJECT_DIR)/build/arm/boot/*.bin \
	$(PROJECT_DIR)/build/amd64/*.d \
	$(PROJECT_DIR)/build/arm/*.d \
	$(PROJECT_DIR)/build/amd64/kernel8.img \
	$(PROJECT_DIR)/build/arm/kernel8.img \
	$(PROJECT_DIR)/file/* 
	