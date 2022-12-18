#include "../mini_os.h"

void *
get_arg(void)
{
	return ptable.running->arg;
}
