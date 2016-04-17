#include "concurrent_counter.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS_NUM 40

typedef struct thread_data {
	counter_t *ctr;
	int tid;
	int *output;
} thread_data_t;

void* worker_func(void *data)
{
	int tmp;
	thread_data_t *t_data;

	t_data = (thread_data_t *)data;

	// Do some work
	increment_counter(t_data->ctr);

	tmp = get_counter(t_data->ctr);
	//(t_data->output)+(t_data->tid) = tmp;
	*(t_data->output) = tmp;
	printf("Thread %d : counter: %d \n", t_data->tid, tmp);
	//printf("Thread %d \n", pthread_self());

	//printf("Thread %d exiting!\n", thread_data->tid);

	//free(data);
	pthread_exit(NULL);
}

int main() {
	int i;
	pthread_t *worker_threads;
	counter_t mycounter;
	int *output;

	init_counter(&mycounter);
	worker_threads = malloc(sizeof(pthread_t) * THREADS_NUM);
	output = (int*)calloc(sizeof(int),THREADS_NUM);
	
	for (i = 0; i < THREADS_NUM; ++i) {
		thread_data_t *data = malloc(sizeof(thread_data_t));
		data->tid = i;
		data->ctr = &mycounter;
		data->output = &output[i];
		if (pthread_create( &worker_threads[i], NULL, worker_func, (void *)data)) {
			printf("Error creating thread %d\n", i);
			return 1;
		}
	}
	
	// Wait for threads to return
	for (i = 0; i < THREADS_NUM; ++i) {
		if (pthread_join(worker_threads[i], NULL)) {
			printf("Error joining thread_%d\n", i);
			return 1;
		}
	}

};