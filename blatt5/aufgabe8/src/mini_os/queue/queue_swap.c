#include <errno.h>
#include "../mini_os.h"

int
queue_swap(struct process *p1, struct process *p2)
{
	struct process *tmp;
	struct process_queue *q;
	if (!p1 || !p2 || !p1->in_queue || (p1->in_queue != p2->in_queue)){
		errno = EINVAL;
		return -1;
	}
	
	tmp = p1->next;
	p1->next = p2->next;
	p2->next = tmp;
	
	tmp = p1->prev;
	p1->prev = p2->prev;
	p2->prev = tmp;
	
	// Update head/tail if needed
	q = p1->in_queue;
	if (q->head == p1)
		q->head = p2;
	if (q->head == p2)
		q->head = p1;
	
	if (q->tail == p1)
		q->tail = p2;
	if (q->tail == p2)
		q->tail = p1;
	
	return 0;
}
