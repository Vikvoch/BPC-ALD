/** \file main_tg_stack.c
 *  \brief Hlavní program pro testování ADT TStack
 *  \author Petyovský
 *  \version 2026
 *  $Id: main_tg_stack.c 3229 2026-03-02 16:14:51Z petyovsky $
 */

#include <stdio.h>
#include <ctype.h>
#include "TStack.h"
#include "main_support.h"
#include "tgadt.h"

/** \defgroup MainProgram 2. Hlavní program
 *  \brief Definice funkcí hlavního programu
 *  \{
 */

/** \brief Testování API Stack
 *  \details Testovací funkce pro API Stack. Funkce načítá z konzoly znaky, které ukládá po slovech do zásobníku. Slovo obsahuje pouze písmena a číslice. Po nalezení konce slova, následně znaky ze zásobníku vybírá, ruší a tiskne.
 */
void demo_tiskni_slova_pozpatku(void)
	{
	struct TStack stack = { 0 };
	init(&stack);
	int znak = 0;
	do
		{
		znak = getchar();
		while(isalnum(znak))
			{
			UNLESS(push(&stack, znak));
			znak = getchar();
			}

		while(!is_empty(&stack))
			{
			int val = 0;
			UNLESS(top(&stack, &val), goto cleanup_demo);
			UNLESS(pop(&stack), goto cleanup_demo);
			putchar(val);
			}
		putchar(znak);
		}
	while(znak != '\n');

cleanup_demo:
	destroy(&stack);
	}

int main_tg_stack(int argc, char *argv[])
	{
	struct TStack stack1 = { 0 };
	init(&stack1);
	printf("stack1 is empty: %s\n", bool_to_cstring(is_empty(&stack1)) );
	UNLESS(push(&stack1, 0));
	printf("stack1 is empty: %s\n", bool_to_cstring(is_empty(&stack1)) );

	UNLESS(push(&stack1, 222));
	for(struct TStackIterator it = begin(&stack1); is_valid(&it); to_next(&it))
		printf(TSTACK_ELEMENT_FRMSTR " ", value(&it));
	putchar('\n');

	UNLESS(push(&stack1, 42));
	UNLESS(push(&stack1, 43));
	UNLESS(push(&stack1, 40));

	for(struct TStackIterator it = begin(&stack1); is_valid(&it); to_next(&it))
		printf(TSTACK_ELEMENT_FRMSTR " ", value(&it));
	putchar('\n');

	TStackElement val = 0;
	if(top(&stack1, &val))
		printf(TSTACK_ELEMENT_FRMSTR "\n", val);

	UNLESS(pop(&stack1));

	for(struct TStackIterator it = begin(&stack1); is_valid(&it);to_next(&it))
		printf(TSTACK_ELEMENT_FRMSTR " ", value(&it));
	putchar('\n');

	destroy(&stack1);

	printf("Zadej retezec:\n");
	demo_tiskni_slova_pozpatku();

	return 0;
	}

/** \} MainProgram */
