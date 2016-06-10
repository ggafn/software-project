/*
 * SPBPriorityQueue.c
 *
 *  Created on: May 26, 2016
 *      Author: MattFryd
 */

#include "SPBPriorityQueue.h"
#include "SPList.h"
#include "SPListElement.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct sp_bp_queue_t {
	int maxSize;
	SPList queue;
};

SPBPQueue spBPQueueCreate(int maxSize) {
	if (maxSize < 1) {								// Invalid Size Bound
		return NULL;
	}
	SPBPQueue this = (SPBPQueue) malloc(sizeof(struct sp_bp_queue_t));
	SPList queue = spListCreate();
	if (!this || !queue) {							// Allocation failure
		return NULL;
	}
	this->maxSize = maxSize;
	this->queue = queue;
	return this;
}

SPBPQueue spBPQueueCopy(SPBPQueue source) {
	SPBPQueue this;
	SPList queue;

	if (!source) {									// Invalid input
		return NULL;
	}

	queue = spListCopy(source->queue);
	if (!queue) {									// Allocation failure
		return NULL;
	}

	this = (SPBPQueue) malloc(sizeof(struct sp_bp_queue_t));
	if (!this) {									// Allocation failure
		return NULL;
	}

	this->maxSize = source->maxSize;
	this->queue = queue;
	return this;
}

void spBPQueueDestroy(SPBPQueue source) {
	if (!source) {									// NULL input
		return;
	}
	spListDestroy(source->queue);
	free(source);
}

void spBPQueueClear(SPBPQueue source) {
	if (!source) {									// NULL input
		return;
	}
	spListClear(source->queue);
}

int spBPQueueSize(SPBPQueue source) {
	if (!source) {									// Invalid input
		return -1;
	}
	return spListGetSize(source->queue);
}

int spBPQueueGetMaxSize(SPBPQueue source) {
	if (!source) {									// Invalid input
		return -1;
	}
	return source->maxSize;
}

SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element) {
	SPListElement i;
	SPListElement input;
	if (!element || !source) {						// Invalid input
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	input = spListElementCopy(element);
	if (!input) {									// Allocation Failure
		return SP_BPQUEUE_OUT_OF_MEMORY;
	}
	if (spBPQueueIsEmpty(source)) {
		spListInsertFirst(source->queue, input);
		spListElementDestroy(input);
		return SP_BPQUEUE_SUCCESS;
	}

	if (spBPQueueIsFull(source)) {					// QUEUE IS FULL
		i = spBPQueuePeekLast(source);
		if (spListElementCompare(input, i) != -1) {	// Input element's value is greater or
			spListElementDestroy(i);				// equals the current maximal value
			spListElementDestroy(input);
			return SP_BPQUEUE_FULL;
		}
		else {										// Input should be inserted
			spListRemoveCurrent(source->queue);
			spListElementDestroy(i);
		}
	}

	i = spListGetFirst(source->queue);
	while (i != NULL) {								// Iterate over the queue
		if (spListElementCompare(input, i) != 1) {	// input->value <= i->value
			spListInsertBeforeCurrent(source->queue, input);
			spListElementDestroy(input);
			return SP_BPQUEUE_SUCCESS;
		}
		i = spListGetNext(source->queue);
	}
	spListInsertLast(source->queue, input);
	spListElementDestroy(input);
	return SP_BPQUEUE_SUCCESS;
}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source) {
	if (!source) {									// Invalid input
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	if (spBPQueueIsEmpty(source)) {
		return SP_BPQUEUE_EMPTY;
	}
	spListGetFirst(source->queue);
	spListRemoveCurrent(source->queue);
	return SP_BPQUEUE_SUCCESS;
}

SPListElement spBPQueuePeek(SPBPQueue source) {
	if (!source || spBPQueueIsEmpty(source)) {
		return NULL;
	}
	return spListElementCopy(spListGetFirst(source->queue));
}

SPListElement spBPQueuePeekLast(SPBPQueue source) {
	if (!source || spBPQueueIsEmpty(source)) {
		return NULL;
	}
	return spListElementCopy(spListGetLast(source->queue));
}

double spBPQueueMinValue(SPBPQueue source) {
	SPListElement minElement;
	double minValue;

	if (!source || spBPQueueIsEmpty(source)) {
		return -1;
	}

	minElement = spBPQueuePeek(source);
	minValue = spListElementGetValue(minElement);
	spListElementDestroy(minElement);
	return minValue;
}

double spBPQueueMaxValue(SPBPQueue source) {
	SPListElement maxElement;
	double maxValue;

	if (!source || spBPQueueIsEmpty(source)) {
		return -1;
	}

	maxElement = spBPQueuePeekLast(source);
	maxValue = spListElementGetValue(maxElement);
	spListElementDestroy(maxElement);
	return maxValue;
}

bool spBPQueueIsEmpty(SPBPQueue source) {
	assert(source != NULL);
	return (spListGetSize(source->queue) == 0);
}

bool spBPQueueIsFull(SPBPQueue source) {
	assert(source != NULL);
	return (spListGetSize(source->queue) == source->maxSize);
}
