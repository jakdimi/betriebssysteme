#include <stdio.h>
#include <signal.h>
#include "mini_os.h"

int disable_interrupts() {
    sigset_t sigset;
	if (sigemptyset(&sigset) != 0) {
		perror("Could not create sigset.");
		return -1;
	}
	if (sigaddset(&sigset, SIGPROF) != 0) {
		perror("Could not add SIGPROF to sigset.");
		return -1;
	}
	if (sigprocmask(SIG_BLOCK, &sigset, NULL) != 0) {
		perror("Could not block SIGPROF.");
		return -1;
	}
	return 0;
}

int enable_interrupts() {
    sigset_t sigset;
	if (sigemptyset(&sigset) != 0) {
		perror("Could not create sigset.");
		return -1;
	}
	if (sigaddset(&sigset, SIGPROF) != 0) {
		perror("Could not add SIGPROF to sigset.");
		return -1;
	}
	if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) != 0) {
		perror("Could not unblock SIGPROF.");
		return -1;
	}
	return 0;
}