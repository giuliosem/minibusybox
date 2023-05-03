#CC= arm-linux-gnueabihf-gcc
CROSS_COMPILER=
CC=gcc

PATH_CHOWN =chown
PATH_CAT = cat
PATH_CHMOD = chmod
PATH_UNAME = uname
LIB_PATH = lib

REMOTE_USR = debian
REMOTE_HOST = 192.168.7.2
REMOTE_PATH = /home/debian/

OBJ = main.o

.PHONY =all clean install uninstall

all: makes_commads minibusybox

makes_commads:
	@cd $(PATH_CHOWN) && make all
	@cd $(PATH_CAT) && make all
	@cd $(PATH_CHMOD)&& make all
	@cd $(PATH_UNAME) && make all

minibusybox: $(OBJ) makes_commads
	$(CROSS_COMPILER)$(CC) $(OBJ) -o $@ -L$(LIB_PATH) \
		-l$(PATH_UNAME) -l$(PATH_CAT) -l$(PATH_CHMOD) -l$(PATH_CHOWN) \
		-I$(PATH_UNAME) -I$(PATH_CAT) -I$(PATH_CHMOD) -I$(PATH_CHOWN)

main.o: main.c 
	$(CROSS_COMPILER)$(CC) -c main.c

clean:
	rm -f *.o minibusybox lib/*.so
	@cd $(PATH_CAT) && make clean
	@cd $(PATH_CHOWN) && make clean
	@cd $(PATH_CHMOD) && make clean
	@cd $(PATH_UNAME) && make clean

install: all
	@cd $(PATH_CHOWN) && make all
	scp -r lib $(REMOTE_USR)@$(REMOTE_HOST):$(REMOTE_PATH)minilib
	ssh $(REMOTE_USR)@$(REMOTE_HOST) 'echo "export LD_LIBRARY_PATH=$\LD_LIBRARY_PATH:$(REMOTE_PATH)minilib" >> ~/.bashrc && source $(REMOTE_PATH).bashrc'
	scp minibusybox $(REMOTE_USR)@$(REMOTE_HOST):$(REMOTE_PATH)

uninstall:
	ssh $(REMOTE_USR)@$(REMOTE_HOST) 'rm -rf minilib minibusybox'
	ssh $(REMOTE_USR)@$(REMOTE_HOST) "grep -v 'export LD_LIBRARY_PATH=LD_LIBRARY_PATH:/home/debian/minilib' ~/.bashrc > ~/.bashrc.new && mv ~/.bashrc.new ~/.bashrc && source ~/.bashrc"
