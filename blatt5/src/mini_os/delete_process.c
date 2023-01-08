#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mini_os.h"

static void
update_created_by(struct process_queue *q, struct process *p)
{
	for (struct process *i = q->head; i != NULL; i = i->next){
		if (i->created_by == p)
			i->created_by = NULL;
	}
}

static void
free_memory(struct process *p)
{
	free(p->context.uc_stack.ss_sp);
	free(p);
}

static void
free_child_zombies(struct process *p)
{
	struct process *i = ptable.zombie_queue.head;
	struct process *next;
	while (i != NULL){
		next = i->next;
		if (i->created_by == p){
			if (queue_remove(i) == -1){
				perror("Failed to remove process from zombie queue");
				exit(EXIT_FAILURE);
			}
			printf("Removed process \"%s\" (PID %i) from zombie queue\n",
			       i->name, i->process_id);
			free_memory(i);
		}
		
		i = next;
	}
}

void
delete_process(struct process *p)
{
	disable_interrupts();

	assert(p != NULL);
	update_created_by(&ptable.run_queue, p);
	update_created_by(&ptable.wait_queue, p);
	
	free_child_zombies(p);
	free_memory(p);

	enable_interrupts();
}
