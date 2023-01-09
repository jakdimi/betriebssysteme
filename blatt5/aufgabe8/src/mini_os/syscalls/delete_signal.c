#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

int
delete_signal(struct signal *s)
{
	disable_interrupts();

	if (!s){
		errno = EINVAL;
		enable_interrupts();
		return -1;
	}
	
	if (s->waiting_process){
		fprintf(stderr, "Signal to delete still in use by \"%s\" (PID %i)!\n",
		        s->waiting_process->name, s->waiting_process->process_id);
		errno = EBUSY;
		enable_interrupts();
		return -1;
	}
	
	free(s);
	enable_interrupts();
	return 0;
}
