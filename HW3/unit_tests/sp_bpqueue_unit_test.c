/*
 * sp_bpqueue_unit_test.c
 *
 *  Created on: Jun 6, 2016
 *      Author: MattFryd
 */

#include "../SPBPriorityQueue.h"
#include "../SPListElement.h"
#include "../SPList.h"
#include "unit_test_util.h"
#include <stdbool.h>

#define CREATE_ELEMENTS() \
	SPListElement e1 = spListElementCreate(1, 1); \
	SPListElement e2 = spListElementCreate(2, 2); \
	SPListElement e3 = spListElementCreate(3, 3); \
	SPListElement e4 = spListElementCreate(4, 4); \
	SPListElement e5 = spListElementCreate(5, 5);

#define FREE_ELEMENTS() \
	spListElementDestroy(e1); \
	spListElementDestroy(e2); \
	spListElementDestroy(e3); \
	spListElementDestroy(e4); \
	spListElementDestroy(e5);

bool bpqueueCreateTest() {

	SPBPQueue queue = spBPQueueCreate(4);

	if (queue == NULL) {
		return false;
	}

	spBPQueueDestroy(queue);
	return true;
}

bool bpqueueCopyTest() {

	SPBPQueue queue;
	SPBPQueue copy;
	CREATE_ELEMENTS();

	copy = spBPQueueCopy(NULL);
	if (copy != NULL) {
		FREE_ELEMENTS()
		return false;
	}

	queue = spBPQueueCreate(4);
	copy = spBPQueueCopy(queue);
	if (spBPQueueSize(copy) != spBPQueueSize(queue) ||
			spBPQueueGetMaxSize(copy) != spBPQueueGetMaxSize(queue)) {
		spBPQueueDestroy(queue);
		spBPQueueDestroy(copy);
		FREE_ELEMENTS()
		return false;
	}
	spBPQueueDestroy(copy);

	spBPQueueEnqueue(queue, e3);
	spBPQueueEnqueue(queue, e2);
	spBPQueueEnqueue(queue, e4);
	spBPQueueEnqueue(queue, e1);

	copy = spBPQueueCopy(queue);
	if (spBPQueueSize(copy) != spBPQueueSize(queue) ||
			spBPQueueGetMaxSize(copy) != spBPQueueGetMaxSize(queue)) {
		spBPQueueDestroy(queue);
		spBPQueueDestroy(copy);
		FREE_ELEMENTS()
		return false;
	}

	while (spBPQueueMinValue(queue) != -1) {
		if (spBPQueueMinValue(copy) != spBPQueueMinValue(queue)) {
			spBPQueueDestroy(queue);
			spBPQueueDestroy(copy);
			FREE_ELEMENTS()
			return false;
		}
		spBPQueueDequeue(queue);
		spBPQueueDequeue(copy);
	}

	if (spBPQueueMinValue(copy) != -1) {
		spBPQueueDestroy(queue);
		spBPQueueDestroy(copy);
		FREE_ELEMENTS()
		return false;
	}

	spBPQueueDestroy(queue);
	spBPQueueDestroy(copy);
	FREE_ELEMENTS()
	return true;
}

