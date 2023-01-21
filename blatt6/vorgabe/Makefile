.PHONY: all clean folder

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -Werror -std=c99 -fPIC
# Add flags for debugging
CFLAGS += -O0 -g

REDUCE_OBJS := obj/loader.o obj/load_op.o obj/reduce.o obj/unload_op.o
LIBS := lib/add.so lib/max.so lib/min.so lib/mul.so lib/concat.so

all: folder reduce $(LIBS)

folder:
	mkdir obj lib

obj/%.o: src/%.c src/loader.h
	$(CC) $(CFLAGS) -o $@ -c $<

reduce: $(REDUCE_OBJS)
	$(CC) -o $@ $^ -ldl

lib/%.so: src/%.c src/loader.h
	$(CC) $(CFLAGS) -shared -Wl,-soname,$(subst lib/,,$@) -o $@ $<

clean:
	rm -rf obj lib reduce
