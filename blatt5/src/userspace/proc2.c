#include "processes.h"
#include "mini_os.h"

int
proc2(void)
{
	msg("proc2 got PID %i", get_pid());
	
	return 42;
}
