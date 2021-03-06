.PHONY:compiler clean

export BUILD_DIR = $(shell pwd)
export HEAD_PATH = $(BUILD_DIR)/inc

#OBJ_DIR = /root/dolphin2/build
#ifneq ("$(wildcard $(OBJ_DIR)/*.o)","")
#BIN = mp3
#include ./makefile.co 
#endif


compiler:
	make -C lcd
	make -C media
	make -C usb
	make -C app
	make -C build

BIN = mp3
include ./makefile.co 


clean:
	rm -fr app/*.o app/mp3  app/*.d
	rm -fr usb/*.o usb/*.d
	rm -fr lcd/*.o lcd/*.d
	rm -fr media/*.o media/*.d
	rm -fr mp3
	rm -fr build/*.o
