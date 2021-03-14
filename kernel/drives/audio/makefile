BIN = 

compiler:all
	make -C $(AARCH)

CC = gcc -I/root/udemy/include

all: /root/udemy/build/audio.o 

audio.o: audio.c audio_drive.h audio.h 

/root/udemy/build/audio.o: audio.c 
	$(CC) -o $@ -c $(filter-out audio_drive.h audio.h,$^) 
	

#include $(PROJECT_DIR)/make/makefile
