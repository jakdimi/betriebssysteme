#include <stdio.h>
#include <stdlib.h>
#include "mini_os.h"

void handler() {
	schedule();
}

int
main(void)
{
	// set timer
	struct itimerval value;
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 500000;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 500000;
	if (setitimer(ITIMER_PROF, &value, NULL) != 0) {
		perror("Failed to set timer.");
		exit(EXIT_FAILURE);
	}

	// set sigaction
	struct sigaction action;
	action.sa_handler = &handler;
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGPROF, &action, NULL) != 0) {
		perror("Failed to set sigaction.");
		exit(EXIT_FAILURE);
	}

	if (create_process("init", init, NULL) == -1){
		perror("Creating init process failed");
		return EXIT_FAILURE;
	}
	
	if (start_scheduler()){
		perror("Scheduling failed");
		return EXIT_FAILURE;
	}
	
	puts("Scheduler returned, all processes done");
	return EXIT_SUCCESS;
}
