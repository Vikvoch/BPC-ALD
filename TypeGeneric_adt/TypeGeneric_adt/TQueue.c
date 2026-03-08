/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí kruhového pole)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TQueue.c 3215 2026-02-20 16:26:16Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

[[nodiscard]] static inline bool queue_invariant(const struct TQueue *aQueue)
{
	return aQueue->iFrontPos < QUEUE_MAXCOUNT && aQueue->iBackPos <QUEUE_MAXCOUNT;
}

void queue_init(struct TQueue *aQueue)
{
	if(aQueue == NULL)
		return;
	aQueue->iFrontPos = 0;
	aQueue->iBackPos  = 0;
	assert(queue_invariant(aQueue));
}

bool queue_is_empty(const struct TQueue *aQueue)
{
	if(aQueue == NULL)
		return true;
	assert(queue_invariant(aQueue));
	return aQueue->iFrontPos == aQueue->iBackPos;
}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
{
	if(queue_is_empty(aQueue) || aValue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	*aValue = aQueue->iValues[aQueue->iFrontPos];
	assert(queue_invariant(aQueue));
	return true;
}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
{
	if(queue_is_empty(aQueue) || aValue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	if(aQueue->iBackPos == 0)
		*aValue = aQueue->iValues[QUEUE_MAXCOUNT - 1];
	else	
		*aValue = aQueue->iValues[aQueue->iBackPos - 1];
	assert(queue_invariant(aQueue));
	return true;
}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
{
	if(aQueue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	// pokud je málo pamìti:
	/*if((aQueue->iBackPos + 1) % QUEUE_MAXCOUNT == aQueue->iFrontPos)
		return false;
	else
		aQueue->iValues[aQueue->iBackPos] = aValue;
	aQueue->iBackPos = (aQueue->iBackPos + 1) % QUEUE_MAXCOUNT;*/
	const size_t nextPos = (aQueue->iBackPos + 1) % QUEUE_MAXCOUNT;
	if(nextPos == aQueue->iFrontPos)
		return false;
	else
		aQueue->iValues[aQueue->iBackPos] = aValue;
	aQueue->iBackPos = nextPos;
	assert(queue_invariant(aQueue));
	return true;
}

bool queue_pop(struct TQueue *aQueue)
{
	if(queue_is_empty(aQueue))
		return false;
	assert(queue_invariant(aQueue));
	aQueue->iFrontPos = (aQueue->iFrontPos + 1) % QUEUE_MAXCOUNT;
	assert(queue_invariant(aQueue));
	return true;
}

void queue_destroy(struct TQueue *aQueue)
{
	if(queue_is_empty(aQueue))
		return;
	aQueue->iFrontPos = 0;
	aQueue->iBackPos  = 0;
}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
{
	if(aQueue == NULL || (aQueue->iFrontPos == aQueue->iBackPos))
		return (struct TQueueIterator) { .iQueue = NULL, .iPos = 0 };
	return (struct TQueueIterator) { .iQueue = aQueue, .iPos = aQueue->iFrontPos };

}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
{
	if(aIter == NULL || aIter->iQueue == NULL)
		return false;
	if(queue_is_empty(aIter->iQueue))
		return false;
	if(aIter->iPos == aIter->iQueue->iBackPos)
		return false;
	return aIter->iPos < QUEUE_MAXCOUNT;
}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
{
	if(aIter == NULL || !queue_iterator_is_valid(aIter))
		return false;
	aIter->iPos = (aIter->iPos + 1) % QUEUE_MAXCOUNT;
	if(aIter->iPos == aIter->iQueue->iBackPos)
		return false;
	return true;
}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
{
	if(!queue_iterator_is_valid(aIter))
		return (TQueueElement) { 0 };
	return (TQueueElement) { aIter->iQueue->iValues[aIter->iPos] };
	
}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
{
	if(!queue_iterator_is_valid(aIter))
		return false;
	((struct TQueue*)aIter->iQueue)->iValues[aIter->iPos] = aValue;
	return true;
}
