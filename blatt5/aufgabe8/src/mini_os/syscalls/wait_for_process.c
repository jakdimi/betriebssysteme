#include <stdio.h>
#include "../mini_os.h"

void
wait_for_process(int pid)
{
	disable_interrupts();

	struct process *p;
	if ((p = queue_search_id(&ptable.run_queue, pid)) == NULL)
		p = queue_search_id(&ptable.wait_queue, pid);
	
	if (p == NULL){
		// Process with id "pid" no longer active, no need to wait
		enable_interrupts();
		return;
	}
	
	ptable.running->state = STATE_BLOCKED;
	ptable.running->waiting_for_process = p;
	printf("Process \"%s\" (PID %i) is waiting for process \"%s\" (PID %i)\n",
	       ptable.running->name, ptable.running->process_id,
	       p->name, p->process_id);
	schedule();

	enable_interrupts();
}
