#pragma once
#include "concurrent_linked_list_coarse.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* worker_func(void *data);
void dowork(int nt, pthread_t* wt, list_t list);