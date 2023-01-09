#include <errno.h>
#include "../mini_os.h"

struct process *
queue_search_id(struct process_queue *q, int id)
{
	if (!q){
		errno = EINVAL;
		return NULL;
	}
	
	for (struct process *p = q->head; p != NULL; p = p->next){
		if (p->process_id == id)
			return p;
	}
	
	// Set errno to 0 to allow caller to differentiate between error and not
	// found
	errno = 0;
	return NULL;
}
