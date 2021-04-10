.PONHY:all

SRCSASM 		= $(wildcard *.$(SUFFIX))
BINS			= $(wildcard *.bin)
BUILD_PATH_BOOT = $(BUILD_PATH)/boot
BIN 	    	= $(addprefix $(BUILD_PATH_BOOT)/,$(SRCSASM:.$(SUFFIX)=.bin)) 
NASM 			= nasm

all:$(BIN)

$(BUILD_PATH_BOOT)/%.bin:%.$(SUFFIX)
	$(NASM) -f bin -o $@ $^

#$(IMG):$(BINS)
	#dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc
	#dd if=load.bin of=boot.img bs=512 count=5 seek=1 conv=notrunc
	#dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc