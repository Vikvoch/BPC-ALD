/** \file TSetHashTableOpenAddr.c
 *  \brief Implementace API pro typ SetHashTable - (hašovací tabulka využívající otevøené adresování)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TSetHashTableOpenAddr.c 3361 2026-04-20 14:36:03Z petyovsky $
 */

#define LINEAR_PROBING		1	///< Volba pro lineární dohledávání následující pozice ve funkci: `set_hash_table_search()`
#define QUADRATIC_PROBING	2	///< Volba pro kvadratické dohledávání následující pozice ve funkci: `set_hash_table_search()`

#define HASH_TABLE_SEARCH_VARIANT	LINEAR_PROBING		///< Varianta využívající lineární dohledávání následující pozice ve funkci: `set_hash_table_search()`
 //#define HASH_TABLE_SEARCH_VARIANT	QUADRATIC_PROBING	///< Varianta využívající kvadratické dohledávání následující pozice ve funkci: `set_hash_table_search()`

#include <stdlib.h>
#include <assert.h>
#include "TSetHashTableOpenAddr.h"
#include "check.h"

/** \brief Úplná definice typu SetHashTable
 *  \details Typ SetHashTable realizuje hash tabulku s elementy typu ukazatel na SetElementHashable a umožòuje s nimi pracovat pomocí definovaného API.
 */
struct TSetHashTable {
	size_t iCapacity;			///< Naalokovaná kapacita vnitøního pole pøihrádek
	TSetElement *iBucket[];		///< Pole pøihrádek realizující hašovací tabulku (každá pøihrádka je ukazatel na typ SetElement Hashable)
};

/** \brief Funkce vracející hodnotu reprezentující smazanou pøihrádku
 *  \details Servisní funkce pro výpoèet hodnoty reprezentující znaèku pro døíve obsazenou, ale nyní již smazanou pøihrádku.
 *  \param[in] aTable Ukazatel na existující hašovací tabulku
 *  \return Vrací hodnotu reprezentující znaèku pro smazanou pøihrádku
 *  \attention Funkce ovìøuje platnost ukazatele \b pouze pøi pøekladu v režimu `Debug`, kdy pomocí `assert` hlásí bìhovou chybu!
 */
static inline TSetElement *calc_erased_bucket_marker(const struct TSetHashTable *aTable)
{
	assert(aTable);
	assert(aTable->iBucket);
	return (TSetElement *)&aTable->iBucket[0];
}

bool set_hash_table_init(struct TSetHashTable **aTablePtr, size_t aCapacity)
{
	if(!aTablePtr || !aCapacity)
		return false;

	struct TSetHashTable *new_table =
		calloc(1, offsetof(struct TSetHashTable, iBucket) + aCapacity * sizeof(TSetElement *));

	if(!new_table)
		return false;

	new_table->iCapacity = aCapacity;
	*aTablePtr = new_table;
	return true;
}

