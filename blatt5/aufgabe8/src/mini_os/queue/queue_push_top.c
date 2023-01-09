#include <errno.h>
#include "../mini_os.h"

int
queue_push_top(struct process_queue *q, struct process *p)
{
	// Is either argument NULL? Is process already in a queue?
	if (!q || !p || p->in_queue){
		errno = EINVAL;
		return -1;
	}
	
	if (q->head)
		q->head->prev = p;
	else
		q->tail = p;
	
	p->next = q->head;
	p->in_queue = q;
	q->head = p;
	
	return 0;
}
