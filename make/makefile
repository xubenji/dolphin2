.PONHY:clean all

#BIN 		= $(BUILD_PATH)/kernel.bin
SRCS 		= $(wildcard *.c)
OBJ 	    = $(addprefix $(BUILD_PATH)/,$(SRCS:.c=.o))  
DEPS 		= $(addprefix $(DEPS_PATH)/,$(SRCS:.c=.d))
OBJS 		= $(wildcard $(BUILD_PATH)/*.o)
#OBJS = build/audio_aarch.o build/audio.o build/hardisk.o build/hardisk_aarch.o build/usb.o build/usb_aarch.o build/kernel.o 
CC = gcc -I$(HEAD_PATH) -g 

all: $(BIN) $(OBJ)
	
-include $(DEPS)

$(BIN): $(OBJS)
	gcc -o $@ $^

$(BUILD_PATH)/%.o: %.c 
	$(CC) -o $@ -c $(filter %.c,$^)


#build/audio_aarch.o:$(PROJECT_DIR)/kernel/drives/audio/aarch/amd64/audio_drive.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/audio.o:$(PROJECT_DIR)/kernel/drives/audio/audio.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/hardisk_aarch.o:$(PROJECT_DIR)/kernel/drives/hardisk/aarch/amd64/hardisk_drive.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/hardisk.o:$(PROJECT_DIR)/kernel/drives/hardisk/hardisk.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/usb_aarch.o:$(PROJECT_DIR)/kernel/drives/usb/aarch/amd64/usb_drive.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/usb.o:$(PROJECT_DIR)/kernel/drives/usb/usb.c
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/kernel.o:$(PROJECT_DIR)/kernel/kernel.c 
#	$(CC) -o $@ -c $(filter %.c,$^)

#build/audio_aarch.o:$(PROJECT_DIR)/kernel/drives/audio/aarch/amd64/audio_drive.c $(HEAD_PATH)/audio_drive.h
#build/audio.o:$(PROJECT_DIR)/kernel/drives/audio/audio.c $(HEAD_PATH)/audio.h $(HEAD_PATH)/audio_drive.h

#build/hardisk_aarch.o:$(PROJECT_DIR)/kernel/drives/hardisk/aarch/amd64/hardisk_drive.c $(HEAD_PATH)/hardisk_drive.h 
#build/hardisk.o:$(PROJECT_DIR)/kernel/drives/hardisk/hardisk.c $(HEAD_PATH)/hardisk.h 

#build/usb_aarch.o:$(PROJECT_DIR)/kernel/drives/usb/aarch/amd64/usb_drive.c $(HEAD_PATH)/usb_drive.h 
#build/usb.o:$(PROJECT_DIR)/kernel/drives/usb/usb.c $(HEAD_PATH)/usb.h 

run:
	./build/kernel.bin

clean:
	rm -rf build/*.o build/kernel.bin
