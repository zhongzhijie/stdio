
APP_NAME = iotest
APP_OBJS = iotest.o
CC = gcc
INC = ./
CFLAG += -g
CFLAG += -DSTD_STREAM -DFILE_STREAM

.PHONY : all

all : $(APP_NAME)

$(APP_NAME) : $(APP_OBJS)
	$(CC) $(CFLAG) $(APP_OBJS) -o $(APP_NAME)
	
%.o : %.c
	$(CC) -c $(CFLAG) $^ -o $@

.PHONY : clean

clean :
	rm -f .o
	rm -f $(APP_NAME) $(APP_OBJS)