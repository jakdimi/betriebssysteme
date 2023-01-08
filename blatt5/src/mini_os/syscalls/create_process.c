#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mini_os.h"

#define STACK_SIZE 16384

int
create_process(const char *name, int func(void), void *arg)
{
	disable_interrupts();

	size_t name_len;
	struct process *result;
	
	if (!name || !func){
		errno = EINVAL;
		enable_interrupts();
		return -1;
	}
	
	name_len = strnlen(name, sizeof(result->name));
	if (name_len >= sizeof(result->name)){
		errno = EOVERFLOW;
		enable_interrupts();
		return -1;
	}
	
	if (!(result = malloc(sizeof(struct process)))){
		errno = ENOMEM;
		enable_interrupts();
		return -1;
	}
	
	// Copy including the terminating zero byte
	memcpy(result->name, name, name_len+1);
	result->next = NULL;
	result->prev = NULL;
	result->waiting_for_process = NULL;
	result->created_by = ptable.running;
	result->in_queue = NULL;
	result->process = func;
	result->arg = arg;
	result->process_id = ++ptable.process_id;
	result->state = STATE_CREATED;
	result->backup_errno = 0;
	
	// Creating context stack for the new process
	if (getcontext(&result->context) == -1){
		perror("Failed to create context for new process");
		free(result);
		enable_interrupts();
		return -1;
	}
	
	if ((result->context.uc_stack.ss_sp = malloc(STACK_SIZE)) == NULL){
		perror("Failed to create stack for the new process");
		free(result);
		enable_interrupts();
		return -1;
	}
	result->context.uc_stack.ss_size = STACK_SIZE;
	result->context.uc_link = &ptable.scheduler_context;
	
	if (queue_push_bottom(&ptable.run_queue, result)){
		perror("Failed to apped new process to run queue");
		free(result->context.uc_stack.ss_sp);
		free(result);
		enable_interrupts();
		return -1;
	}
	
	if (ptable.running){
		printf("Process \"%s\" (PID %i) created process \"%s\" (PID %i)\n",
		       ptable.running->name, ptable.running->process_id,
		       result->name, result->process_id);
	} else {
		printf("Created first process \"%s\" (PID %i)\n",
		       result->name, result->process_id);
	}
	
	enable_interrupts();
	return result->process_id;
}
