#The computer architecture. 
export ARCH 	  		 = arm
export PROJECT_DIR		 = $(shell pwd)
export DEBUG_FILE		 = printk.o
export OPTIMIZATION		 = -O0
export VIRTUAL_MEMORY	 = 512

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	