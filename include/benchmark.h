#include <time.h>
#include <stdint.h>

#ifndef BENCHMARK_H
#define BENCHMARK_H

struct timespec get_time();
unsigned long long int get_time_elapsed(struct timespec initial_time);

#endif
