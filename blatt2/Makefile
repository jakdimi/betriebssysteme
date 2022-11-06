.PHONY: all clean

OBJS := mmu_proof.o
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -O0 -g
CC := gcc

all: mmu_proof

clean:
	rm -f mmu_proof $(OBJS)

mmu_proof: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<