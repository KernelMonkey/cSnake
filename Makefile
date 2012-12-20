CC = gcc
SRCDIR = src/
INCDIR = include/
CFLAGS = -Wall -O3 -I$(INCDIR)
LFLAGS = -lncurses

all:
	$(CC) $(CFLAGS) -c $(SRCDIR)cSnake.c $(LFLAGS)
	$(CC) $(CFLAGS) $(SRCDIR)main.c *.o -o cSnake $(LFLAGS)

clean:
	rm *.o *.txt cSnake

install:
	cp cSnake /usr/local/bin

uninstall:
	rm /usr/local/bin/cSnake
