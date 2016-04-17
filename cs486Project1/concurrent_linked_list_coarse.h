#pragma once
#include <pthread.h>

typedef struct node{
	int key;
	int value;
	struct node *next;
} node_t;

typedef node_t* list_t;

/*Initializes the list*/
void list_init(list_t *list);

/*Inserts a node on the list with data set to key*/
int list_insert(list_t *list, int key);

/*Deletes node with matching key from the list.
Returns FALSE upon failure or TRUE upon success. */
int list_delete(list_t *list, int key);

/*Traverses the list to find the node with a matching key.
Returns a pointer to the node if found, or NULL otherwise.*/
node_t *list_lookup(list_t *list, int key);


