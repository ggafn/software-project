#ifndef SPBPRIORITYQUEUE_H_
#define SPBPRIORITYQUEUE_H_
#include "SPListElement.h"
#include <stdbool.h>
/**
 * Bounded Priority-Queue Summary
 *
 * Implementation of a Bounded Priority-Queue (BPQ) using a singly linked list.
 * The queue itself is of type SPList, please refer to SPList.h for usage.
 * The elements of the queue are of type SPListElement, please refer
 * to SPListElement.h for usage.
 *
 * The following functions are available:
 *
 *   spBPQueueCreate		- Creates a new empty BPQ.
 *   spBPQueueCopy			- Copies an existing BPQ.
 *   spBPQueueDestroy		- Frees all memory allocations associated with a BPQ.
 *   spBPQueueClear			- Clears all elements from a BPQ.
 *   spBPQueueSize			- Returns the current number of elements.
 *   spBPQueueGetMaxSize	- Returns a BPQ's size bound.
 *   spBPQueueEnqueue		- Inserts a new element into a BPQ.
 *   spBPQueueDequeue		- Removes the minimal element from a BPQ.
 *   spBPQueuePeek			- Returns the element whose value is minimal.
 *   spBPQueuePeekLast		- Returns the element whose value is maximal.
 *   spBPQueueMinValue		- Returns the BPQ's minimal value.
 *   spBPQueueMaxValue		- Returns the BPQ's maximal value.
 *   spBPQueueIsEmpty       - Decides whether a BPQ is empty.
 *   spBPQueueIsFull		- Decides whether a BPQ is full.
 */


/** type used to define Bounded priority queue **/
typedef struct sp_bp_queue_t* SPBPQueue;

/** type for error reporting **/
typedef enum sp_bp_queue_msg_t {
	SP_BPQUEUE_OUT_OF_MEMORY,
	SP_BPQUEUE_FULL,
	SP_BPQUEUE_EMPTY,
	SP_BPQUEUE_INVALID_ARGUMENT,
	SP_BPQUEUE_SUCCESS
} SP_BPQUEUE_MSG;

/**
 * Creates a new BPQ with the given size bound.
 *
 * @param maxSize - The size bound of the queue.
 * @return
 * NULL in case of a memory allocation failure or if the input bound is less than 1;
 * The new BPQ otherwise.
 */
SPBPQueue spBPQueueCreate(int maxSize);

/**
 * Creates a copy of a given BPQ.
 *
 * @param source - The queue to be copied.
 * @return
 * NULL in case of a memory allocation failure;
 * The new copy BPQ otherwise.
 */
SPBPQueue spBPQueueCopy(SPBPQueue source);

/**
 * Frees all memory allocations associated with a BPQ.
 * Does nothing if given a NULL argument.
 *
 * @param source - The queue to be destroyed.
 */
void spBPQueueDestroy(SPBPQueue source);

/**
 * Clears a BPQ of all its elements.
 * Does nothing if given a NULL argument (or if the queue is already empty).
 *
 * @param source - The queue to be cleared.
 */
void spBPQueueClear(SPBPQueue source);

/**
 * Returns the number of elements of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * -1 if given a NULL argument;
 * The queue size otherwise.
 */
int spBPQueueSize(SPBPQueue source);

/**
 * Returns the size bound of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * -1 if given a NULL argument;
 * The queue size bound otherwise.
 */
int spBPQueueGetMaxSize(SPBPQueue source);

/**
 * Inserts a new element to a given BPQ.
 * If the queue is at full capacity, only elements whose values are
 * strictly less than the current maximal value will be inserted. In
 * that case, the current maximal element will be removed from the queue.
 *
 * @param source - The input BPQ.
 * @param element - The new element to insert.
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT if given NULL arguments;
 * SP_BPQUEUE_OUT_OF_MEMORY in case of a memory allocation failure;
 * SP_BPQUEUE_FULL if the queue is full AND the new element's value
 *  is greater or equals the current maximal value of the BPQ;
 * SP_BPQUEUE_SUCCESS otherwise (i.e. the insertion succeeded).
 */
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element);

/**
 * Removes the minimal element from a given BPQ.
 * If there are several elements holding the minimal value, the element
 * which was inserted last (chronologically) will be removed first.
 *
 * @param source - The input BPQ.
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT if given a NULL argument;
 * SP_BPQUEUE_OUT_OF_MEMORY in case of a memory allocation failure;
 * SP_BPQUEUE_EMPTY if the queue is empty;
 * SP_BPQUEUE_SUCCESS otherwise (i.e. the removal succeeded).
 */
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source);

/**
 * Returns the minimal (first) list element of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * NULL if given a NULL argument, if the input queue is empty or in
 * 	case of a memory allocation failure;
 * A copy of the minimal element otherwise.
 */
SPListElement spBPQueuePeek(SPBPQueue source);

/**
 * Returns the maximal (last) list element of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * NULL if given a NULL argument, if the input queue is empty or in
 * 	case of a memory allocation failure;
 * A copy of the maximal element otherwise.
 */
SPListElement spBPQueuePeekLast(SPBPQueue source);

/**
 * Returns the minimal value of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * -1 if given a NULL argument or if the input queue is empty;
 * The minimal value otherwise.
 */
double spBPQueueMinValue(SPBPQueue source);

/**
 * Returns the maximal value of a given BPQ.
 *
 * @param source - The query queue.
 * @return
 * -1 if given a NULL argument or if the input queue is empty;
 * The maximal value otherwise.
 */
double spBPQueueMaxValue(SPBPQueue source);

/**
 * Decides whether a given BPQ is empty.
 *
 * @param source - The query queue.
 * @assert source != NULL
 * @return
 * True if the input queue is empty;
 * False otherwise.
 */
bool spBPQueueIsEmpty(SPBPQueue source);

/**
 * Decides whether a given BPQ is full, i.e. if its size equals its size bound.
 *
 * @param source - The query queue.
 * @assert source != NULL
 * @return
 * True if the input queue is full;
 * False otherwise.
 */
bool spBPQueueIsFull(SPBPQueue source);

#endif
