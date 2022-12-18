#include <errno.h>
#include <stdlib.h>
#include "../mini_os.h"

struct signal *
create_signal(void)
{
	struct signal *result = malloc(sizeof(struct signal));
	
	if (result){
		result->waiting_process = NULL;
		result->value = 0;
	} else {
		errno = ENOMEM;
	}
	
	return result;
}
