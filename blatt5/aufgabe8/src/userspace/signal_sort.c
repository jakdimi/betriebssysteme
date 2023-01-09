#include "userspace.h"
#include "mini_os.h"

#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

int
signal_sort(void)
{
	int merger_exit_code;
	int merger_pid;
	
	int data[] = {9, -3, 1337, 15, 11, 14, 42};
	int result[ARRAY_LENGTH(data)];
	struct sort_me sort1;
	struct sort_me sort2;
	struct merge_me merge;
	
	sort1.data = data;
	sort1.len = 4;
	sort1.signal = create_signal();
	
	sort2.data = data + sort1.len;
	sort2.len = ARRAY_LENGTH(data)-sort1.len;
	sort2.signal = create_signal();
	
	merge.sorted1 = sort1.data;
	merge.sorted2 = sort2.data;
	merge.merged = result;
	merge.len1 = sort1.len;
	merge.len2 = sort2.len;
	merge.signal1 = sort1.signal;
	merge.signal2 = sort2.signal;
	
	if (!sort1.signal || !sort2.signal){
		msg("Failed to create signals!");
		return -1;
	}
	
	if (
		(-1 == (merger_pid = create_process("merge", merger, &merge))) ||
		(-1 == create_process("sort1", sorter, &sort1)) ||
		(-1 == create_process("sort2", sorter, &sort2))
	){
		msg("Failed to create processes");
		return -1;
	}
	
	if (wait_for_child(merger_pid, &merger_exit_code) == -1){
		msg("Failed to wait for merger!");
		return -1;
	}
	
	if (delete_signal(sort1.signal) || delete_signal(sort2.signal)){
		msg("Failed to delete signals!");
		return -1;
	}
	
	msg("merger ended with exit code %i", merger_exit_code);
	msg("Sorted array is %i, %i, %i, %i, %i, %i, %i",
	    result[0], result[1], result[2], result[3], result[4], result[5],
	    result[6]);
	return 0;
}