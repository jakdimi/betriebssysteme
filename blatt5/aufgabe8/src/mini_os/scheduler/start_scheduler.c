#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mini_os.h"

enum print_state_argument{
	BEFORE_SCHEDULING,
	AFTER_SCHEDULING
};

static void
print_state(enum print_state_argument arg)
{
	struct process *p = ptable.running;
	switch (arg){
	case BEFORE_SCHEDULING:
		puts("\n === Scheduler entered with state ===");
		break;
	case AFTER_SCHEDULING:
		puts("\n ===  Scheduler left with state   ===");
		break;
	}
	
	if (p)
		printf(" Current process: \"%s\" (PID %i)\n", p->name, p->process_id);
	else
		puts(" Current process: -");
	
	if ((p = ptable.run_queue.head) != NULL){
		printf(" Runnable: \"%s\" (PID %i)", p->name, p->process_id);
		for (p = p->next; p != NULL; p = p->next)
			printf(", \"%s\" (PID %i)", p->name, p->process_id);
		puts("");
	} else {
		puts(" Runnable: -");
	}
	
	if ((p = ptable.wait_queue.head) != NULL){
		printf(" Blocked: \"%s\" (PID %i)", p->name, p->process_id);
		for (p = p->next; p != NULL; p = p->next)
			printf(", \"%s\" (PID %i)", p->name, p->process_id);
		puts("");
	} else {
		puts(" Blocked: -");
	}
	
	if ((p = ptable.zombie_queue.head) != NULL){
		printf(" Zombies: \"%s\" (PID %i)", p->name, p->process_id);
		for (p = p->next; p != NULL; p = p->next)
			printf(", \"%s\" (PID %i)", p->name, p->process_id);
		puts("");
	} else {
		puts(" Zombies: -");
	}
	puts(" ====================================\n");
}

static int
handle_process_paused(struct process *p)
{
	if (p->state == STATE_BLOCKED){
		// Current process is blocked, so put it in wait queue
		if (queue_push_bottom(&ptable.wait_queue, p)){
			perror("Failed to add process to wait queue");
			return -1;
		}
		printf("Process \"%s\" (PID %i) has been PAUSED and added to "
		       "the wait queue\n", p->name, p->process_id);
	} else {
		// Process must be runnable, if it's paused and not blocked
		assert(p->state == STATE_RUNNABLE);
		if (queue_push_bottom(&ptable.run_queue, p)){
			perror("Failed to add process to run queue");
			return -1;
		}
		printf("Process \"%s\" (PID %i) has been PAUSED and  added to "
		       "the run queue\n", p->name, p->process_id);
	}
	
	return 0;
}

static int
unblock_waiters(struct process *p)
{
	for (struct process *i = ptable.wait_queue.head; i != NULL; i = i->next){
		if (i->waiting_for_process == p){
			// i was waiting for p, so unblock it
			i->waiting_for_process = NULL;
			i->state = STATE_RUNNABLE;
			if (queue_remove(i)){
				perror("Failed to unqueue process from wait queue");
				return -1;
			}
			if (queue_push_bottom(&ptable.run_queue, i)){
				perror("Failed to append process to run queue");
				return -1;
			}
		}
	}
	
	return 0;
}

static int
handle_process_ended(struct process *p)
{
	printf("Process \"%s\" (PID %i) FINISHED\n", p->name,
	       p->process_id);
	
	if (unblock_waiters(p))
		return -1;
	
	if (p->created_by != NULL){
		printf("Added process \"%s\" (PID %i) to Zombie list\n",
		        p->name, p->process_id);
		if (queue_push_bottom(&ptable.zombie_queue, p)){
			perror("Failed to append process to zombie queue");
			return -1;
		}
	} else {
		printf("Removed process \"%s\" (PID %i) (parent dead)\n",
		        p->name, p->process_id);
		delete_process(p);
	}
	
	return 0;
}

static void
process_wrapper(void)
{
	disable_interrupts();

	struct process *p = ptable.running;
	p->exit_code = p->process();
	p->state = STATE_DEAD;
	
	enable_interrupts();

	if (setcontext(&ptable.scheduler_context) == -1){
		perror("Failed to return to core scheduler");
		exit(EXIT_FAILURE);
	}
	
	// Should never return here
	fputs("Failed to return to core scheduler!\n", stderr);
	exit(EXIT_FAILURE);
}

int
start_scheduler(void)
{
	struct process *cur;
	if (getcontext(&ptable.scheduler_context) == -1){
		perror("Failed to back up scheduler context");
		return -1;
	}
	
	print_state(BEFORE_SCHEDULING);
	
	if (ptable.running != NULL){
		cur = ptable.running;
		if (cur->state == STATE_DEAD){
			// Resumed from process_wrapper() ==> Process ended
			if (handle_process_ended(cur))
				return -1;
		} else {
			// Resumed from schedule()
			if (handle_process_paused(ptable.running))
				return -1;
		}
	}
	
	while (ptable.run_queue.head){
		cur = ptable.running = select_next_process();
		print_state(AFTER_SCHEDULING);
		if (!ptable.running){
			perror("Failed to select next process");
			return -1;
		}
		
		if (cur->state == STATE_CREATED){
			// New process, start function
			cur->state = STATE_RUNNING;
			makecontext(&cur->context, process_wrapper, 0);
			if (setcontext(&cur->context) == -1){
				perror("Failed to switch to new process");
				return -1;
			}
			// Should not return to this point
			fputs("Failed to switch to new process!\n", stderr);
			return -1;
		} else {
			// Existing process, continue function
			cur->state = STATE_RUNNING;
			if (setcontext(&cur->context) == -1){
				perror("Failed to resume process");
				return -1;
			}
			// Programm flow should never return here
			fputs("ERROR: setcontext() failed!\n", stderr);
			errno = ECANCELED;
			return -1;
		}
		
		if (handle_process_ended(cur))
			return -1;
	}
	
	if (ptable.wait_queue.head){
		fputs("ERROR: Wait queue not empty\n", stderr);
		errno = ECANCELED;
		return -1;
	}
	
	return 0;
}
