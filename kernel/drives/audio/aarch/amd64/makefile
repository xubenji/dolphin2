#BIN = 

#include $(PROJECT_DIR)/make/makefile

CC = gcc -I/root/udemy/include



all: /root/udemy/build/audio_drive.o 

audio_drive.o: audio_drive.c audio_drive.h 

/root/udemy/build/audio_drive.o: audio_drive.c 
	$(CC) -o $@ -c $(filter %.c,$^) 

