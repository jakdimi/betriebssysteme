#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "../mini_os.h"

int
msg(const char *s, ...)
{
	va_list ap;
	if (!s){
		errno = EINVAL;
		return -1;
	}
	
	printf("Message from process \"%s\" (PID %i):\n",
	        ptable.running->name, ptable.running->process_id);
	va_start(ap, s);
	vprintf(s, ap);
	va_end(ap);
	puts("");
	return 0;
}
