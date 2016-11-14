#include "benchmark.h"

struct timespec get_time()
{
	struct timespec current_time;
	clock_gettime(CLOCK_MONOTONIC, &current_time);

	return current_time;
}

unsigned long long int get_time_elapsed(struct timespec initial_time)
{
	struct timespec final_time = get_time();

	return ((final_time.tv_sec - initial_time.tv_sec)*1e+9) + ((final_time.tv_nsec - initial_time.tv_nsec));
}