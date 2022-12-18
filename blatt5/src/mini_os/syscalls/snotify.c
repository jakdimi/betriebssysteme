#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

int
snotify(struct signal *s)
{
	if (!s){
		errno = EINVAL;
		return -1;
	}
	
	if (s->waiting_process){
		// Notify waiting process
		s->waiting_process->state = STATE_RUNNABLE;
		if (
			(queue_remove(s->waiting_process) == -1) ||
			(queue_push_bottom(&ptable.run_queue, s->waiting_process))
		){
			perror("Failed to move process from wait to run queue");
			exit(EXIT_FAILURE);
		}
		s->waiting_process = NULL;
	} else {
		// No process waiting, setting signal value to 1 so next swait() can
		// return immediately
		s->value = 1;
	}
	
	return 0;
}
 