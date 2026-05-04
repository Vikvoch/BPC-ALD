/** \file heap_sort_with_iterators.c
 *  \brief Implementace API výkonnìjší metody tøídìní (Heap sort), využívající iterátorové API pro pøístup k uzlùm haldy
 *  \author Petyovský
 *  \version 2026
 *  $Id: heap_sort_with_iterators.c 3342 2026-04-13 14:19:07Z petyovsky $
 */

#include "heap_sort_with_iterators.h"
#include "THeap.h"

 /** \brief Vnitøní a lokální funkce realizující algoritmus vložení hodnoty do zvoleného uzlu haldy, pøi zachování podmínek haldy
   *  \details Lokální funkce implementuje algoritmus vložení hodnoty do zvoleného uzlu haldy, pøi zachování podmínek haldy (prosívání hodnoty smìrem k listùm).
   *  \param[in] aParent Iterátor na uzel haldy urèený pro vložení hodnoty \p aValue (hodnota v tomto uzlu bude pøepsána)
   *  \param[in] aValue Hodnota vkládáná do haldy
   */
 static inline void heap_iterator_alg_sift_down(struct THeapIterator aParent, THeapElement aValue)
 {
struct THeapIterator parent = aParent;

	while(true)
	{
		struct THeapIterator left = parent;
		if(!heap_iterator_to_left(&left))
			break;

		// Najdi vìtší dítì (mezi levým a pravým)
		struct THeapIterator larger_child = left;
		struct THeapIterator right = parent;
		bool has_right = heap_iterator_to_right(&right);
		if(has_right && heap_compare_with_iterators(&right, &larger_child) > 0)
			larger_child = right;

		// Porovnaj vìtší dítì s hodnotou
		if(heap_compare_with_iterator_value(&larger_child, aValue) > 0)
		{
			heap_move_with_iterators(&parent, &larger_child);
			parent = larger_child;
		}
		else
			break;
	}

// Vložení hodnoty na finální pozici
heap_iterator_set_value(&parent, aValue);
 }

 /** \brief Vnitøní a lokální funkce realizující algoritmus uspoøádání elementù vektoru do haldy
  *  \details Lokální funkce implementuje algoritmus uspoøádání elementù vektoru do haldy, pomocí volání funkce `sift_down()`.
  *  \param[in,out] aHeap Ukazatel na vytváøenou haldu
  */
 static inline void heap_iterator_alg_heapify(struct THeap *aHeap)
 {
size_t heapsize = heap_size(aHeap);

if(heapsize < 2)
return;

// Zaèíná od poslední rodièovské pozice a prosívá všechny prvky dolù
for(size_t i = (heapsize - 2) / 2;; --i)
{
struct THeapIterator iter = heap_iterator_begin(aHeap);

// Posun iterátoru na pozici i
for(size_t j = 0; j < i; ++j)
	heap_iterator_to_next(&iter);

const THeapElement value = heap_iterator_value(&iter);
heap_iterator_alg_sift_down(iter, value);

if(i == 0)
	break;
}
 }

void heap_sort_with_iterators(struct TVector *aVector)
{
	//	for(size_t i = 0; i < vector_size(aVector); ++i)
	//		if(!vector_element_store_file(aVector->iValues[i], stdout))
	//			fputs("Function 'vector_element_store_file()' failed!\n", stderr);
	//	putchar('\n');

	if(vector_size(aVector) < 2)
		return;

	//auto heap = heap_create(*aVector);		// `auto` since C23
	struct THeap heap = heap_create(*aVector);

	//	heap_dump(&heap, stdout);

	heap_iterator_alg_heapify(&heap);

	//	heap_dump(&heap, stdout);

	//	fputs("Heapify stats:\n", stdout);
	//	if(!vector_print_sortstats(aVector, stdout))
	//		fputs("Function 'vector_print_sortstats()' failed!\n", stderr);

	size_t heapsize = heap_size(&heap);

	while(heapsize > 1)
	{
		struct THeapIterator root = heap_iterator_begin(&heap);
		const struct THeapIterator last = heap_iterator_last(&heap);

		//		heap_dump(&heap, stdout);

		const THeapElement value = heap_iterator_value(&last);
		heap_move_with_iterators(&last, &root);

		heapsize = heap_decrement_size(&heap);

		//		fprintf(stdout, "Value: %" TVECTOR_ELEMENT_FRMSTR "\n", value);
		//		heap_dump(&heap, stdout);

		heap_iterator_alg_sift_down(root, value);

		//		heap_dump(&heap, stdout);
	}
}
