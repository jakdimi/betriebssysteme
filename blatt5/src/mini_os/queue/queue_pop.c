#include <errno.h>
#include "../mini_os.h"

struct process *
queue_pop(struct process_queue *q)
{
	struct process *p;
	
	if (!q){
		errno = EINVAL;
		return NULL;
	}
	
	if (!q->head){
		// Set errno to 0 to allow caller to differentiate between error and
		// empty queue
		errno = 0;
		return NULL;
	}
	
	p = q->head;
	q->head = p->next;
	
	if (q->head)
		q->head->prev = NULL;
	else
		q->tail = NULL;
	
	p->next = NULL;
	p->in_queue = NULL;
	return p;
}
