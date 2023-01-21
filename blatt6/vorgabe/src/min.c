#include "loader.h"

static int
min(int a, int b)
{
	return (a < b) ? a : b;
}

struct opfn op = {
	.op = min
};
