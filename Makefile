#CC= arm-linux-gnueabihf-gcc
CROSS_COMPILER=
CC=gcc
PREFIX =/usr/local/bin

PATH_CHOWN =./chown/
PATH_CAT =./cat/
PATH_CHMOD =./chmod/
PATH_UNAME =./uname/

OBJ =$(PATH_CHOWN)chown.o $(PATH_CAT)cat.o $(PATH_CHMOD)chmod.o $(PATH_UNAME)uname.o main.o

.PHONY =all clean install uninstall

all: makes_commads minibusybox

makes_commads:
	@cd $(PATH_CHOWN) && make all
	@cd $(PATH_CAT) && make all
	@cd $(PATH_CHMOD)&& make all
	@cd $(PATH_UNAME) && make all

minibusybox: $(OBJ)
	$(CROSS_COMPILER)$(CC) $(OBJ) -o minibusybox 

main.o: main.c 
	$(CROSS_COMPILER)$(CC) -c main.c

clean:
	rm -f *.o minibusybox
	@cd $(PATH_CAT) && make clean
	@cd $(PATH_CHOWN) && make clean
	@cd $(PATH_CHMOD) && make clean
	@cd $(PATH_UNAME) && make clean

install: 
	scp minibusybox debian@192.168.7.2:/home/debian

uninstall:

