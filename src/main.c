#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#include "thread_handler.h"

sig_atomic_t print_flag = 1;
pthread_mutex_t lock;

void signal_handler(int signal_number)
{
	printf("\nEncerrando aplicação. Aguardando finalização das threads...\n");
	print_flag = 0;
}

int main(int argc, char* argv[])
{

	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);

	if(argc <= 1) {
		printf("Invalid number of arguments. Need to set threads number.\n");
		return 0;
	}

	int threads_amount;
	threads_amount = get_threads_amount(argv[1]);

	if(threads_amount < 1) {
		return 0;
	}

	pthread_t* threads = initialize_thread_vector(threads_amount);
	struct thread_arguments* thread_arguments = initialize_thread_arguments_vector(threads_amount);

	create_threads(threads, threads_amount, thread_arguments, &print_flag, &lock);
	join_threads(threads, threads_amount);

	if(!print_flag) {
		print_statistics(thread_arguments, threads_amount);
	}
	else {
		printf("Error on threads finalization\n");
	}

	free(threads);

	return 0;
}