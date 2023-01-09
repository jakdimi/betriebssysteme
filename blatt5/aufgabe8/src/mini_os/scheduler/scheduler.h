#ifndef MINI_OS_SCHEDULER_H
#define MINI_OS_SCHEDULER_H

int start_scheduler(void);
void schedule(void);
struct process * select_next_process(void);

#endif
