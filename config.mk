#The computer architecture. 
export ARCH 	  		 = x86
export PROJECT_DIR		 = $(shell pwd)
export DEBUG_FILE		 = put.o

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	