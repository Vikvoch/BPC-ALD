/** \file main_tg_vector.c
 *  \brief Hlavní program testující Basic Vector API
 *  \author Petyovský
 *  \version 2026
 *  $Id: main_tg_vector.c 3229 2026-03-02 16:14:51Z petyovsky $
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TVector.h"
#include "main_support.h"
#include "tgadt.h"
#include "check.h"

/** \defgroup MainProgram 3. Hlavní program
 *  \brief Definice funkcí hlavního programu
 *  \{
 */

/** \brief Vytisknutí elementu vektoru pomocí iterátoru
 *  \details Tisk hodnoty elementu vektoru, na který ukazuje iterátor.
 *  \param[in] aIter Ukazatel na existující iterátor
 */
static void print_element(const struct TVectorIterator *aIter)
	{
	printf(TVECTOR_ELEMENT_FRMSTR " ", value(aIter));
	//vector_element_store_file(value(aIter), stdout);
	}

/** \brief Testování funkce pro vector `resize()`
 *  \details Testovací funkce pro vector `resize()`, funkce změří výpočetní čas a velikost paměti, kterou funkce potřebovala k dokončení změny velikosti vektoru.
 *  \param[in] aOrigVector Ukazatel na vstupní vektor
 *  \param[in] aNewSize Nově požadovaná velikost vektoru
 */
void resize_testing(const struct TVector *aOrigVector, size_t aNewSize)
	{
	struct TVector vector = { 0 };
	UNLESS(clone(aOrigVector, &vector), goto cleanup_resize_testing);

	//for(size_t i = 0; i < size(&vector); ++i)
	//	printf(TVECTOR_ELEMENT_FRMSTR " ", value(&vector, i));
	//putchar('\n');

	printf("\n------ Resize to %zu ------\n", aNewSize);
	//for_each(begin(&vector), print_element);
	//putchar('\n');

	struct timespec start_timespec = { 0, }, end_timespec = { 0, };
	UNLESS(timespec_get(&start_timespec, TIME_UTC));

	UNLESS(resize(&vector, aNewSize), goto cleanup_resize_testing);

	UNLESS(timespec_get(&end_timespec, TIME_UTC));

	//for_each_n(begin(&vector), 20, print_element);
	//putchar('\n');

	printf("\nResizing time: %lf seconds.\n", difftimespec(end_timespec, start_timespec));
	printf("Allocation size max peak: %zu.\n", get_alloc_max_peak_size());

cleanup_resize_testing:
	destroy(&vector);
	}

#define VECTOR_INIT_FROM_FILE	"reversed_data.txt"

int main_tg_vector(int argc, char *argv[])
	{
	srand((unsigned int)time(NULL));

	struct TVector vector1 = { 0 };

#ifdef VECTOR_INIT_FROM_FILE
	FILE *fsrc = fopen(VECTOR_INIT_FROM_FILE, "r");
	//if(!fsrc)
	//	return 1;
	UNLESS(fsrc, return 1);

	bool initialized = init_file(&vector1, fsrc);
	fclose(fsrc);
#else
	bool initialized = init_random(&vector1, 50000);
#endif

	//if(!initialized)
	//	return 2;
	UNLESS(initialized, return 2);

#ifdef VECTOR_INIT_FROM_FILE
	printf("Vector of %zu elements from file '" VECTOR_INIT_FROM_FILE "':\n", size(&vector1));
#else
	printf("Vector of %zu random elements:\n", size(&vector1));
#endif

	//printf("vector1 is empty: %s\n", is_empty(&vector1) ? "true" : "false");
	printf("vector1 is empty: %s\n", bool_to_cstring(is_empty(&vector1)) );

	#ifndef NDEBUG
		const struct TVector vector = vector1;
		// Debug configuration (vector API value access)
		for(size_t i = 0; i < size(&vector1); ++i)
			printf(TVECTOR_ELEMENT_FRMSTR " ", value(&vector, i));
	#else
		// Release configuration (direct value access)
		if(vector1.iValues)
			{
			for(size_t i = 0; i < vector1.iSize; ++i)
				printf(TVECTOR_ELEMENT_FRMSTR " ", vector1.iValues[i]);
			}
	#endif /* NDEBUG */
	putchar('\n');

	//for_each(begin(&vector1), print_element);
	//putchar('\n');

	resize_testing(&vector1, 5);

	//for_each(begin(&vector1), print_element);
	//putchar('\n');

	resize_testing(&vector1, 1000000);		// 4Mb
	resize_testing(&vector1, 10000000);		// 40Mb
	resize_testing(&vector1, 100000000);	// 400Mb
	resize_testing(&vector1, 1000000000);	// 4000Mb

	//for_each_n(begin(&vector1), 20, print_element);
	//putchar('\n');

	destroy(&vector1);
	return 0;
	}

/** \} MainProgram */
