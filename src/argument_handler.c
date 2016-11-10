#include <stdio.h>
#include <stdlib.h>

#include "argument_handler.h"

int get_threads_amount(char *argument)
{
	int threads_amount = atoi(argument);

	if(threads_amount > MAX_THREADS_AMOUNT) {
		printf("Can't make more than 10 threads. Setting threads amount to 10.\n");
		threads_amount = MAX_THREADS_AMOUNT;
	}
	else if(threads_amount < 1) {
		printf("Invalid number of threads\n");
		return 0;
	}

	return threads_amount;
}