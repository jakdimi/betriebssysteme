#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

int
swait(struct signal *s)
{
	disable_interrupts();

	if (!s){
		errno = EINVAL;
		enable_interrupts();
		return -1;
	}
	
	if (s->waiting_process){
		errno = EBUSY;
		enable_interrupts();
		return -1;
	}
	
	if (s->value){
		// Signal already set :-) We can return immediately
		s->value = 0;
		enable_interrupts();
		return 0;
	}
	
	// Signal not set, we need to wait
	
	s->waiting_process = ptable.running;
	ptable.running->state = STATE_BLOCKED;
	schedule();
	enable_interrupts();
	return 0;
}
