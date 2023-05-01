CROSS_COMPILER = 
CC =gcc
CFLAGS= -Wall

.PHONY: all clean

all:chown.o

chown.o: chown.c chown.h
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c chown.c -o chown.o
clean:
	rm -rf chown.o
