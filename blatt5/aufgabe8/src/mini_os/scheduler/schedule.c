#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

void
schedule(void)
{
	if (ptable.running->state == STATE_RUNNING)
		ptable.running->state = STATE_RUNNABLE;
	
	if (getcontext(&ptable.running->context) == -1){
		perror("Failed to back up current context");
		exit(EXIT_FAILURE);
	}
	
	if (ptable.running->state == STATE_RUNNING){
		// Returned from scheduler ==> Restore errno and continue
		errno = ptable.running->backup_errno;
		return;
	}
	
	// Backup current errno value
	ptable.running->backup_errno = errno;
	
	// Return to core scheduler logic
	if (setcontext(&ptable.scheduler_context) == -1){
		perror("Failed to return to core scheduler");
		exit(EXIT_FAILURE);
	}
	
	// Should never return to this point
	fputs("Return to core scheduler failed!\n", stderr);
	exit(EXIT_FAILURE);
}
