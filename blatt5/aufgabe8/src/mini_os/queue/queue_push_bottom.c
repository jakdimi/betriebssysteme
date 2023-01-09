#include <errno.h>
#include "../mini_os.h"

int
queue_push_bottom(struct process_queue *q, struct process *p)
{
	// Is either argument NULL? Is process already in a queue?
	if (!q || !p || p->in_queue){
		errno = EINVAL;
		return -1;
	}
	
	if (q->tail)
		q->tail->next = p;
	else
		q->head = p;
	
	p->prev = q->tail;
	p->in_queue = q;
	q->tail = p;
	
	return 0;
}
