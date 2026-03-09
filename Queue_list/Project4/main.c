#include <stdio.h>
#include <stdlib.h>
#include "TQueue.h"
#include "check.h"

int main()
{
    struct TQueue queue1 = { 0 };
    struct TQueue queue2 = { 0 };
    queue_init(&queue1);
    queue_init(&queue2);
    char data;
    do
    {
        data = getchar();
        if(data == ' ')
        {
            for(struct TQueueIterator it = queue_iterator_begin(&queue2); queue_iterator_is_valid(&it); queue_iterator_to_next(&it))
                printf(TQUEUE_ELEMENT_FRMSTR ,queue_iterator_value(&it));
            bool isPalindrome = true;
            while(!queue_is_empty(&queue1))
            {
                TQueueElement element1, element2;
                queue_front(&queue1, &element1);
                queue_front(&queue2, &element2);
                if(element1 != element2)
                    isPalindrome = false;
                queue_pop(&queue1);
                queue_pop(&queue2);
            }
            switch(isPalindrome)
            {
            case true:
                printf("Slovo je palindrom :-)\n");
                break;
            default:
                printf("Slovo neni palindrom :-(\n");
                break;
            }
        }
        else
        {
            if(!queue_push_front(&queue1, data) || !queue_push(&queue2, data))
            {
                queue_destroy(&queue1);
                queue_destroy(&queue2);
                printf("Chyba vkládání elementù!");
                return 1;
            }
        }
    } while(data != '\n');
    return 0;
}