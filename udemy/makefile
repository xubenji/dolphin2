.PONHY:clean all

OBJ = build/audio_aarch.o build/audio.o build/hardisk_aarch.o build/hardisk.o build/usb_aarch.o build/usb.o build/kernel.o

all: build/kernel.bin

build/kernel.bin: $(OBJ)
	gcc -o $@ $^

build/audio_aarch.o:kernel/drives/audio/aarch/amd64/audio_drive.c
	gcc -o $@ -c $(filter %.c,$^)

build/audio.o:kernel/drives/audio/audio.c
	gcc -o $@ -c $(filter %.c,$^)

build/hardisk_aarch.o:kernel/drives/hardisk/aarch/amd64/hardisk_drive.c
	gcc -o $@ -c $(filter %.c,$^)

build/hardisk.o:kernel/drives/hardisk/hardisk.c
	gcc -o $@ -c $(filter %.c,$^)

build/usb_aarch.o:kernel/drives/usb/aarch/amd64/usb_drive.c
	gcc -o $@ -c $(filter %.c,$^)

build/usb.o:kernel/drives/usb/usb.c
	gcc -o $@ -c $(filter %.c,$^)

build/kernel.o:kernel/kernel.c 
	gcc -o $@ -c $(filter %.c,$^)

build/audio_aarch.o:kernel/drives/audio/aarch/amd64/audio_drive.c kernel/drives/audio/audio_drive.h
build/audio.o:kernel/drives/audio/audio.c kernel/drives/audio/audio.h kernel/drives/audio/audio_drive.h

build/hardisk_aarch.o:kernel/drives/hardisk/aarch/amd64/hardisk_drive.c kernel/drives/hardisk/hardisk_drive.h 
build/hardisk.o:kernel/drives/hardisk/hardisk.c kernel/drives/hardisk/hardisk.h 

build/usb_aarch.o:kernel/drives/usb/aarch/amd64/usb_drive.c kernel/drives/usb/usb_drive.h 
build/usb.o:kernel/drives/usb/usb.c kernel/drives/usb/usb.h 


clean:
	rm -rf build/*.o build/kernel.bin