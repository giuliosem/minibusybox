CROSS_COMPILER=arm-linux-gnueabihf-
CC = gcc

CFLAGS = -Wall

.PHONY: all clean

all:cat.o

cat.o: cat.h cat.c
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c cat.c -o cat.o

clean:
	rm -rf cat.o

