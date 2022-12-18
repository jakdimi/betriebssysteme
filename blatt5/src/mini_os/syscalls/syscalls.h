#ifndef MINI_OS_SYSCALLS_H
#define MINI_OS_SYSCALLS_H

int create_process(const char *name, int func(void), void *arg);
struct signal * create_signal(void);
int delete_signal(struct signal *);
void * get_arg(void);
int get_pid(void);
int msg(const char *s, ...);
int snotify(struct signal *);
int swait(struct signal *);
void wait_for_process(int pid);
int wait_for_child(int pid, int *exit_code);

#endif
