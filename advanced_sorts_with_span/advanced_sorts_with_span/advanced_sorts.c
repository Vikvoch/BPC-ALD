/** \file advanced_sorts.c
 *  \brief Implementace API úèinnìjších metod tøídìní
 *  \author Petyovský
 *  \version 2026
 *  $Id: advanced_sorts.c 3317 2026-04-02 17:27:02Z petyovsky $
 */

#include "advanced_sorts.h"

 /** \brief Formátovaný tisk hodnoty elementu za pøedpokladu platné hodnoty predikátu
  *  \details Vytiskne formátovanì hodnotu elementu pokud je parametr \p aCondition platný, jinak se vytisknou zástupné znaky.
  *  \param[in] aCondition pokud je \c true bude hodnota vytisknuta, jinak se vytisknou zástupné znaky
  *  \param[in] aValue Hodnota elementu k vytisknutí
  */
[[maybe_unused]] static void vector_element_print_if(bool aCondition, TVectorElement aValue)
{
	if(!aCondition)
		fputs(". ", stdout);
	else
		if(!vector_element_store_file(aValue, stdout))
			fputs("Function 'vector_element_store_file()' failed!\n", stderr);
}

void shell_sort(struct TVector *aVector)
{
	size_t elementCnt = aVector->iSize;
	size_t gapSize = elementCnt / 2;
	while(gapSize > 0)
	{
		//printf("gapSize: %zu\n", gapSize);

		for(size_t i = gapSize; i < elementCnt; ++i)
		{
			/*for(size_t x = 0; x < aVector->iSize; ++x)
				vector_element_store_file(aVector->iValues[x], stdout);
			putchar('\n');*/

			TVectorElement temp = aVector->iValues[i];
			size_t j = i;
			while(j >= gapSize && vector_compare_position_value(aVector, j - gapSize, temp) > 0)
			{
				vector_swap_positions(aVector, j, aVector, j - gapSize);
				j -= gapSize;
			}
			aVector->iValues[j] = temp;

			/*for(size_t x = 0; x < aVector->iSize; ++x)
				vector_element_print_if((x % gapSize == i % gapSize) && (x <= i), aVector->iValues[x]);
			putchar('\n');*/
		}

		//putchar('\n');
		gapSize /= 2;
	}

	/*for(size_t gap = elementCnt / 2; gap > 0; gap /= 2)
	{
		for(int i = gap; i < elementCnt; i++)
		{
			TVectorElement temp = aVector->iValues[i];
			size_t j = i;

			while(j >= gap && vector_compare_position_value(aVector, j - gap, temp) > 0)
			{
				vector_swap_positions(aVector, j, aVector, j - gap);
				j -= gap;
			}
			aVector->iValues[j] = temp;
		}
	}*/
}

/** \brief Vnitøní a lokální funkce realizující rekurzivní pracovní funkci pro metodu (Quick Sort)
 *  \details Realizuje rekurzivní pracovní funkci pro tøídicí metodu (Quick Sort) pro elementy vektoru v rozsahu pozic `<k,l>`.
 *  \param[in,out] aVector Ukazatel na tøídìný vektor hodnot
 *  \param[in] k Index levého elementu z rozsahu `<k,l>`
 *  \param[in] l Index pravého elementu z rozsahu `<k,l>`
 */
static void quick_sort_worker(struct TVector * /*restrict*/ aVector, size_t k, size_t l)
{
	/*for(size_t x = 0; x < aVector->iSize; ++x)
		vector_element_print_if((x >= k) && (x <= l), aVector->iValues[x]);
	putchar('\n');*/

	if(k > l)
		return;

	TVectorElement pivot = aVector->iValues[(k + l) / 2];
	size_t i = k;
	size_t j = l;

	while(i <= j)
	{
		while(vector_compare_position_value(aVector, i, pivot) < 0)
		{
			if(i < vector_size(aVector))
				++i;
			else
				break;
		}
		while(vector_compare_position_value(aVector, j, pivot) > 0)
		{
			if(j > 0)
				--j;
			else
				break;
		}
		if(i <= j)
		{
			vector_swap_positions(aVector, i, aVector, j);
			++i;
			if(j > 0)
				--j;
		}
	}

	if(k < j)
		quick_sort_worker(aVector, k, j);
	if(i < l)
		quick_sort_worker(aVector, i, l);
}

void quick_sort(struct TVector *aVector)
{
	if(vector_size(aVector) < 1)
		return;

	quick_sort_worker(aVector, 0, aVector->iSize - 1);
}
