/** \file TSetSortedFlexArray.c
 *  \brief Implementace API pro typ SetSortedFlexArray (Flexibilní, tzv. otevøené, pole pro realizaci množiny pomocí setøídìného dynamicky alokovaného pole)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TSetSortedFlexArray.c 3361 2026-04-20 14:36:03Z petyovsky $
 */

#define LINEAR_SEARCH_OPTIMIZED	1	///< Volba pro vyhledávání s optimalizací døívìjšího ukonèení
#define BINARY_SEARCH			2	///< Volba pro binární vyhledávání

#define FLEX_ARRAY_SEARCH_VARIANT	LINEAR_SEARCH_OPTIMIZED	///< Varianta využívající lineární vyhledávání s optimalizací ve funkci: `set_flex_array_search()`
 //#define FLEX_ARRAY_SEARCH_VARIANT	BINARY_SEARCH			///< Varianta využívající binární vyhledávání ve funkci: `set_flex_array_search()`

#include <stdlib.h>
#include <assert.h>
#include "TSetSortedFlexArray.h"
#include "check.h"

/** \brief Úplná definice privátního typu SetSortedFlexArray
 *  \details Privátní typ SetSortedFlexArray (nedostupný mimo funkce z tohoto zdrojového souboru) reprezentuje typ pro tzv. flexibilní (otevøené) pole hodnot typu SetElement.
 */
struct TSetSortedFlexArray {
	size_t iCapacity;			///< Skuteènì naalokovaná kapacita prvkù vnitøního dynamického pole
	TSetElement iElement[];		///< Flexibilní (otevøené) pole hodnot typu SetElement (nedostupné mimo funkce ze souboru TSetSortedFlexArray.c)
};

int set_flex_array_search(const struct TSetSortedFlexArray *aFlexArray, TSetElement aValue, size_t *aPosPtr, size_t aSize)
{
	assert(aPosPtr);

	if(!aSize)
	{
		*aPosPtr = 0;
		return -2;
	}

	assert(aFlexArray);
	assert(aFlexArray->iCapacity >= aSize);

#if FLEX_ARRAY_SEARCH_VARIANT == LINEAR_SEARCH_OPTIMIZED

	/* Lineární vyhledávání s optimalizací døívìjšího ukonèení */
	for(size_t i = 0; i < aSize; ++i)
	{
		int cmp_result = set_element_comparator(&aValue, &aFlexArray->iElement[i]);
		
		if(cmp_result == 0)
		{
			*aPosPtr = i;
			return 0;
		}
		else if(cmp_result == -1)
		{
			*aPosPtr = i;
			return -1;
		}
	}
	
	/* Element not found, and is greater than all elements */
	*aPosPtr = aSize - 1;
	return 1;

#elif FLEX_ARRAY_SEARCH_VARIANT == BINARY_SEARCH

	/* Binární vyhledávání */
	size_t left = 0;
	size_t right = aSize - 1;
	size_t last_pos = 0;

	while(left <= right)
	{
		size_t mid = left + (right - left) / 2;
		int cmp_result = set_element_comparator(&aValue, &aFlexArray->iElement[mid]);
		
		if(cmp_result == 0)
		{
			*aPosPtr = mid;
			return 0;
		}
		else if(cmp_result == -1)
		{
			last_pos = mid;
			if(mid == 0)
				break;
			right = mid - 1;
		}
		else
		{
			last_pos = mid;
			left = mid + 1;
		}
	}
	
	*aPosPtr = last_pos;
	
	int cmp_result = set_element_comparator(&aValue, &aFlexArray->iElement[last_pos]);
	if(cmp_result == -1)
		return -1;
	else
		return 1;

#else
#error Missing correct FLEX_ARRAY_SEARCH_VARIANT symbol definition
#endif
}

