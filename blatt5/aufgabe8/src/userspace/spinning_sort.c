#include "userspace.h"
#include "mini_os.h"

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

int
spinning_sort(void)
{
	int merger_exit_code;
	int merger_pid;
	
	int data[] = {9, -3, 1337, 15, 11, 14, 42};
	int result[ARRAY_LENGTH(data)];
	struct spinning_sort_me sort1;
	struct spinning_sort_me sort2;
	struct spinning_merge_me merge;
	int spinlock1 = 0;
	int spinlock2 = 0;
	
	sort1.data = data;
	sort1.len = 4;
	sort1.spinlock = &spinlock1;
	
	sort2.data = data + sort1.len;
	sort2.len = ARRAY_LENGTH(data)-sort1.len;
	sort2.spinlock = &spinlock2;
	
	merge.sorted1 = sort1.data;
	merge.sorted2 = sort2.data;
	merge.merged = result;
	merge.len1 = sort1.len;
	merge.len2 = sort2.len;
	merge.spinlock1 = sort1.spinlock;
	merge.spinlock2 = sort2.spinlock;
	
	if (
		(-1 == (merger_pid = create_process("spinlock merge", spinning_merger,
		                                    &merge))) ||
		(-1 == create_process("spinlock sort1", spinning_sorter, &sort1)) ||
		(-1 == create_process("spinlock sort2", spinning_sorter, &sort2))
	){
		msg("Failed to create processes");
		return -1;
	}
	
	if (wait_for_child(merger_pid, &merger_exit_code) == -1){
		msg("Failed to wait for merger!");
		return -1;
	}
	
	msg("merger ended with exit code %i", merger_exit_code);
	msg("Sorted array is %i, %i, %i, %i, %i, %i, %i",
	    result[0], result[1], result[2], result[3], result[4], result[5],
	    result[6]);
	return 0;
}