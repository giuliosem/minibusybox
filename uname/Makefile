CROSS_COMPILER = 
CC =gcc
CFLAGS= -Wall

.PHONY: all clean

all:uname.o

uname.o: uname.h uname.c
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c uname.c -o uname.o
clean:
	rm -rf uname.o

