/** \file basic_sorts.c
 *  \brief Implementace API pøímých metod tøídìní
 *  \author Petyovský
 *  \version 2026
 *  $Id: basic_sorts.c 3260 2026-03-16 16:21:51Z petyovsky $
 */

#include "basic_sorts.h"

void print_element(const struct TVectorIterator *aIter)
{
	if(!vector_element_store_file(vector_iterator_value(aIter), stdout))
		fputs("Function 'vector_element_store_file()' failed!\n", stderr);
}

void insert_sort(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	for(size_t i = 1; i < aVector->iSize; ++i)
	{
		TVectorElement tmp = vector_value(aVector, i);
		size_t j = i;
		for(; j > 0; --j)
		{
			if(vector_compare_position_value(aVector, j - 1, tmp) <= 0)
				break;
			vector_move_positions(aVector, j, aVector, j - 1);
		}
		vector_set_value(aVector, j, tmp);
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}

void select_sort(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	for(size_t i = 0; i < aVector->iSize - 1; i++)
	{
		size_t minPos = i;
		for(size_t j = i + 1; j < aVector->iSize; j++)
			if(vector_compare_positions(aVector, j, aVector, minPos) <= 0)
				minPos = j;
		vector_swap_positions(aVector, i, aVector, minPos);
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}

void bubble_sort(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	for(size_t i = 0; i < aVector->iSize - 1; i++)
	{
		for(size_t j = 0; j < aVector->iSize - i - 1; j++)
		{
			if(vector_compare_positions(aVector, j, aVector, j + 1) >= 1)
				vector_swap_positions(aVector, j, aVector, j + 1);
		}
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}

void bubble_sort_optimized(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	for(size_t i = 0; i < aVector->iSize - 1; i++)
	{
		bool isSorted = true;
		for(size_t j = 0; j < aVector->iSize - i - 1; j++)
		{
			if(vector_compare_positions(aVector, j, aVector, j + 1) >= 1)
			{
				vector_swap_positions(aVector, j, aVector, j + 1);
				isSorted = false;
			}
		}
		if(isSorted)
			return;
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}

void bubble_sort_optimized2(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	size_t endpos = aVector->iSize - 1;
	while(endpos > 0)
	{
		size_t swapPos = 0;
		for(size_t j = 0; j < endpos; j++)
		{
			if(vector_compare_positions(aVector, j, aVector, j + 1) >= 1)
			{
				vector_swap_positions(aVector, j, aVector, j + 1);
				swapPos = j;
			}
		}
		endpos = swapPos;
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}

void shaker_sort(struct TVector *aVector)
{
	if(aVector == NULL)
		return;
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
	size_t begin = 0;
	size_t end = aVector->iSize - 1;
	size_t lastSwap = 0;
	while(begin < end)
	{
		for(size_t i = begin; i < end; i++)
		{
			if(vector_compare_positions(aVector, i, aVector, i + 1) > 0)
			{
				vector_swap_positions(aVector, i, aVector, i + 1);
				lastSwap = i;
			}
		}
		end = lastSwap;
		for(size_t i = end; i > begin; i--)
		{
			if(vector_compare_positions(aVector, i - 1, aVector, i) > 0)
			{
				vector_swap_positions(aVector, i, aVector, i - 1);
				lastSwap = i;
			}
		}
		begin = lastSwap;
	}
	/*vector_for_each_n(vector_iterator_begin(aVector), 20, print_element);
	putchar('\n');*/
}
