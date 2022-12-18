#include "userspace.h"
#include "mini_os.h"

int
init(void)
{
	int exit_code;
	int pid;
	
	if (-1 == (pid = create_process("singal sort", signal_sort, NULL))){
		msg("Failed to start multi process sort using signals");
		return -1;
	}
	
	if (wait_for_child(pid, &exit_code) == -1){
		msg("Failed to wait multi process sort using signals");
		return -1;
	}
	
	msg("Multi process sort using signals exited with %i", exit_code);
	
#if 0
	if (-1 == (pid = create_process("spinlock sort", spinning_sort, NULL))){
		msg("Failed to start multi process sort using spinlocks");
		return -1;
	}
	
	if (wait_for_child(pid, &exit_code) == -1){
		msg("Failed to wait multi process sort using spinlocks");
		return -1;
	}
	
	msg("Multi process sort using spinlocks exited with %i", exit_code);
#endif
	
	return 0;
}