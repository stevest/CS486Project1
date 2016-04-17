#include "benchmark_lists.h"

#define THREADS_NUM 1

static pthread_barrier_t barrier;

typedef struct thread_data {
	list_t *list;
	int tid;
	//int *output;
} thread_data_t;

int main() {
	int i;
	list_t list;
	pthread_t *worker_threads;
	int *output;

	list_init(&list);
	worker_threads = malloc(sizeof(pthread_t) * THREADS_NUM);

	dowork(THREADS_NUM, worker_threads, list);

};


void* worker_func(void *data)
{
	int i, s, amount, it, key;
	thread_data_t *t_data;

	t_data = (thread_data_t *)data;
	it = 500;
	// Do some work
	amount = (int)((it * 0.1) / THREADS_NUM);
	for (i = 0; i < amount; i++) {
		key = i + (t_data->tid*amount) + 1;
		list_insert(t_data->list, key);
		printf("@ %d: Inserting entry: %d \n", t_data->tid, i);
	}

	s = pthread_barrier_wait(&barrier);

	amount = (int)((it * 0.8) / THREADS_NUM);
	for (i = 0; i < amount; i++) {
		key = (t_data->tid * 10 + 17) % it;
		list_lookup(t_data->list, key);
		printf("@ %d: Looking up entry: %d \n", t_data->tid, i);
	}

	s = pthread_barrier_wait(&barrier);

	amount = (int)((it * 0.1) / THREADS_NUM);
	for (i = 0; i < amount; i++) {
		key = i + (t_data->tid*amount) + 1;
		list_delete(t_data->list, key);
		printf("@ %d: Deleting entry: %d \n", t_data->tid, i);
	}

	pthread_exit(NULL);
}

void dowork(int nt, pthread_t* wt, list_t list) {
	int i;

	for (i = 0; i < nt; ++i) {
		thread_data_t *data = malloc(sizeof(thread_data_t));
		data->tid = i;
		data->list = &list;
		//data->output = &output[i];
		if (pthread_create(&wt[i], NULL, worker_func, (void *)data)) {
			printf("Error creating thread %d\n", i);
		}
	}

	// Wait for threads to return
	for (i = 0; i < nt; ++i) {
		if (pthread_join(wt[i], NULL)) {
			printf("Error joining thread_%d\n", i);
		}
	}
}
