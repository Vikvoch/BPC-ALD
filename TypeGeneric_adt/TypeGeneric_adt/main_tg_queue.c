/** \file main_tg_queue.c
 *  \brief Hlavní program pro testování ADT TQueue
 *  \author Petyovský
 *  \version 2026
 *  $Id: main_tg_queue.c 3229 2026-03-02 16:14:51Z petyovsky $
 */

#include <stdio.h>
#include "TQueue.h"
#include "main_support.h"
#include "tgadt.h"

/** \defgroup MainProgram 3. Hlavní program
 *  \brief Definice funkcí hlavního programu
 *  \{
 */

/** \brief Vytisknutí elementu fronty pomocí iterátoru
 *  \details Tisk hodnoty elementu fronty, na který ukazuje předaný iterátor.
 *  \param[in] aIter Ukazatel na existující iterátor
 */
static void print_element(const struct TQueueIterator *aIter)
	{
	printf("<" TQUEUE_ELEMENT_FRMSTR "> ", value(aIter));
	}

/** \brief Porovnání hodnoty elementu fronty pomocí iterátoru s hodnotou 43
 *  \details Příklad predikátové funkce. Porovnání hodnoty elementu fronty, na který ukazuje předaný iterátor s hodnotou 43.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \return \c true pokud je hodnota elementu fronty na který ukazuje iterátor rovna hodnotě 43
 */
[[nodiscard]] static bool is_element_with_value_43(const struct TQueueIterator *aIter)
	{
	return value(aIter) == 43;
	}

int main_tg_queue(int argc, char *argv[])
	{
	struct TQueue queue1 = { 0 };
	init(&queue1);

	printf("queue1 is empty: %s\n", bool_to_cstring(is_empty(&queue1)) );
	UNLESS(push(&queue1, 0));
	printf("queue1 is empty: %s\n", bool_to_cstring(is_empty(&queue1)) );

	UNLESS(push(&queue1, 222));
	for(struct TQueueIterator it = begin(&queue1); is_valid(&it); to_next(&it))
		printf(TQUEUE_ELEMENT_FRMSTR " ", value(&it));
	putchar('\n');

	UNLESS(push(&queue1, 42));
	UNLESS(push(&queue1, 43));
	UNLESS(push(&queue1, 40));

	for(struct TQueueIterator it = begin(&queue1); is_valid(&it); to_next(&it))
		print_element(&it);
	putchar('\n');

	for_each(begin(&queue1), print_element);
	putchar('\n');

	struct TQueueIterator it = find_if(begin(&queue1), is_element_with_value_43);
	UNLESS(set_value(&it, 128));
	putchar('\t');
	for_each(it, print_element);
	putchar('\n');

	it = find_if_not(begin(&queue1), is_element_with_value_43);
	UNLESS(set_value(&it, 64));
	putchar('\t');
	for_each(it, print_element);
	putchar('\n');

	for_each(begin(&queue1), print_element);
	putchar('\n');

	TQueueElement val = 0;
	if(front(&queue1, &val))
		printf("queue1 front: " TQUEUE_ELEMENT_FRMSTR "\n", val);
	if(back(&queue1, &val))
		printf("queue1 back: " TQUEUE_ELEMENT_FRMSTR "\n", val);

	while(!is_empty(&queue1))
		UNLESS(pop(&queue1));

	UNLESS(push(&queue1, 99));
	for_each(begin(&queue1), print_element);
	putchar('\n');

	destroy(&queue1);
	return 0;
	}

/** \} MainProgram */