bool set_flex_array_insert(struct TSetSortedFlexArray **aFlexArrayPtr, TSetElement aValue, size_t aSize)
{
	assert(aFlexArrayPtr);
	struct TSetSortedFlexArray *act_array = *aFlexArrayPtr;

	size_t insert_pos = 0;
	
	if(aSize == 0)
	{
		/* První vložení do prázdného pole */
		struct TSetSortedFlexArray *new_array = (struct TSetSortedFlexArray *)malloc(sizeof(struct TSetSortedFlexArray) + sizeof(TSetElement) * 1);
		if(!new_array)
			return false;
		
		new_array->iCapacity = 1;
		new_array->iElement[0] = aValue;
		*aFlexArrayPtr = new_array;
		return true;
	}
	
	/* Vyhledat pozici prvku */
	int search_result = set_flex_array_search(act_array, aValue, &insert_pos, aSize);
	
	if(search_result == 0)
	{
		/* Prvek již existuje */
		return false;
	}
	
	/* Prvek neexistuje, urèit pozici pro vložení */
	if(search_result == -1)
	{
		/* Prvek je menší než prvek na pozici insert_pos */
		/* insert_pos je již na správné pozici */
	}
	else if(search_result == 1)
	{
		/* Prvek je vìtší než všechny prvky */
		insert_pos = aSize;
	}
	
	/* Zkontrolovat kapacitu */
	if(aSize >= act_array->iCapacity)
	{
		/* Potøebujeme více místa - alokovat dvojnásobnou kapacitu */
		size_t new_capacity = act_array->iCapacity * 2;
		struct TSetSortedFlexArray *new_array = (struct TSetSortedFlexArray *)malloc(sizeof(struct TSetSortedFlexArray) + sizeof(TSetElement) * new_capacity);
		if(!new_array)
			return false;
		
		new_array->iCapacity = new_capacity;
		
		/* Kopírovat prvky a vložit nový prvek */
		for(size_t i = 0; i < insert_pos; ++i)
		{
			new_array->iElement[i] = act_array->iElement[i];
		}
		
		new_array->iElement[insert_pos] = aValue;
		
		for(size_t i = insert_pos; i < aSize; ++i)
		{
			new_array->iElement[i + 1] = act_array->iElement[i];
		}
		
		free(act_array);
		*aFlexArrayPtr = new_array;
	}
	else
	{
		/* Máme místo, posunout prvky a vložit */
		for(size_t i = aSize; i > insert_pos; --i)
		{
			act_array->iElement[i] = act_array->iElement[i - 1];
		}
		
		act_array->iElement[insert_pos] = aValue;
	}
	
	return true;
}

bool set_flex_array_erase(struct TSetSortedFlexArray **aFlexArrayPtr, TSetElement aValue, size_t aSize)
{
	assert(aFlexArrayPtr);
	assert(aSize);

	struct TSetSortedFlexArray *act_array = *aFlexArrayPtr;

	size_t erase_pos = 0;
	
	/* Vyhledat pozici prvku */
	int search_result = set_flex_array_search(act_array, aValue, &erase_pos, aSize);
	
	if(search_result != 0)
	{
		/* Prvek není v poli */
		return false;
	}
	
	/* Prvek existuje - odebrat ho */
	if(aSize == 1)
	{
		/* Poslední prvek - dealokovat pole */
		free(act_array);
		*aFlexArrayPtr = NULL;
		return true;
	}
	
	/* Zkontrolovat, zda je potøeba zmenšit pole */
	/* Zmenšit, pokud je nová velikost <= 25% kapacity (tj. když zaplnìní bude <= 50%) */
	size_t new_size = aSize - 1;
	
	if(new_size > 0 && new_size <= (act_array->iCapacity / 4))
	{
		/* Zmenšit pole na polovinu kapacity */
		size_t new_capacity = act_array->iCapacity / 2;
		struct TSetSortedFlexArray *new_array = (struct TSetSortedFlexArray *)malloc(sizeof(struct TSetSortedFlexArray) + sizeof(TSetElement) * new_capacity);
		if(!new_array)
			return false;
		
		new_array->iCapacity = new_capacity;
		
		/* Kopírovat prvky a vynechat prvek na pozici erase_pos */
		for(size_t i = 0; i < erase_pos; ++i)
		{
			new_array->iElement[i] = act_array->iElement[i];
		}
		
		for(size_t i = erase_pos + 1; i < aSize; ++i)
		{
			new_array->iElement[i - 1] = act_array->iElement[i];
		}
		
		free(act_array);
		*aFlexArrayPtr = new_array;
	}
	else
	{
		/* Pole zùstane stejné, jen posunout prvky */
		for(size_t i = erase_pos + 1; i < aSize; ++i)
		{
			act_array->iElement[i - 1] = act_array->iElement[i];
		}
	}
	
	return true;
}

void set_flex_array_destroy(struct TSetSortedFlexArray *aFlexArray)
{
	free(aFlexArray);
}

size_t set_flex_array_begin_pos(const struct TSetSortedFlexArray *aFlexArray)
{
	return 0;
}

bool set_flex_array_is_valid_pos(const struct TSetSortedFlexArray *aFlexArray, size_t aPos, size_t aSize)
{
	if(aFlexArray)
		return (aSize <= aFlexArray->iCapacity) && (aPos < aSize);

	return false;
}

size_t set_flex_array_next_pos(const struct TSetSortedFlexArray *aFlexArray, size_t aPos)
{
	return ++aPos;
}

TSetElement set_flex_array_value_at_pos(const struct TSetSortedFlexArray *aFlexArray, size_t aPos)
{
	assert(aFlexArray);
	assert(aPos < aFlexArray->iCapacity);

	return aFlexArray->iElement[aPos];
}
