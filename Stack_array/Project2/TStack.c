/** \file TStack.c
 *  \brief Implementace API pro typ zásobník (realizace pomocí pole)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TStack.c 3201 2026-02-13 18:07:58Z petyovsky $
 */

#include <assert.h>
#include "TStack.h"

[[nodiscard]] static inline bool stack_invariant(const struct TStack *aStack)
{
	return aStack->iCount <= aStack->iCapacity;
}

void stack_init(struct TStack *aStack)
{
	if(aStack == NULL)
		return;
	aStack->iCount = 0;
	aStack->iCapacity = 0;
	assert(stack_invariant(aStack));
}

bool stack_is_empty(const struct TStack *aStack)
{
	if(aStack == NULL)
		return 1;
	assert(stack_invariant(aStack));
	return !aStack->iCount;
}

bool /* TStackIterator */ stack_top(const struct TStack *aStack, TStackElement *aValue)
{
	if(aValue == NULL || stack_is_empty(aStack))
		return 0;
	assert(stack_invariant(aStack));
	*aValue = aStack->iValues[aStack->iCount - 1];
	return 1;
}

bool stack_push(struct TStack *aStack, TStackElement aValue)
{
	if(aStack == NULL)
		return 0;
	assert(stack_invariant(aStack));
	if(aStack->iCount == aStack->iCapacity)
	{
		size_t newCapacity;
		if(aStack->iCapacity == 0)
			newCapacity = 1;
		else
			newCapacity = aStack->iCapacity * 2;
		TStackElement *newData;
		newData= malloc(newCapacity * sizeof(TStackElement));
		if(newData == NULL)
			return false;
		for(size_t i = 0; i < aStack->iCount; i++)
			newData[i] = aStack->iValues[i];
		free(aStack->iValues);
		aStack->iValues = newData;
		aStack->iCapacity = newCapacity;
	}
	aStack->iValues[aStack->iCount++] = aValue;
	assert(stack_invariant(aStack));
	return 1;
}

bool stack_pop(struct TStack *aStack)
{
	if(aStack == NULL || stack_is_empty(aStack))
		return 0;
	assert(stack_invariant(aStack));
	--aStack->iCount;
	if(aStack->iCount <= aStack->iCapacity / 4)
	{
		size_t newCapacity = aStack->iCapacity / 2;
		TStackElement *newData;
		newData = calloc(newCapacity, sizeof(TStackElement));
		if(newData == NULL)
			return false;
		for(size_t i = 0; i < aStack->iCount; i++)
			newData[i] = aStack->iValues[i];
		free(aStack->iValues);
		aStack->iValues = newData;
		aStack->iCapacity = newCapacity;
	}
	assert(stack_invariant(aStack));
	return 1;
}

void stack_destroy(struct TStack *aStack)
{
	if(aStack == NULL)
		return;
	assert(stack_invariant(aStack));
	free(aStack->iValues);
	aStack->iCapacity = 0;
	aStack->iCount = 0;
	assert(stack_invariant(aStack));
}

struct TStackIterator stack_iterator_begin(const struct TStack *aStack)
{
	if(aStack == NULL || aStack->iCount == 0)
		return (struct TStackIterator) { .iStack = NULL, .iPos = 0 };
	assert(stack_invariant(aStack));
	return (struct TStackIterator) { .iStack = aStack, .iPos = aStack->iCount - 1 };
}

bool stack_iterator_is_valid(const struct TStackIterator *aIter)
{
	if(aIter == NULL || aIter->iStack == NULL)
		return 0;
	return aIter->iPos < aIter->iStack->iCount;
}

bool stack_iterator_to_next(struct TStackIterator *aIter)
{
	if(aIter == NULL || aIter->iStack == NULL)
		return 0;
	if(aIter->iPos == 0 || !stack_invariant(aIter->iStack))
	{
		aIter->iPos = 0;
		aIter->iStack = NULL;
		return 0;
	}
	--aIter->iPos;
	return stack_iterator_is_valid(aIter);
}

TStackElement stack_iterator_value(const struct TStackIterator *aIter)
{
	if(!stack_iterator_is_valid(aIter))
		return (TStackElement) { 0 };
	return aIter->iStack->iValues[aIter->iPos];
}
