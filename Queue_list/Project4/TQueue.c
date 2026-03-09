/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí lineárního jednosmìrnì vázaného seznamu)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TQueue.c 3215 2026-02-20 16:26:16Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

 /** \brief Úplná definice privátního typu QueueNode
  *  \details Privátní typ QueueNode (nedostupný mimo funkce ze souboru TQueue.c) reprezentuje typ pro jednotlivé uzly lineárního jednosmìrnì vázaného seznamu.
  */
struct TQueueNode {
	struct TQueueNode *iNext;				///< Ukazatel na následující uzel lineárního jednosmìrnì vázaného seznamu
	TQueueElement iValue;					///< Element fronty uložený v uzlu lineárního jednosmìrnì vázaného seznamu
};

[[nodiscard]] static inline bool queue_invariant(const struct TQueue *aQueue)
{
	return (aQueue->iFront == NULL && aQueue->iBack == NULL) || (aQueue->iFront != NULL && aQueue->iBack != NULL);
}

void queue_init(struct TQueue *aQueue)
{
	if(aQueue == NULL)
		return;
	aQueue->iFront = NULL;
	aQueue->iBack = NULL;
}

bool queue_is_empty(const struct TQueue *aQueue)
{
	if(aQueue == NULL)
		return true;
	assert(queue_invariant(aQueue));
	return aQueue->iFront == NULL;
}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
{
	if(queue_is_empty(aQueue) || aValue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	*aValue = aQueue->iFront->iValue;
	assert(queue_invariant(aQueue));
	return true;
}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
{
	if(queue_is_empty(aQueue) || aValue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	*aValue = aQueue->iBack->iValue;
	assert(queue_invariant(aQueue));
	return true;
}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
{
	if(aQueue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	struct TQueueNode *new_node = malloc(sizeof(struct TQueueNode));
	if(new_node == NULL)
		return false;
	new_node->iValue = aValue;
	new_node->iNext = NULL;
	if(queue_is_empty(aQueue))
		aQueue->iFront = new_node;
	else
		aQueue->iBack->iNext = new_node;
	aQueue->iBack = new_node;
	assert(queue_invariant(aQueue));
	return true;
}

bool queue_push_front(struct TQueue *aQueue, TQueueElement aValue)
{
	if(aQueue == NULL)
		return false;
	assert(queue_invariant(aQueue));
	struct TQueueNode *new_node = malloc(sizeof(struct TQueueNode));
	if(new_node == NULL)
		return false;
	new_node->iValue = aValue;
	new_node->iNext = aQueue->iFront;
	aQueue->iFront = new_node;
	if(aQueue->iBack == NULL)
		aQueue->iBack = new_node;
	assert(queue_invariant(aQueue));
	return true;
}

bool queue_pop(struct TQueue *aQueue)
{
	if(aQueue == NULL || queue_is_empty(aQueue))
		return false;
	assert(queue_invariant(aQueue));
	struct TQueueNode *front_node = aQueue->iFront;
	aQueue->iFront = front_node->iNext;
	if(aQueue->iFront == NULL)
		aQueue->iBack = NULL;
	free(front_node);
	assert(queue_invariant(aQueue));
	assert(queue_invariant(aQueue));
	return true;
}

void queue_destroy(struct TQueue *aQueue)
{
	if(aQueue == NULL)
		return;
	assert(queue_invariant(aQueue));
	while(queue_pop(aQueue));
	assert(queue_invariant(aQueue));
}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
{
	if(aQueue == NULL || queue_is_empty(aQueue))
		return (struct TQueueIterator) { .iQueue = NULL, .iActual = NULL };
	return (struct TQueueIterator) { .iQueue = aQueue, .iActual = aQueue->iFront };
}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
{
	if(aIter == NULL || aIter->iQueue == NULL || queue_is_empty(aIter->iQueue))
		return false;
	if(aIter->iActual == NULL)
		return false;
	return true;
}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
{
	if(!queue_iterator_is_valid(aIter))
	{
		aIter->iQueue = NULL;
		return false;
	}
	aIter->iActual = aIter->iActual->iNext;
	if(aIter->iActual == NULL)
	{
		aIter->iQueue = NULL;
		return false;
	}
	return true;
}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
{
	if(!queue_iterator_is_valid(aIter))
		return (TQueueElement) { 0 };
	return aIter->iActual->iValue;
}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
{
	if(!queue_iterator_is_valid(aIter))
		return false;
	aIter->iActual->iValue = aValue;
	return true;
}
