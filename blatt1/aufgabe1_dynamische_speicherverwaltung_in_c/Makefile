CC=gcc
CFLAGS=-Wall -Werror -pedantic-errors -ggdb -std=c99

OBJS = leaking_program.o main.o monitoring_alloc.o

all: leaking_program

leaking_program: $(OBJS) 
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $(OBJS)

leaking_program.o: leaking_program.h leaking_program.c
	$(CC) $(CFLAGS) $(CLIBS) -c leaking_program.c
	
monitoring_alloc.o: monitoring_alloc.h monitoring_alloc.c
	$(CC) $(CFLAGS) $(CLIBS) -c monitoring_alloc.c -o monitoring_alloc.o

main.o: main.c 
	$(CC) $(CFLAGS) $(CLIBS) -c main.c

clean:
	-rm *.o *~ leaking_program

.PHONY: tags

tags:
	ctags *.[ch]

