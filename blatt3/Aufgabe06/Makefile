CC=gcc
CFLAGS=-Wall -Werror -pedantic-errors -ggdb -std=c99 -Wextra

all: client timeServer

client: client.c message.h
	$(CC) $(CFLAGS) $(CLIBS) -o $@ client.c

timeServer: timeServer.c message.h
	$(CC) $(CFLAGS) $(CLIBS) -o $@ timeServer.c
	
clean:
	-rm *~ client timeServer

.PHONY: tags

tags:
	ctags *.[ch]

