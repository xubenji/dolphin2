#The computer architecture. 
export target 	  		 = x86
export PROJECT_DIR		 = $(shell pwd)
export DEBUG_FILE		 = memory.o
export OPTIMIZATION		 = -O0
export VIRTUAL_MEMORY	 = 1024

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	