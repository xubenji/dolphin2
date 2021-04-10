.PONHY:clean all

#BIN 		= $(BUILD_PATH)/kernel.bin
SRCS 		= $(wildcard *.c)
SRCSASM		= $(wildcard *.$(SUFFIX))
OBJ 	    = $(addprefix $(BUILD_PATH)/,$(SRCS:.c=.o))
OBJ		   += $(addprefix $(BUILD_PATH)/,$(SRCSASM:.$(SUFFIX)=.o))
DEPS 		= $(addprefix $(DEPS_PATH)/,$(SRCS:.c=.d))
OBJS 		= $(wildcard $(BUILD_PATH)/*.o)

ifeq ($(ARCH),x86)
CC 			= gcc 
COPS		= -I$(HEAD_PATH) -g -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone
ASMOPS		= -I$(HEAD_PATH)
LD 			= ld 
LDOPS 		= -nostdlib -T $(PROJECT_DIR)/link/lds/link_x86.lds -o
KERNEL_ELF  = kernel8.elf
OBJCOPY 	= objcopy -O binary
endif

ifeq ($(ARCH),arm)
CC			= aarch64-elf-gcc
COPS 		= -Wall -nostdlib -nostartfiles -ffreestanding -I$(HEAD_PATH) -mgeneral-regs-only
ASMOPS		= -I$(HEAD_PATH)
LD			= aarch64-elf-ld
LDOPS 		= -T $(PROJECT_DIR)/link/lds/link_arm.lds -o
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
	gcc -I$(HEAD_PATH) -MM $(filter %.c,$^) | sed 's,\(.*\)\.o[ :]*,$(BUILD_PATH)/\1.o $@:,g' > $@

-include $(DEPS)

$(BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(KERNEL_ELF) $(BIN)

$(KERNEL_ELF): $(OBJS)
	$(LD) $(LDOPS) $@ $^

$(BUILD_PATH)/%.o: %.c 
	$(CC) $(COPS) -o $@ -c $(filter %.c,$^)

$(BUILD_PATH)/%.o: %.$(SUFFIX) 
	$(CC) $(ASMOPS) -o $@ -c $(filter %.$(SUFFIX),$^)

