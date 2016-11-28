#include "PriorityQueue.h"

void pQueuePush(heap_t *h, int priority, void *data) {
	if (h->len + 1 >= h->size) {
		h->size = h->size ? h->size * 2 : 4;
		h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
	}
	int i = h->len + 1;
	int j = i / 2;
	while (i > 1 && h->nodes[j].priority > priority) {
		h->nodes[i] = h->nodes[j];
		i = j;
		j = j / 2;
	}
	h->nodes[i].priority = priority;
	h->nodes[i].data = data;
	h->len++;
}

void *pQueuePop(heap_t *h) {
	int i, j, k;
	if (!h->len) {
		return NULL;
	}
	void *data = h->nodes[1].data;
	h->nodes[1] = h->nodes[h->len];
	h->len--;
	i = 1;
	while (1) {
		k = i;
		j = 2 * i;
		if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
			k = j;
		}
		if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
			k = j + 1;
		}
		if (k == i) {
			break;
		}
		h->nodes[i] = h->nodes[k];
		i = k;
	}
	h->nodes[i] = h->nodes[h->len + 1];
	return data;
}


bool pQueueIsEmpty(heap_t *h){
	if (h->len >= 0)
		return false;
	else
		return true;
}

void pQueueClear(heap_t *h, int i){
	h->len = 0;
	if (i == 1)
		free(h);
}

void pQueueInit(heap_t *h){
	if (h->size > 0)
		return;
	h->size = 4;
	h->len = 0;
	h->nodes = (node_t *)malloc(h->size * sizeof (node_t));
}
