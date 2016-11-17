#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "thread_handler.h"

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

pthread_t* initialize_thread_vector(int threads_amount)
{
	pthread_t* thread_vector = (pthread_t*) malloc(threads_amount * sizeof(pthread_t));

	return thread_vector;
}

struct thread_arguments* initialize_thread_arguments_vector(int threads_amount)
{
	struct thread_arguments* thread_arguments = (struct thread_arguments*) malloc(threads_amount *
	 sizeof(struct thread_arguments));

	return thread_arguments;
}

void create_threads(pthread_t* threads, int threads_amount, struct thread_arguments* thread_arguments, 
	sig_atomic_t* print_flag, pthread_mutex_t* lock)
{
	int counter = 0;

	while(counter < threads_amount) {
		thread_arguments[counter].thread_number = (counter + 1);
		thread_arguments[counter].print_counter = 0;
		thread_arguments[counter].print_flag = print_flag;
		thread_arguments[counter].lock = lock;
		pthread_create(&threads[counter], NULL, &print_char, &thread_arguments[counter]);
		counter++;
	}
}

void* print_char(void* thread_arguments)
{
	struct thread_arguments* thread_args = (struct thread_arguments*) thread_arguments;
	char c;
	int counter = 0;

	c = find_thread_char(thread_args->thread_number);

	while(*(thread_args->print_flag)) {

		pthread_mutex_lock(thread_args->lock);

		thread_args->print_counter++;

		for(counter = 0; counter < thread_args->thread_number; counter++) {
			fprintf(stdout, "%c", c);
		}

		fprintf(stdout, "\n");

		pthread_mutex_unlock(thread_args->lock);

		usleep(500000);
	}

		return NULL;
}

char find_thread_char(int thread_number)
{
	char c;

	c = 96 + thread_number;

	return c;
}

void join_threads(pthread_t* threads, int threads_amount)
{
	int counter = 0;

	for(counter = 0; counter < threads_amount; counter++) {
		pthread_join(threads[counter], NULL);
	}
}

void print_statistics(struct thread_arguments* thread_arguments, int threads_amount)
{
	int counter = 0;
	printf("Aplicação encerrado com sucesso!\n");
	printf("Estatísticas: \n");

	while(counter < threads_amount) {
		printf("thread %d: %d linhas.\n", thread_arguments[counter].thread_number,
			thread_arguments[counter].print_counter);
		counter++;
	}
}