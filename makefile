#ifeq ($(DEBUG),"true")
#CC = gcc -g
.PONHY:clean all

CC = gcc -I$(HEAD_PATH)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
OBJ_DIR = $(BUILD_DIR)/build
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))
OBJ = $(wildcard $(OBJ_DIR)/*.o)
DEP_DIR = $(BUILD_DIR)/build/link
DEPS := $(addprefix $(DEP_DIR)/,$(DEPS))
BIN := $(addprefix $(BUILD_DIR)/,$(BIN))


all: $(DEPS) $(BIN) $(OBJS)

ifneq ("$(wildcard $(DEPS"))","")
include $(DEPS)
endif

$(BIN):$(OBJ)
	$(CC) -o $@ $^ 

#usb.o:usb.c usb.h 
$(OBJ_DIR)/%.o:%.c 
	$(CC) -o $@ -c $(filter %.c,$^)

$(DEP_DIR)/%.d:%.c 
	gcc -MM $^ | sed 's,\(.*\).o[ :]*,$(OBJ_DIR)/\1.o $@:.g' > $@



#hello:helloworld.o
#	gcc -o hello helloworld.o
#helloworld.o:helloworld.c
#	gcc -o helloworld.o -c helloworld.c 

#clean:
	#rm mp3 *.o *.d 
