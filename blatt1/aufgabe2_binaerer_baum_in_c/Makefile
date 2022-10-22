CC=gcc
CFLAGS=-Wall -Werror -pedantic-errors -ggdb -std=c99

OBJS = tree.o main.o

all: tree

tree: $(OBJS) 
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $(OBJS)

tree.o: tree.h tree.c
	$(CC) $(CFLAGS) $(CLIBS) -c tree.c
	
main.o: tree.h main.c 
	$(CC) $(CFLAGS) $(CLIBS) -c main.c

clean:
	-rm *.o *~ tree

.PHONY: tags

tags:
	ctags *.[ch]

