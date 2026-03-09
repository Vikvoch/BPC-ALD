/** \file TStack.c
 *  \brief Implementace API pro typ zásobník (realizace pomocí lineárního jednosmìrnì vázaného seznamu)
 *  \author Petyovský
 *  \version 2026
 *  $Id: TStack.c 3201 2026-02-13 18:07:58Z petyovsky $
 */

#include "TStack.h"

 /** \brief Úplná definice privátního typu StackNode
  *  \details Privátní typ StackNode (nedostupný mimo funkce ze souboru TStack.c) reprezentuje typ pro jednotlivé uzly lineárního jednosmìrnì vázaného seznamu.
  */
struct TStackNode {
	struct TStackNode *iNext;				///< Ukazatel na následující uzel lineárního jednosmìrnì vázaného seznamu
	TStackElement iValue;					///< Element zásobníku uložený v uzlu lineárního jednosmìrnì vázaného seznamu
};

void stack_init(struct TStack *aStack)
{
	if(aStack == NULL)
		return;
	aStack->iTop = NULL;
}

bool stack_init_file(struct TStack *aStack, FILE *aInputFile)
{
	if(aStack == NULL || aInputFile == NULL)
		return false;
	int dataCnt;
	if(fscanf(aInputFile, "%d", &dataCnt) != 1)
		return false;
	for(int i = 0; i < dataCnt; i++)
	{
		TStackElement newData;
		if(fscanf(aInputFile, TSTACK_ELEMENT_FRMSTR, &newData) != 1)
		{
			stack_destroy(aStack);
			return false;
		}
		if(!stack_push(aStack, newData))
		{
			stack_destroy(aStack);
			return false;
		}
	}
	return true;
}

bool stack_is_empty(const struct TStack *aStack)
{
	if(aStack == NULL || aStack->iTop == NULL)
		return 1;
	return 0;
}

bool /* TStackIterator */ stack_top(const struct TStack *aStack, TStackElement *aValue)
{
	if(aStack == NULL || aStack->iTop == NULL || aValue == NULL)
		return 0;
	*aValue = aStack->iTop->iValue;
	return 1;
}

bool stack_push(struct TStack *aStack, TStackElement aValue)
{
	if(aStack == NULL)
		return 0;
	struct TStackNode *new_node = malloc(sizeof(struct TStackNode));
	if(new_node == NULL)
		return 0;
	new_node->iNext = aStack->iTop;
	new_node->iValue = aValue;
	aStack->iTop = new_node;
	return 1;
}

bool stack_pop(struct TStack *aStack)
{
	if(aStack == NULL || aStack->iTop == NULL)
		return 0;
	struct TStackNode *pop_node = aStack->iTop;
	aStack->iTop = aStack->iTop->iNext;
	free(pop_node);
	return 1;
}

void stack_destroy(struct TStack *aStack)
{
	if(aStack == NULL || aStack->iTop == NULL)
		return;
	while(stack_pop(aStack));
}

struct TStackIterator stack_iterator_begin(const struct TStack *aStack)
{
	if(aStack == NULL || aStack->iTop == NULL)
		return (struct TStackIterator) { .iStack = NULL, .iActual = NULL };
	return (struct TStackIterator) { .iStack = aStack, .iActual = aStack->iTop };

}

bool stack_iterator_is_valid(const struct TStackIterator *aIter)
{
	if(aIter == NULL || aIter->iStack == NULL || aIter->iStack->iTop == NULL || aIter->iActual == NULL)
		return 0;
	return 1;
}

bool stack_iterator_to_next(struct TStackIterator *aIter)
{
	if(!stack_iterator_is_valid(aIter))
		return 0;
	aIter->iActual = aIter->iActual->iNext;
	return aIter->iActual != NULL;
}

TStackElement stack_iterator_value(const struct TStackIterator *aIter)
{
	if(!stack_iterator_is_valid(aIter))
		return (TStackElement) { 0 };
	return aIter->iActual->iValue;
}
