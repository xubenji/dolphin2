#The computer architecture. 
export ARCH 	  		 = x86
export PROJECT_DIR		 = $(shell pwd)
export DEBUG_FILE		 = memory.o
export OPTIMIZATION		 = -O0
export VIRTUAL_MEMORY	 = 512

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	