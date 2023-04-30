CROSS_COMPILER = arm-linux-gnueabihf-
CC = gcc

CFLAGS = -Wall

.PHONY: all clean

all:Make_cat Test


Make_cat:
	cd ./ComandoCat/ && make

Test: Test.o ./ComandoCat/cat.o
	$(CROSS_COMPILER)$(CC) $(CFLAGS) Test.o ./ComandoCat/cat.o -o Test

Test.o: Test.c
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c Test.c -o Test.o

clean:
	rm -rf Test Test.o 
	cd ./ComandoCat/ && make clean

