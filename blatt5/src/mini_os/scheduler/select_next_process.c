#include "../mini_os.h"

struct process *select_next_process(void)
{
	struct process *sel;

	sel = ptable.run_queue.head;

	for (struct process *cur = sel->next; cur ; cur = cur->next) {
		if (cur->process_id > sel->process_id) {
			sel = cur;
		}
	}
	
	queue_remove(sel);
	return sel;
}
