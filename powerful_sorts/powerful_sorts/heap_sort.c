/** \file heap_sort.c
 *  \brief Implementace API vıkonnìjší metody tøídìní (Heap sort), vyuívající pozièní API pro pøístup k uzlùm haldy
 *  \author Petyovskı
 *  \version 2026
 *  $Id: heap_sort.c 3342 2026-04-13 14:19:07Z petyovsky $
 */

#include "heap_sort.h"
#include "THeap.h"

 /** \brief Vnitøní a lokální funkce zajišující algoritmus vloení hodnoty do zvoleného uzlu haldy, pøi zachování podmínek haldy
  *  \details Lokální funkce implementuje algoritmus vloení hodnoty do zvoleného uzlu haldy, pøi zachování podmínek haldy (prosívání hodnoty smìrem k listùm).
  *  \param[in,out] aHeap Ukazatel na vytváøenou haldu
  *  \param[in] aParentPos Index uzlu urèeného pro vloení hodnoty \p aValue (hodnota v tomto uzlu bude pøepsána).
  *  \param[in] aValue Hodnota vkládáná do haldy
  */
static inline void heap_alg_sift_down(struct THeap *aHeap, size_t aParentPos, THeapElement aValue)
{
	size_t pos = aParentPos;
	size_t heapsize = heap_size(aHeap);
	size_t left_pos = heap_pos_to_left(pos);

	while(left_pos < heapsize)
	{
		size_t right_pos = heap_pos_to_right(pos);

		// Najdi vìtší dítì
		size_t larger_child = left_pos;
		if(right_pos < heapsize && heap_compare_positions(aHeap, right_pos, aHeap, left_pos) > 0)
			larger_child = right_pos;

		// Porovnaj vìtší dítì s hodnotou
		if(heap_compare_position_value(aHeap, larger_child, aValue) > 0)
		{
			heap_move_positions(aHeap, pos, aHeap, larger_child);
			pos = larger_child;
			left_pos = heap_pos_to_left(pos);
		}
		else
			break;
	}

	// Vloení hodnoty na finální pozici
	heap_set_value(aHeap, pos, aValue);
}

/** \brief Vnitøní a lokální funkce realizující algoritmus uspoøádání elementù vektoru do haldy
 *  \details Lokální funkce implementuje algoritmus uspoøádání elementù vektoru do haldy, pomocí volání funkce `heap_alg_sift_down()`.
 *  \param[in,out] aHeap Ukazatel na vytváøenou haldu
 */
static inline void heap_alg_heapify(struct THeap *aHeap)
{
	size_t heapsize = heap_size(aHeap);

	if(heapsize < 2)
		return;

	// Zaèíná od poslední rodièovské pozice a prosívá všechny prvky dolù
	for(size_t i = (heapsize - 2) / 2;; --i)
	{
		const THeapElement value = heap_value(aHeap, i);
		heap_alg_sift_down(aHeap, i, value);

		if(i == 0)
			break;
	}
}

void heap_sort(struct TVector *aVector)
{
	//	for(size_t i = 0; i < vector_size(aVector); ++i)
	//		vector_element_store_file(aVector->iValues[i], stdout);
	//	putchar('\n');

	if(vector_size(aVector) < 2)
		return;

	//auto heap = heap_create(*aVector);		// auto since C23
	struct THeap heap = heap_create(*aVector);

	//	for(size_t i = 0; i < heap_size(&heap); ++i)
	//		vector_element_store_file(heap.iVector.iValues[i], stdout);
	//	putchar('\n');

	heap_alg_heapify(&heap);

	//	for(size_t i = 0; i < heap_size(&heap); ++i)
	//		vector_element_store_file(heap.iVector.iValues[i], stdout);
	//	putchar('\n');

	//	puts("Heapify stats:");
	//	vector_print_sortstats(aVector);

	const size_t root_pos = 0;
	size_t heapsize = heap_size(&heap);

	while(heapsize > 1)
	{
		const size_t last_pos = heapsize - 1;

		//		heap_dump(&heap, stdout);

		const THeapElement value = heap_value(&heap, last_pos);
		heap_move_positions(&heap, last_pos, &heap, root_pos);

		heapsize = heap_decrement_size(&heap);

		//		fprintf(stdout, "Value: %" TVECTOR_ELEMENT_FRMSTR "\n", value);
		//		heap_dump(&heap, stdout);

		heap_alg_sift_down(&heap, root_pos, value);

		//		for(size_t i = 0; i < heapsize; ++i)
		//			vector_element_store_file(heap.iVector.iValues[i], stdout);
		//		puts("\n-------");
	}
}