int set_hash_table_search(const struct TSetHashTable *aTable, TSetElement aValue, size_t *aPosPtr)
{
	if(!aTable)
		return -2;

	if(!aPosPtr)
		return -1;

	assert(aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	size_t hash_pos = set_element_hash_value(&aValue) % aTable->iCapacity;
	size_t first_erased_pos = aTable->iCapacity;	// Initialize to invalid position
	size_t i = 0;	// Probing counter

#if HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING

	while(i < aTable->iCapacity)
	{
		size_t current_pos = (hash_pos + i) % aTable->iCapacity;
		
		// Check if bucket is empty (never used)
		if(!aTable->iBucket[current_pos])
		{
			*aPosPtr = (first_erased_pos < aTable->iCapacity) ? first_erased_pos : current_pos;
			return 1;	// Element not found, but position available
		}
		
		// Check if bucket is marked as erased
		if(aTable->iBucket[current_pos] == Marked_as_erased)
		{
			if(first_erased_pos >= aTable->iCapacity)
				first_erased_pos = current_pos;
			++i;
			continue;
		}
		
		// Bucket contains an element, check if it's the one we're looking for
		if(set_element_comparator(aTable->iBucket[current_pos], &aValue) == 0)
		{
			*aPosPtr = current_pos;
			return 0;	// Element found
		}
		
		++i;
	}

#elif HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING

	while(i < aTable->iCapacity)
	{
		size_t current_pos = (hash_pos + i * i) % aTable->iCapacity;
		
		// Check if bucket is empty (never used)
		if(!aTable->iBucket[current_pos])
		{
			*aPosPtr = (first_erased_pos < aTable->iCapacity) ? first_erased_pos : current_pos;
			return 1;	// Element not found, but position available
		}
		
		// Check if bucket is marked as erased
		if(aTable->iBucket[current_pos] == Marked_as_erased)
		{
			if(first_erased_pos >= aTable->iCapacity)
				first_erased_pos = current_pos;
			++i;
			continue;
		}
		
		// Bucket contains an element, check if it's the one we're looking for
		if(set_element_comparator(aTable->iBucket[current_pos], &aValue) == 0)
		{
			*aPosPtr = current_pos;
			return 0;	// Element found
		}
		
		++i;
	}

#else
#error Missing correct HASH_TABLE_SEARCH_VARIANT symbol definition
#endif

	// Hash table is full and element was not found
	*aPosPtr = (first_erased_pos < aTable->iCapacity) ? first_erased_pos : (hash_pos + (aTable->iCapacity - 1)) % aTable->iCapacity;
	return 2;		// Element was not found and hash table is completely full
}

bool set_hash_table_insert(struct TSetHashTable *aTable, TSetElement aValue)
{
	if(!aTable)
		return false;

	size_t pos = 0;
	int search_result = set_hash_table_search(aTable, aValue, &pos);

	// If element already exists, return false (no duplicate insertion)
	if(search_result == 0)
		return false;

	// If hash table is full and element was not found, return false
	if(search_result == 2)
		return false;

	// Element not found and position is available, insert it
	TSetElement *new_element = malloc(sizeof(TSetElement));
	if(!new_element)
		return false;

	*new_element = aValue;
	aTable->iBucket[pos] = new_element;

	return true;
}

bool set_hash_table_erase(struct TSetHashTable *aTable, TSetElement aValue)
{
	if(!aTable)
		return false;

	size_t pos = 0;
	int search_result = set_hash_table_search(aTable, aValue, &pos);

	// If element was found, erase it
	if(search_result == 0)
	{
		TSetElement *Marked_as_erased = calc_erased_bucket_marker(aTable);
		free(aTable->iBucket[pos]);
		aTable->iBucket[pos] = Marked_as_erased;
		return true;
	}

	return false;	// Element was not found
}

void set_hash_table_destroy(struct TSetHashTable *aTable)
{
	if(!aTable)
		return;

	assert(aTable->iCapacity);
	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	for(size_t i = 0; i < aTable->iCapacity; ++i)
	{
		if(aTable->iBucket[i] != Marked_as_erased)
			free(aTable->iBucket[i]);

		aTable->iBucket[i] = NULL;
	}

	free(aTable);
}

size_t set_hash_table_begin_pos(const struct TSetHashTable *aTable)
{
	assert(aTable);
	assert(aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	size_t pos = 0;
	for(; pos < aTable->iCapacity; ++pos)
		if((aTable->iBucket[pos]) && (aTable->iBucket[pos] != Marked_as_erased))
			break;

	return pos;
}

bool set_hash_table_is_valid_pos(const struct TSetHashTable *aTable, size_t aPos)
{
	if(aTable)
	{
		assert(aTable->iCapacity);
		TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
		return (aPos < aTable->iCapacity) && (aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased);
	}

	return false;
}

size_t set_hash_table_next_pos(const struct TSetHashTable *aTable, size_t aPos)
{
	assert(aTable);
	assert(aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	for(++aPos; aPos < aTable->iCapacity; ++aPos)
		if((aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased))
			break;

	return aPos;
}

TSetElement set_hash_table_value_at_pos(const struct TSetHashTable *aTable, size_t aPos)
{
	assert(aTable);
	assert(aTable->iCapacity);
	assert(aPos < aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	assert((aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased));

	return *aTable->iBucket[aPos];
}
