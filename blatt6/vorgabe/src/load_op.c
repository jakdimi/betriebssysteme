#include "loader.h"

int
load_op(struct dynop *dest, const char *filename)
{
    void *handle;
    handle = dlopen(filename, 3);
    printf("%p", handle);
    if (!handle) {
        errno = 2;
        perror("Could not open library.");
		return -1;
	}

    struct opfn *symbol;
    symbol = dlsym(handle, "op");
    if (!symbol) {
        errno = 2;
        perror("Could not find \"op\".");
		return -1;
	}

    dest->libhandle = handle;
    dest->op = symbol->op;

    return 0;
}
