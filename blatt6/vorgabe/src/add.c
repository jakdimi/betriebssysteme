#include "loader.h"

static int
add(int a, int b)
{
	return a + b;
}

struct opfn op = {
	.op = add
};
