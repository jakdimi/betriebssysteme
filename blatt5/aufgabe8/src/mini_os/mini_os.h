#ifndef MINI_OS_H
#define MINI_OS_H
#include <ucontext.h>
#include <stddef.h>
#include <sys/time.h>
#include <signal.h>
#include "constants.h"
#include "structs.h"
#include "globals.h"
#include "queue/queue.h"
#include "scheduler/scheduler.h"
#include "syscalls/syscalls.h"

int disable_interrupts();
int enable_interrupts();
void delete_process(struct process *);
int init(void);
#endif
