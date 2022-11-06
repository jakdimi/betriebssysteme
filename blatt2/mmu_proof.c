#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int stack[1];
	int *heap = malloc(sizeof(int));
	if (!heap){
		fputs("Failed to allocate memory.\n", stderr);
		exit(EXIT_FAILURE);
	}
	
	if (argc == 2){
		unsigned long value;
		int *ptr;
		
		value = strtoul(argv[1], NULL, 0);
		if (value == ULONG_MAX){
			perror("Failed to parse given address");
			exit(EXIT_FAILURE);
		}
		ptr = (int *)value;
		
		printf("Value at %p is %i, setting it to zero\n", (void *)ptr, *ptr);
		*ptr = 0;
	} else {
		// Initialize data;
		*stack = 42;
		*heap = 1337;
		
		printf("Value at %p (stack) is %i\n", (void *)stack, *stack);
		printf("Value at %p (heap) is %i\n", (void *)heap, *heap);
		printf("Now run \"%s <ADDR>\" in a seperate terminal within 60 sec.\n",
		       argv[0]);
		puts("Sleeping 60 seconds...");
		sleep(60);
		printf("Value at %p (stack) is %i\n", (void *)stack, *stack);
		printf("Value at %p (heap) is %i\n", (void *)heap, *heap);
	}
	
    free(heap); 
    return 0;
}
