#include "loader.h"

static int
concat(int a, int b)
{
    char str1[12];
    char str2[12];
    sprintf(str1, "%d", a);
    sprintf(str2, "%d", b);
	return atoi(strcat(str1, str2));
}

struct opfn op = {
	.op = concat
};
