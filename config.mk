#x86 or arm
export ARCH 	  		 = x86
export PROJECT_DIR		 = $(shell pwd)

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	