#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

static const int values[] = {1, 2, 3, 4};

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

int
main(int argc, char **argv)
{
	struct dynop op;
	int result = 0;
	
	if (argc != 2){
		puts("Usage: ./reduce <OP_LIB>");
		return EXIT_FAILURE;
	}
	
	printf("Reduced \"%i", values[0]);
	for (size_t i = 1; i < ARRAY_LENGTH(values); i++)
		printf(", %i", values[i]);
	
	printf("\" to: %i\n", result);
	
	return EXIT_SUCCESS;
}
