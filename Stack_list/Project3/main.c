#include <stdio.h>
#include <stdlib.h>
#include "TStack.h"
#include "check.h"

int main()
{
	struct TStack stack = { 0 };
	FILE *inputFile = fopen("stack_data.txt", "r");
	if(inputFile == NULL)
		return 1;
	if(!stack_init_file(&stack, inputFile))
	{
		fclose(inputFile);
		return 2;
	}
	fclose(inputFile);
	for(struct TStackIterator it = stack_iterator_begin(&stack); stack_iterator_is_valid(&it); stack_iterator_to_next(&it))
		printf(TSTACK_ELEMENT_FRMSTR " ", stack_iterator_value(&it));
	printf("\n");
	TStackElement val;
	if(!stack_is_empty(&stack))
	{
		stack_top(&stack, &val);
		printf(TSTACK_ELEMENT_FRMSTR " ", val);
		stack_pop(&stack);
	}
	while(!stack_is_empty(&stack))
	{
		TStackElement val2;
		stack_top(&stack, &val2);
		stack_pop(&stack);
		if(val2 < val)
			printf("\n");
		printf(TSTACK_ELEMENT_FRMSTR " ", val2);
		val = val2;
	}

	return 0;
}