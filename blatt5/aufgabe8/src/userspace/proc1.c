#include "processes.h"
#include "mini_os.h"

int
proc1(void)
{
	int pid_proc2;
	int exit_code_proc2;
	
	msg("proc1 got PID %i", get_pid());
	
	pid_proc2 = create_process("proc2", proc2, NULL);
	if (pid_proc2 == -1){
		msg("Failed to create proc2!");
		return -1;
	}
	
	if (wait_for_child(pid_proc2, &exit_code_proc2)){
		msg("Failed to wait for child proc2!");
		return -1;
	}
	
	msg("proc2 ended with exit code %i", exit_code_proc2);
	
	return 0;
}
