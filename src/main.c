#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "thread_handler.h"

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

	pthread_t* threads = initialize_thread_vector(threads_amount);
	struct thread_arguments* thread_arguments = initialize_thread_arguments_vector(threads_amount);

	create_threads(threads, threads_amount, thread_arguments);
	join_threads(threads, threads_amount);

	free(threads);

	return 0;
}