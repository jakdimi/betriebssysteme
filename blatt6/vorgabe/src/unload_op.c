#include "loader.h"

void
unload_op(struct dynop *op)
{
    dlclose(op->libhandle);

    // "Aufräumen"...
    op->libhandle = NULL;
    op->op = NULL;
}
