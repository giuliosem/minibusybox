CROSS_COMPILER =
CC =gcc
CFLAGS= -Wall

.PHONY: all clean

all:chmod.o

chmod.o: chmod.h chmod.c
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c chmod.c -o chmod.o

clean:
	rm -rf chmod.o

