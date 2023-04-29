CC = gcc

PREFIX = /usr/local/bin

.PHONY = all clean install uninstall 

all: minibusybox

minibusybox: minibusybox.o 
	$(CC) -o minibusybox minibusybox.o 

minibusybox.o: minibusybox.c 
	$(CC)  -c minibusybox.c

clean:
	rm -f *.o minibusybox

install: all
	sudo ln -sf $(PWD)/minibusybox $(PREFIX)/my_sleep;
	sudo ln -sf $(PWD)/minibusybox $(PREFIX)/my_uname;
	sudo ln -sf $(PWD)/minibusybox $(PREFIX)/my_mkdir;
	sudo ln -sf $(PWD)/minibusybox $(PREFIX)/my_chmod

uninstall:
	sudo rm -f $(PREFIX)/my_sleep
	sudo rm -f $(PREFIX)/my_uname
	sudo rm -f $(PREFIX)/my_mkdir
	sudo rm -f $(PREFIX)/my_chmod
