/** \file TVector.c
 *  \brief Implementace Basic Vector API
 *  \author Petyovsk?
 *  \version 2026
 *  $Id: TVector.c 3192 2026-02-08 18:45:10Z petyovsky $
 */

#include <stdlib.h>
#include <assert.h>
#include "TVector.h"
#include "check.h"

[[nodiscard]] static inline bool vector_invariant(const struct TVector *aVector)
{
	return ((!aVector->iValues && !aVector->iSize) || (aVector->iValues && aVector->iSize));
}

bool vector_init(struct TVector *aVector, size_t aSize)
{
	if(aVector == NULL || aSize)
		return 0;
	TVectorElement *new_values;
	new_values = calloc(aSize, sizeof(TVectorElement));
	if(new_values == NULL)
		return 0;
	aVector->iValues = new_values;
	aVector->iSize = aSize;
	assert(vector_invariant(aVector));
	return 1;
}

bool vector_init_random(struct TVector *aVector, size_t aSize)
{
	if(aVector == NULL || aSize)
		return 0;
	TVectorElement *new_values;
	new_values = malloc(aSize * sizeof(TVectorElement));
	if(new_values == NULL)
		return 0;
	for(size_t i = 0; i < aSize; ++i)
		new_values[i] = vector_element_random_value();
	aVector->iValues = new_values;
	aVector->iSize = aSize;
	assert(vector_invariant(aVector));
	return 1;
}

bool vector_init_file(struct TVector *aVector, FILE *aInputFile)
{
	if(aVector == NULL || aInputFile == NULL)
		return 0;
	size_t new_size = 0;
	if(fscanf(aInputFile, "%zu", &new_size) != 1)
		return 0;
	TVectorElement *new_values;
	new_values = malloc(new_size * sizeof(TVectorElement));
	if(new_values == NULL)
		return 0;
	for(size_t i = 0; i < new_size; ++i)
	{
		if(!vector_element_load_file(&new_values[i], aInputFile))
		{
			free(new_values);
			return 0;
		}
	}
	aVector->iValues = new_values;
	aVector->iSize = new_size;
	assert(vector_invariant(aVector));
	return 1;
}

bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone)
{
	if(aVector == NULL || aVectorClone == NULL)
		return 0;
	assert(vector_invariant(aVector));
	if(aVector == aVectorClone)
		return 1;
	assert(vector_invariant(aVectorClone));

	TVectorElement *act_values = aVectorClone->iValues;
	if(aVector->iSize != aVectorClone->iSize)
	{
		TVectorElement *new_values = NULL;
		if(aVector->iSize)
		{
			new_values = malloc(aVector->iSize * sizeof(TVectorElement));
			if(new_values == NULL)
				return 0;
			free(act_values);
			act_values = new_values;
		}
	}
	for(size_t i = 0; i < aVectorClone->iSize; ++i)
		act_values[i] = aVector->iValues[i];
	aVectorClone->iValues = act_values;
	aVectorClone->iSize = aVector->iSize;
	assert(vector_invariant(aVector));
	assert(vector_invariant(aVectorClone));
	return 1;
}

bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile)
{
	if(aVector == NULL || aOutputFile == NULL)
		return 0;
	assert(vector_invariant(aVector));
	if(fprintf(aOutputFile, "%zu", aVector->iSize) < 2)
		return 0;
	for(size_t i = 0; i < aVector->iSize; i++)
	{
		if(!vector_element_store_file(aVector->iValues, aOutputFile))
			return 0;
	}
	assert(vector_invariant(aVector));
	return 1;
}

TVectorElement vector_value(const struct TVector *aVector, size_t aPos)
{
	if(aVector == NULL)
		return 0;
	assert(aVector);
	assert(aVector->iSize > aPos);
	assert(vector_invariant(aVector));

	return aVector->iValues[aPos];
}

void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue)
{
	if(aVector == NULL)
		return;
	assert(aVector);
	assert(aVector->iSize > aPos);
	assert(vector_invariant(aVector));

	aVector->iValues[aPos] = aValue;
	assert(aVector);
}

size_t vector_size(const struct TVector *aVector)
{
	if(aVector == NULL)
		return 0;
	assert(aVector);
	return aVector->iSize;
}

bool vector_resize(struct TVector *aVector, size_t aNewSize)
{
	if(aVector == NULL)
		return 0;
	assert(vector_invariant(aVector));
	if(aVector->iSize == aNewSize)
		return 1;
	TVectorElement *new_values = NULL;
	if(aNewSize)
	{
		if(aVector->iSize > aNewSize)
			new_values = malloc(aNewSize * sizeof(TVectorElement));
		else
			new_values = calloc(aNewSize, sizeof(TVectorElement));
	}
	if(new_values == NULL)
		return 0;
	size_t copy_size = 0;
	if(aVector->iSize > aNewSize)
		copy_size = aNewSize;
	else
		copy_size = aVector->iSize;
	for(size_t i = 0; i < copy_size; i++)
		new_values[i] = aVector->iValues[i];
	free(aVector->iValues);
	aVector->iValues = new_values;
	aVector->iSize = aNewSize;
	assert(vector_invariant(aVector));
	return 1;
}

void vector_destroy(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	assert(vector_invariant(aVector));
	free(aVector->iValues);
	aVector->iValues = NULL;
	aVector->iSize = 0;
	assert(vector_invariant(aVector));
}

struct TVectorIterator vector_iterator_begin(const struct TVector *aVector)
{
	if(aVector == NULL || aVector->iSize == 0)
		return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	return (struct TVectorIterator) { .iVector = (struct TVector *)aVector, .iPos = 0 };
}

struct TVectorIterator vector_iterator_pos(const struct TVector *aVector, size_t aPos)
{
	if(aVector == NULL || aPos >= aVector->iSize)
		return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	return (struct TVectorIterator) { .iVector = (struct TVector *)aVector, .iPos = aPos };
}

struct TVectorIterator vector_iterator_last(const struct TVector *aVector)
{
	if(aVector == NULL || aVector->iSize == 0)
		return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	return (struct TVectorIterator) { .iVector = (struct TVector *)aVector, .iPos = aVector->iSize - 1 };
}

bool vector_iterator_is_valid(const struct TVectorIterator *aIter)
{
	if(aIter != NULL)
		if(aIter->iVector != NULL)
			if((aIter->iVector->iSize - 1) < aIter->iPos)
				return true;
	return false;
}

bool vector_iterator_to_next(struct TVectorIterator *aIter)
{
	if(vector_iterator_is_valid(aIter) == false)
		return false;

	++aIter->iPos;
	if(aIter->iPos >= aIter->iVector->iSize)
	{
		*aIter = (struct TVectorIterator){ .iVector = NULL, .iPos = 0 };
		return false;
	}
	return true;
}

bool vector_iterator_to_prev(struct TVectorIterator *aIter)
{
	if(vector_iterator_is_valid(aIter) == false)
		return false;

	if(aIter->iPos <= 0)
	{
		*aIter = (struct TVectorIterator){ .iVector = NULL, .iPos = 0 };
		return false;
	}
	--aIter->iPos;
	return true;
}

TVectorElement vector_iterator_value(const struct TVectorIterator *aIter)
{
	if(vector_iterator_is_valid(aIter) == false)
		return (TVectorElement) { 0 };
	return (TVectorElement) { aIter->iVector->iValues[aIter->iPos] };
}

bool vector_iterator_set_value(const struct TVectorIterator *aIter, TVectorElement aValue)
{
	if(vector_iterator_is_valid(aIter) == false)
		return false;
	aIter->iVector->iValues[aIter->iPos] = aValue;
	return true;
}
