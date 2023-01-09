#ifndef MINI_OS_STRUCTS_H
#define MINI_OS_STRUCTS_H

struct process_queue;

struct process {
	ucontext_t context;
	char name[32];
	struct process *next;
	struct process *prev;
	struct process *waiting_for_process;
	struct process *created_by;
	struct process_queue *in_queue;
	int (*process)(void);
	void *arg;
	int process_id;
	int exit_code;
	int backup_errno;
	enum process_state state;
};

struct process_queue {
	struct process *head;
	struct process *tail;
};

struct process_table {
	ucontext_t scheduler_context;
	struct process *running;
	struct process_queue run_queue;
	struct process_queue wait_queue;
	struct process_queue zombie_queue;
	int process_id;
};

struct signal {
	struct process *waiting_process;
	int value;
};

#endif
