#ifndef MINI_OS_QUEUE_H
#define MINI_OS_QUEUE_H

struct process * queue_pop(struct process_queue *);
int queue_push_top(struct process_queue *, struct process *);
int queue_push_bottom(struct process_queue *, struct process *);
struct process * queue_search_id(struct process_queue *, int id);
int queue_swap(struct process *, struct process *);
int queue_remove(struct process *);
#endif
