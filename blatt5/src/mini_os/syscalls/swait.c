#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

int
swait(struct signal *s)
{
	if (!s){
		errno = EINVAL;
		return -1;
	}
	
	if (s->waiting_process){
		errno = EBUSY;
		return -1;
	}
	
	if (s->value){
		// Signal already set :-) We can return immediately
		s->value = 0;
		return 0;
	}
	
	// Signal not set, we need to wait
	
	s->waiting_process = ptable.running;
	ptable.running->state = STATE_BLOCKED;
	schedule();
	return 0;
}