bool bpqueueClearTest() {

	SPBPQueue queue = spBPQueueCreate(4);
	CREATE_ELEMENTS();

	spBPQueueEnqueue(queue, e2);
	spBPQueueEnqueue(queue, e1);
	spBPQueueEnqueue(queue, e3);

	spBPQueueClear(queue);
	if (!spBPQueueIsEmpty(queue) || spBPQueueGetMaxSize(queue) != 4) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueSizeTest() {

	SPBPQueue queue;
	CREATE_ELEMENTS();
	int i;

	if (spBPQueueSize(NULL) != -1) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueSize(queue) != 0) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	for (i=1; i<4; i++) {
		spBPQueueEnqueue(queue, e1);
		if (spBPQueueSize(queue) != i) {
			spBPQueueDestroy(queue);
			FREE_ELEMENTS();
			return false;
		}
	}

	spBPQueueEnqueue(queue, e1);
	if (spBPQueueSize(queue) != 4) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueMaxSizeTest() {

	SPBPQueue queue;

	if (spBPQueueGetMaxSize(NULL) != -1) {
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueGetMaxSize(queue) != 4) {
		spBPQueueDestroy(queue);
		return false;
	}

	spBPQueueDestroy(queue);
	return true;
}

bool bpqueueEnqueueTest() {

	SPBPQueue queue;
	CREATE_ELEMENTS();

	if (spBPQueueEnqueue(NULL, e1) != SP_BPQUEUE_INVALID_ARGUMENT) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueEnqueue(queue, NULL) != SP_BPQUEUE_INVALID_ARGUMENT) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	if (spBPQueueEnqueue(queue, e3) != SP_BPQUEUE_SUCCESS ||
			spBPQueueEnqueue(queue, e2) != SP_BPQUEUE_SUCCESS ||
			spBPQueueEnqueue(queue, e5) != SP_BPQUEUE_SUCCESS ||
			spBPQueueEnqueue(queue, e4) != SP_BPQUEUE_SUCCESS ||
			spBPQueueEnqueue(queue, e1) != SP_BPQUEUE_SUCCESS) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	if (spBPQueueEnqueue(queue, e5) != SP_BPQUEUE_FULL) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueDequeueTest() {

	SPBPQueue queue;
	CREATE_ELEMENTS();
	int i;

	if (spBPQueueDequeue(NULL) != SP_BPQUEUE_INVALID_ARGUMENT) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueDequeue(queue) != SP_BPQUEUE_EMPTY) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e3);
	spBPQueueEnqueue(queue, e2);
	spBPQueueEnqueue(queue, e4);
	spBPQueueEnqueue(queue, e1);

	for (i=0; i<4; i++) {
		if (spBPQueueDequeue(queue) != SP_BPQUEUE_SUCCESS) {
			spBPQueueDestroy(queue);
			FREE_ELEMENTS();
			return false;
		}
	}

	if (spBPQueueDequeue(queue) != SP_BPQUEUE_EMPTY) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueuePeekTest() {

	SPBPQueue queue;
	SPListElement element;
	CREATE_ELEMENTS();

	if (spBPQueuePeek(NULL) != NULL) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueuePeek(queue) != NULL) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e3);
	element = spBPQueuePeek(queue);
	if (spListElementGetIndex(element) != 3 ||
			spListElementGetValue(element) != 3) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e2);
	element = spBPQueuePeek(queue);
	if (spListElementGetIndex(element) != 2 ||
			spListElementGetValue(element) != 2) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e4);
	element = spBPQueuePeek(queue);
	if (spListElementGetIndex(element) != 2 ||
			spListElementGetValue(element) != 2) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e1);
	element = spBPQueuePeek(queue);
	if (spListElementGetIndex(element) != 1 ||
			spListElementGetValue(element) != 1) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueDequeue(queue);
	element = spBPQueuePeek(queue);
	if (spListElementGetIndex(element) != 2 ||
			spListElementGetValue(element) != 2) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}

	spListElementDestroy(element);
	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueuePeekLastTest() {

	SPBPQueue queue;
	SPListElement element;
	CREATE_ELEMENTS();

	if (spBPQueuePeekLast(NULL) != NULL) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueuePeekLast(queue) != NULL) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e3);
	element = spBPQueuePeekLast(queue);
	if (spListElementGetIndex(element) != 3 ||
			spListElementGetValue(element) != 3) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e2);
	element = spBPQueuePeekLast(queue);
	if (spListElementGetIndex(element) != 3 ||
			spListElementGetValue(element) != 3) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e4);
	element = spBPQueuePeekLast(queue);
	if (spListElementGetIndex(element) != 4 ||
			spListElementGetValue(element) != 4) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e5);
	element = spBPQueuePeekLast(queue);
	if (spListElementGetIndex(element) != 5 ||
			spListElementGetValue(element) != 5) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}
	spListElementDestroy(element);

	spBPQueueEnqueue(queue, e1);
	element = spBPQueuePeekLast(queue);
	if (spListElementGetIndex(element) != 4 ||
			spListElementGetValue(element) != 4) {
		spBPQueueDestroy(queue);
		spListElementDestroy(element);
		FREE_ELEMENTS();
		return false;
	}

	spListElementDestroy(element);
	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueMinValueTest() {

	SPBPQueue queue;
	CREATE_ELEMENTS();

	if (spBPQueueMinValue(NULL) != -1) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueMinValue(queue) != -1) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e3);
	if (spBPQueueMinValue(queue) != 3) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e2);
	if (spBPQueueMinValue(queue) != 2) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e4);
	if (spBPQueueMinValue(queue) != 2) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e1);
	if (spBPQueueMinValue(queue) != 1) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDequeue(queue);
	if (spBPQueueMinValue(queue) != 2) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueMaxValueTest() {

	SPBPQueue queue;
	CREATE_ELEMENTS();

	if (spBPQueueMaxValue(NULL) != -1) {
		FREE_ELEMENTS();
		return false;
	}

	queue = spBPQueueCreate(4);

	if (spBPQueueMaxValue(queue) != -1) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e3);
	if (spBPQueueMaxValue(queue) != 3) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e2);
	if (spBPQueueMaxValue(queue) != 3) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e4);
	if (spBPQueueMaxValue(queue) != 4) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e5);
	if (spBPQueueMaxValue(queue) != 5) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e1);
	if (spBPQueueMaxValue(queue) != 4) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueIsEmptyTest() {

	SPBPQueue queue = spBPQueueCreate(4);
	CREATE_ELEMENTS();

	if (!spBPQueueIsEmpty(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e1);

	if (spBPQueueIsEmpty(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDequeue(queue);
	if (!spBPQueueIsEmpty(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e1);
	spBPQueueClear(queue);
	if (!spBPQueueIsEmpty(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}

bool bpqueueIsFullTest() {

	SPBPQueue queue = spBPQueueCreate(2);
	CREATE_ELEMENTS();

	if (spBPQueueIsFull(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e1);
	if (spBPQueueIsFull(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueEnqueue(queue, e2);
	if (!spBPQueueIsFull(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDequeue(queue);
	if (spBPQueueIsFull(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueClear(queue);
	if (spBPQueueIsFull(queue)) {
		spBPQueueDestroy(queue);
		FREE_ELEMENTS();
		return false;
	}

	spBPQueueDestroy(queue);
	FREE_ELEMENTS();
	return true;
}
///*
int main() {
	RUN_TEST(bpqueueCreateTest);
	RUN_TEST(bpqueueCopyTest);
	RUN_TEST(bpqueueClearTest);
	RUN_TEST(bpqueueSizeTest);
	RUN_TEST(bpqueueMaxSizeTest);
	RUN_TEST(bpqueueEnqueueTest);
	RUN_TEST(bpqueueDequeueTest);
	RUN_TEST(bpqueueMinValueTest);
	RUN_TEST(bpqueueMaxValueTest);
	RUN_TEST(bpqueueIsEmptyTest);
	RUN_TEST(bpqueueIsFullTest);
	RUN_TEST(bpqueuePeekTest);
	RUN_TEST(bpqueuePeekLastTest);



	return 0;
}
//*/
