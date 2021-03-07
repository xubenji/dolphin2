.PONHY:clean all

PROJECT_DIR = $(shell pwd)
HEAD_PATH = $(PROJECT_DIR)/include
#OBJS = $(wildcard build/*.o)
OBJS = build/audio_aarch.o build/audio.o build/hardisk.o build/hardisk_aarch.o build/usb.o build/usb_aarch.o build/kernel.o 
CC = gcc -I$(HEAD_PATH)

all: build/kernel.bin

build/kernel.bin: $(OBJS)
	gcc -o $@ $^

build/audio_aarch.o:$(PROJECT_DIR)/kernel/drives/audio/aarch/amd64/audio_drive.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/audio.o:$(PROJECT_DIR)/kernel/drives/audio/audio.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/hardisk_aarch.o:$(PROJECT_DIR)/kernel/drives/hardisk/aarch/amd64/hardisk_drive.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/hardisk.o:$(PROJECT_DIR)/kernel/drives/hardisk/hardisk.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/usb_aarch.o:$(PROJECT_DIR)/kernel/drives/usb/aarch/amd64/usb_drive.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/usb.o:$(PROJECT_DIR)/kernel/drives/usb/usb.c
	$(CC) -o $@ -c $(filter %.c,$^)

build/kernel.o:$(PROJECT_DIR)/kernel/kernel.c 
	$(CC) -o $@ -c $(filter %.c,$^)

build/audio_aarch.o:$(PROJECT_DIR)/kernel/drives/audio/aarch/amd64/audio_drive.c $(HEAD_PATH)/audio_drive.h
build/audio.o:$(PROJECT_DIR)/kernel/drives/audio/audio.c $(HEAD_PATH)/audio.h

build/hardisk_aarch.o:$(PROJECT_DIR)/kernel/drives/hardisk/aarch/amd64/hardisk_drive.c $(HEAD_PATH)/hardisk_drive.h 
build/hardisk.o:$(PROJECT_DIR)/kernel/drives/hardisk/hardisk.c $(HEAD_PATH)/hardisk.h 

build/usb_aarch.o:$(PROJECT_DIR)/kernel/drives/usb/aarch/amd64/usb_drive.c $(HEAD_PATH)/usb_drive.h 
build/usb.o:$(PROJECT_DIR)/kernel/drives/usb/usb.c $(HEAD_PATH)/usb.h 


clean:
	rm -rf build/*.o build/kernel.bin