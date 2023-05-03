CROSS_COMPILER =
CC =gcc
CFLAGS= -Wall
LDFLAGS = -fPIC

LIB = cat
SHLIB_NAME = lib$(LIB).so

.PHONY: all clean

all: $(SHLIB_NAME)

$(SHLIB_NAME): $(LIB).o
	$(CROSS_COMPILER)$(CC) $(LDFLAGS) -shared $< -o ../lib/$@

$(LIB).o: $(LIB).c $(LIB).h 
	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o 

