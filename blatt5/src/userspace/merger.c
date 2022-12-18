#include "userspace.h"
#include "mini_os.h"

int
merger(void)
{
	struct merge_me *arg;
	size_t i, pos1, pos2, merged_len;
	
	arg = get_arg();
	if (!arg){
		msg("Failed to get argument");
		return -1;
	}
	
	msg("Waiting for sorting processes to finish");
	if ((swait(arg->signal1) == -1) || (swait(arg->signal2) == -1)){
		msg("Failed to wait for signal");
		return -1;
	}
	
	// Merge to sorted inputs
	pos1 = pos2 = 0;
	merged_len = arg->len1 + arg->len2;
	for (i = 0; i < merged_len; i++){
		if (pos1 == arg->len1){
			while (i < merged_len)
				arg->merged[i++] = arg->sorted2[pos2++];
		} else if (pos2 == arg->len2){
			while (i < merged_len)
				arg->merged[i++] = arg->sorted1[pos1++];
		} else if (arg->sorted1[pos1] < arg->sorted2[pos2])
			arg->merged[i] = arg->sorted1[pos1++];
		else
			arg->merged[i] = arg->sorted2[pos2++];
	}
	
	return 0;
}
