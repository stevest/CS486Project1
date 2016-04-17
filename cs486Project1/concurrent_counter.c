#include "concurrent_counter.h"

pthread_mutex_t p_lock;

void init_counter(counter_t *counter) {
	
	if (pthread_mutex_init(&p_lock, NULL) == 0) {
		*counter = 0;
	}
	else {
		printf("Failed to initialize mutex..\n");
		exit(-1);
	}
}

void increment_counter(counter_t *counter) {
	pthread_mutex_lock(&p_lock);
	(*counter)++;
	pthread_mutex_unlock(&p_lock);
}

void decrement_counter(counter_t *counter) {
	pthread_mutex_lock(&p_lock);
	(*counter)--;
	pthread_mutex_unlock(&p_lock);
}

int get_counter(counter_t *counter) {
	counter_t tmp;
	pthread_mutex_lock(&p_lock);
	tmp = *counter;
	pthread_mutex_unlock(&p_lock);
	return tmp;
}

int test_and_set_counter(counter_t *counter, int test_value, int new_value) {
	int cmp;
	pthread_mutex_lock(&p_lock);
	if (*counter == test_value) {
		cmp = 1;
		*counter = new_value;
	}
	else {
		cmp = 0;
	}
	pthread_mutex_unlock(&p_lock);
	
	if (cmp) { return 1; }
	return 0;
}
