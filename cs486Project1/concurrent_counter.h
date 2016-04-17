#pragma once
#include <pthread.h>
//#include <sched.h>
//#include <semaphore.h>

typedef int counter_t;

/*Sets val to 0 and initializes the mutex.*/
void init_counter(counter_t *counter);

/*Increments val by one.*/
void increment_counter(counter_t *counter);

/*Decrements val by one*/
void decrement_counter(counter_t *counter);

/*Returns the current value of val*/
int get_counter(counter_t *counter);

/*Tests the current value of val against test_value and if equal sets it to new_value. 
Must return 0 upon failure and 1 upon success.*/
int test_and_set_counter(counter_t *counter, int test_value, int new_value);
