#include <stdio.h>
#include <stdlib.h>

#include "argument_handler.h"

int main(int argc, char* argv[])
{

	if(argc <= 1) {
		printf("Invalid number of arguments. Need to set threads number.\n");
		return 0;
	}

	int threads_amount;
	threads_amount = get_threads_amount(argv[1]);

	if(threads_amount < 1) {
		return 0;
	}

	printf("Threads amount: %d\n", threads_amount);

	return 0;
}