#ifndef USERSPACE_H
#define USERSPACE_H
#include <stddef.h>

struct sort_me{
	int *data;
	size_t len;
	struct signal *signal;
};

struct spinning_sort_me{
	int *data;
	size_t len;
	int *spinlock;
};

struct merge_me{
	int *sorted1;
	int *sorted2;
	int *merged;
	size_t len1;
	size_t len2;
	struct signal *signal1;
	struct signal *signal2;
};

struct spinning_merge_me{
	int *sorted1;
	int *sorted2;
	int *merged;
	size_t len1;
	size_t len2;
	int *spinlock1;
	int *spinlock2;
};

int init(void);
int sorter(void);
int merger(void);
int signal_sort(void);
int spinning_sorter(void);
int spinning_merger(void);
int spinning_sort(void);
#endif
