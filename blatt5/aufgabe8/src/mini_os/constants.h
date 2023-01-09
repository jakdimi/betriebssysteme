#ifndef MINI_OS_CONSTANTS_H
#define MINI_OS_CONSTANTS_H

enum process_state {
	STATE_CREATED    = 0,
	STATE_RUNNABLE   = 1,
	STATE_RUNNING    = 2,
	STATE_BLOCKED    = 3,
	STATE_DEAD       = 4,
};

#endif
