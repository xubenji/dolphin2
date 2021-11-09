.PONHY:clean all

#BIN 		= $(BUILD_PATH)/kernel.bin
SRCS 		= $(wildcard *.c)
SRCSASM		= $(wildcard *.$(SUFFIX))
OBJ 	    = $(addprefix $(BUILD_PATH)/,$(SRCS:.c=.o))
OBJ		   += $(addprefix $(BUILD_PATH)/,$(SRCSASM:.$(SUFFIX)=.o))
DEPS 		= $(addprefix $(DEPS_PATH)/,$(SRCS:.c=.d))
OBJS 		= $(wildcard $(BUILD_PATH)/*.o)

ifeq ($(ARCH),x86)
NASM 		= nasm
ASM_FLAGS   = -f elf64 -F dwarf
CC 			= gcc 
COPS		= -I$(HEAD_PATH) -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -w -g $(OPTIMIZATION)
ASMOPS		= -I$(HEAD_PATH)
LD 			= ld 
#时刻要注意init.o是不是第一个被链接
LDOPS 		= -nostdlib -T $(PROJECT_DIR)/link/lds/link_x86.lds -o
KERNEL_ELF  = kernel8.elf
OBJCOPY 	= objcopy -O binary
DISASSEMBLY = -j .text -l -C -S -d -mi386:x86-64:intel $(DEBUG_FILE) $(PROJECT_DIR)/build/amd64/$(KERNEL_ELF) 
endif

ifeq ($(ARCH),arm)
CC			= aarch64-elf-gcc
#CC			= aarch64-linux-gnu-gcc
#COPS 		= -Wall $(OPTIMIZATION) -nostdlib -nostartfiles -ffreestanding -I$(HEAD_PATH) -g -fno-stack-protector -nostdinc -c
COPS 		= -Wall $(OPTIMIZATION) -nostdlib -nostartfiles -ffreestanding -I$(HEAD_PATH) -g -fno-stack-protector -c -w
#-mgeneral-regs-only
ASMOPS		= -I$(HEAD_PATH)
LD			= aarch64-elf-ld
#LD			= aarch64-linux-gnu-ld
LDOPS 		= -nostdlib -nostartfiles -T $(PROJECT_DIR)/link/lds/link_arm.lds -o
KERNEL_ELF  = kernel8.elf
OBJCOPY 	= aarch64-elf-objcopy -O binary
endif

export CC
export COPS
export ASMOPS
export LD
export LDOPS
export KERNEL_ELF
export OBJCOPY

all: $(BIN) $(OBJ)

$(DEPS_PATH)/%.d:%.c
	$(CC) -I$(HEAD_PATH) -MM $(filter %.c,$^) | sed 's,\(.*\)\.o[ :]*,$(BUILD_PATH)/\1.o $@:,g' > $@

-include $(DEPS)

$(BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(KERNEL_ELF) $(BIN)

$(KERNEL_ELF): $(OBJS)
	$(LD) $(LDOPS) $@ $^

$(BUILD_PATH)/%.o: %.c 
	$(CC) $(COPS) -o  $@ -c $(filter %.c,$^) 

$(BUILD_PATH)/%.o: %.$(SUFFIX) 
	$(CC) $(ASMOPS) -o $@ -c $(filter %.$(SUFFIX),$^)

$(BUILD_PATH)/%.o: %.asm
	$(NASM) $(ASM_FLAGS) -o $@ $^

