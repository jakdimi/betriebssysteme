#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

int
wait_for_child(int pid, int *exit_code)
{
	disable_interrupts();

	struct process *p;
	if ((p = queue_search_id(&ptable.run_queue, pid)) == NULL){
		if ((p = queue_search_id(&ptable.wait_queue, pid)) == NULL)
			p = queue_search_id(&ptable.zombie_queue, pid);
	}
	
	if ((p == NULL) || (p->created_by != ptable.running)){
		// Procces does not exist or it's not my child
		errno = EINVAL;
		enable_interrupts();
		return -1;
	}
	
	if (p->state != STATE_DEAD){
		ptable.running->state = STATE_BLOCKED;
		ptable.running->waiting_for_process = p;
		printf("Process \"%s\" (PID %i) is waiting for child \"%s\" (PID %i)\n",
		       ptable.running->name, ptable.running->process_id,
		       p->name, p->process_id);
		schedule();
	}
	
	if (exit_code)
		*exit_code = p->exit_code;
	
	enable_interrupts();
	return 0;
}
