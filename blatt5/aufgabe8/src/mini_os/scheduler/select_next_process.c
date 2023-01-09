#include "../mini_os.h"
#include <stdio.h>

struct process *select_next_process(void)
{
	return queue_pop(&ptable.run_queue);
}
