#include "concurrent_linked_list_coarse.h"

pthread_mutex_t p_lock;

void list_init(list_t *list) {
	node_t *end;
	if (pthread_mutex_init(&p_lock, NULL) == 0) {
		if (!((*list) = (node_t*)malloc(sizeof(node_t))))
		{
			printf("Memory overflow in insert.\n");
			exit(100);
		}
		if (!(end = (node_t*)malloc(sizeof(node_t))))
		{
			printf("Memory overflow in insert.\n");
			exit(100);
		}
		(*list)->key = 0;
		end->key = INT_MAX;
		end->next = NULL;
		(*list)->next = end;
	}
	else {
		printf("Failed to initialize mutex..\n");
		exit(-1);
	}
}

int list_insert(list_t *list, int key) {
	node_t *pred, *curr, *head, *node;
	int result;

	if ((key == 0) | (key == INT_MAX)) {
		printf("Can not insert keys with same value as sentinels!\n");
		return 0;
	}
	else {
		pthread_mutex_lock(&p_lock);
		head = *list;

		pred = head;
		curr = pred->next;
		while (curr->key < key) {
			pred = curr;
			curr = curr->next;
		}
		if (key == curr->key) {
			result = 0;
		}
		else {
			node = malloc(sizeof(node_t));
			node->key = key;
			node->next = curr;
			pred->next = node;
			result = 1;
		}

		pthread_mutex_unlock(&p_lock);
		return result;
	}
}

int list_delete(list_t *list, int key) {
	node_t *pred, *curr, *head;
	int result;

	if ((key == 0) | (key == INT_MAX)) {
		printf("Can not delete keys with same value as sentinels!\n");
		return 0;
	}
	else {
		pthread_mutex_lock(&p_lock);
		head = *list;

		pred = head;
		curr = pred->next;
		while (curr->key < key) {
			pred = curr;
			curr = curr->next;
		}
		if (key == curr->key) {
			pred->next = curr->next;
			result = 1;
		}
		else {
			result = 0;
		}

		pthread_mutex_unlock(&p_lock);
		return result;
	}
}

node_t *list_lookup(list_t *list, int key) {
	node_t *pred, *curr, *head;
	int result;

	pthread_mutex_lock(&p_lock);
	head = *list;

	pred = head;
	curr = pred->next;
	while (curr->key < key) {
		pred = curr;
		curr = curr->next;
	}
	if (key == curr->key) {
		result = curr;
	}
	else {
		result = NULL;
	}

	pthread_mutex_unlock(&p_lock);
	return result;
}