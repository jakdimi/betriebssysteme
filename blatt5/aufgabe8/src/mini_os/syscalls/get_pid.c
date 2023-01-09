#include "../mini_os.h"

int
get_pid(void)
{
	return ptable.running->process_id;
}
