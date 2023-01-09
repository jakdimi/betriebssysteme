CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g -O0 -D_DEFAULT_SOURCE
LDFLAGS := 
AR := ar

.PHONY: all clean folder mini_os

all: folder mini_os

MINI_OS_OBJS += obj/mini_os/interrupts.o
MINI_OS_OBJS += obj/mini_os/delete_process.o
MINI_OS_OBJS += obj/mini_os/mini_os.o
MINI_OS_OBJS += obj/mini_os/ptable.o
MINI_OS_OBJS += obj/mini_os/queue/queue_pop.o
MINI_OS_OBJS += obj/mini_os/queue/queue_push_bottom.o
MINI_OS_OBJS += obj/mini_os/queue/queue_push_top.o
MINI_OS_OBJS += obj/mini_os/queue/queue_remove.o
MINI_OS_OBJS += obj/mini_os/queue/queue_search_id.o
MINI_OS_OBJS += obj/mini_os/queue/queue_swap.o
MINI_OS_OBJS += obj/mini_os/scheduler/schedule.o
MINI_OS_OBJS += obj/mini_os/scheduler/select_next_process.o
MINI_OS_OBJS += obj/mini_os/scheduler/start_scheduler.o
MINI_OS_OBJS += obj/mini_os/syscalls/create_process.o
MINI_OS_OBJS += obj/mini_os/syscalls/create_signal.o
MINI_OS_OBJS += obj/mini_os/syscalls/delete_signal.o
MINI_OS_OBJS += obj/mini_os/syscalls/get_arg.o
MINI_OS_OBJS += obj/mini_os/syscalls/get_pid.o
MINI_OS_OBJS += obj/mini_os/syscalls/msg.o
MINI_OS_OBJS += obj/mini_os/syscalls/snotify.o
MINI_OS_OBJS += obj/mini_os/syscalls/swait.o
MINI_OS_OBJS += obj/mini_os/syscalls/wait_for_child.o
MINI_OS_OBJS += obj/mini_os/syscalls/wait_for_process.o

USERSPACE_OBJS += obj/userspace/init.o
USERSPACE_OBJS += obj/userspace/sorter.o
USERSPACE_OBJS += obj/userspace/merger.o
USERSPACE_OBJS += obj/userspace/signal_sort.o
USERSPACE_OBJS += obj/userspace/spinning_sorter.o
USERSPACE_OBJS += obj/userspace/spinning_merger.o
USERSPACE_OBJS += obj/userspace/spinning_sort.o

MINI_OS_COMMON_HEADER += src/mini_os/constants.h
MINI_OS_COMMON_HEADER += src/mini_os/mini_os.h
MINI_OS_COMMON_HEADER += src/mini_os/globals.h
MINI_OS_COMMON_HEADER += src/mini_os/structs.h

FOLDER += obj/mini_os/queue
FOLDER += obj/mini_os/scheduler
FOLDER += obj/mini_os/syscalls
FOLDER += obj/userspace

folder:
	mkdir -p $(FOLDER)

mini_os: $(MINI_OS_OBJS) $(USERSPACE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

obj/mini_os/mini_os.o: src/mini_os/mini_os.c $(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/interrupts.o: \
		src/mini_os/interrupts.c $(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/delete_process.o: \
		src/mini_os/delete_process.c $(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/ptable.o: src/mini_os/ptable.c $(MINI_OS_COMMON_HEADER) 
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/queue/%.o: \
		src/mini_os/queue/%.c \
		src/mini_os/queue/queue.h \
		$(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/syscalls/%.o: \
		src/mini_os/syscalls/%.c \
		src/mini_os/syscalls/syscalls.h \
		$(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/mini_os/scheduler/%.o: \
		src/mini_os/scheduler/%.c \
		src/mini_os/scheduler/scheduler.h \
		$(MINI_OS_COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/userspace/%.o: \
		src/userspace/%.c \
		src/userspace/mini_os.h \
		src/userspace/userspace.h \
		src/mini_os/syscalls/syscalls.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf obj
	rm -f mini_os