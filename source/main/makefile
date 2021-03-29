.PONHY:clean all

#BIN 		= $(BUILD_PATH)/kernel.bin
SRCS 		= $(wildcard *.c)
SRCSASM		= $(wildcard *.asm)
OBJ 	    = $(addprefix $(BUILD_PATH)/,$(SRCS:.c=.o))
OBJ		   += $(addprefix $(BUILD_PATH)/,$(SRCSASM:.asm=.o))
DEPS 		= $(addprefix $(DEPS_PATH)/,$(SRCS:.c=.d))
OBJS 		= $(wildcard $(BUILD_PATH)/*.o)

CC 			= gcc -I$(HEAD_PATH) -g -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone  
LD 			= ld -nostdlib -T link.lds -o
KERNEL_ELF  = kernel8.elf
OBJCOPY 	= objcopy -O binary

all: $(BIN) $(OBJ)

$(DEPS_PATH)/%.d:%.c
	gcc -I$(HEAD_PATH) -MM $(filter %.c,$^) | sed 's,\(.*\)\.o[ :]*,$(BUILD_PATH)/\1.o $@:,g' > $@

-include $(DEPS)

$(BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(KERNEL_ELF) $(BIN)

$(KERNEL_ELF): $(OBJS)
	$(LD) $@ $^


$(BUILD_PATH)/%.o: %.c 
	$(CC) -o $@ -c $(filter %.c,$^)

run:
	./build/kernel.bin

clean:
	rm -rf build/*.o build/kernel.bin
