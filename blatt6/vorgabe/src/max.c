#include "loader.h"

static int
max(int a, int b)
{
	return (a > b) ? a : b;
}

struct opfn op = {
	.op = max
};
