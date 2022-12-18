#include <errno.h>
#include "../mini_os.h"

int
queue_remove(struct process *p)
{
	struct process_queue *q;
	if (!p || !p->in_queue){
		errno = EINVAL;
		return -1;
	}
	
	q = p->in_queue;
	
	if (p->next)
		p->next->prev = p->prev;
	else
		q->tail = p->prev;
	
	if (p->prev)
		p->prev->next = p->next;
	else
		q->head = p->next;
	
	p->in_queue = NULL;
	
	return 0;
}
