BIN = 

compiler:all
	make -C $(AARCH)

CC = gcc -I$(BUILD_PATH)

all: $(BUILD_PATH)/audio.o 

audio.o: audio.c audio_drive.h audio.h 

$(BUILD_PATH)/audio.o: audio.c 
	$(CC) -o $@ -c $(filter-out audio_drive.h audio.h,$^) 
	

#include $(PROJECT_DIR)/make/makefile
