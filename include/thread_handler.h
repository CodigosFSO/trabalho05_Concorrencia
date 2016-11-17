#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include <signal.h>

#define MAX_THREADS_AMOUNT 10

struct thread_arguments {
	int thread_number;
	int print_counter;
	sig_atomic_t* print_flag;
	pthread_mutex_t *lock;
};

int get_threads_amount(char *argument);
pthread_t* initialize_thread_vector(int threads_amount);
struct thread_arguments* initialize_thread_arguments_vector(int threads_amount);
void create_threads(pthread_t* threads, int threads_amount, struct thread_arguments* thread_arguments, 
	sig_atomic_t* print_flag, pthread_mutex_t* lock);
void* print_char(void* thread_arguments);
char find_thread_char(int thread_number);
void join_threads(pthread_t* threads, int threads_amount);
void print_statistics(struct thread_arguments* thread_arguments, int threads_amount);

#endif