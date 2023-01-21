#include "loader.h"

int
reduce(int *dest, const int *values, size_t count, int op(int a, int b))
{
    if (count == 0) {
        errno = EINVAL;
        perror("Could not reduce empty array.");
        return -1;
    }

    int res = *values;
    for (int i = 1; i < (int) count; i++) {
        res = op(res, i[values]);
    }
    *dest = res;

    return 0;
}
