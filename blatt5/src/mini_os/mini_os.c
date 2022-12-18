#include <stdio.h>
#include <stdlib.h>
#include "mini_os.h"

int
main(void)
{
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
