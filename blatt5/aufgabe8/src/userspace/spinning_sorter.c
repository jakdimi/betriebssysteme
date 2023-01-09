#include "userspace.h"
#include "mini_os.h"

static void
swap_ints(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int
spinning_sorter(void)
{
	int is_sorted = 0;
	struct spinning_sort_me *arg = get_arg();
	
	if (!arg){
		msg("Failed to get argument!");
		return -1;
	}
	
	while (!is_sorted){
		is_sorted = 1;
		for (size_t i = 0; i < arg->len - 1; i++){
			if (arg->data[i] > arg->data[i+1]){
				is_sorted = 0;
				swap_ints(&arg->data[i], &arg->data[i+1]);
			}
		}
	}
	
	*arg->spinlock = 1;
	return 0;
}
