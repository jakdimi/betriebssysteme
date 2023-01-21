#include "loader.h"

static int
mul(int a, int b)
{
	return a * b;
}

struct opfn op = {
	.op = mul
};
