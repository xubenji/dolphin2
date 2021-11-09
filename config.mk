#The computer architecture. 
export ARCH 	  		 = arm
export PROJECT_DIR		 = $(shell pwd)
export DEBUG_FILE		 = put.o
export OPTIMIZATION		 = -O0

BUILD_DIR				 = $(PROJECT_DIR)/boot/	\
						   $(PROJECT_DIR)/kernel/drives/usb/	\
						   $(PROJECT_DIR)/kernel/	\
						   $(PROJECT_DIR)/build/	