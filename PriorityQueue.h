//taken from https://rosettacode.org/wiki/Priority_queue#C
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int priority;
	void **data;
} node_t;

typedef struct {
	node_t *nodes;
	int len;
	int size;
} heap_t;

void pQueuePush(heap_t *h, int priority, void const *);
void *pQueuePop(heap_t *h);
bool pQueueIsEmpty(heap_t *h);
void pQueueClear(heap_t *h, int flag);//flag determines deallocate or not. 1 - deallocate, 0, just sets len to 0
void pQueueInit(heap_t *h);

#endif