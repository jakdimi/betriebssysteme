#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "../mini_os.h"

int
msg(const char *s, ...)
{
	disable_interrupts();

	va_list ap;
	if (!s){
		errno = EINVAL;
		enable_interrupts();
		return -1;
	}
	
	printf("Message from process \"%s\" (PID %i):\n",
	        ptable.running->name, ptable.running->process_id);
	va_start(ap, s);
	vprintf(s, ap);
	va_end(ap);
	puts("");
	enable_interrupts();
	return 0;
}
