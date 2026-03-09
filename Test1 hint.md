# Project setup
## Configuration Properties / General
**C++ Languague standard:** ``C++ ISO 14``<br>
**C language standard:** ``Preview - Features from the Latest C Working Draft (std:clatest)``

## C/C++ / Preprocessor
**Preprocessor Definitions:** ``_CRT_SECURE_NO_WARNINGS;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)``

## Generic includes and int main() for saving some seconds
```
#include <stdio.h>
#include <stdlib.h>
#include /*DataTypeHeader*/
#include "check.h"

int main()
{

    return 0;
}
```

# TVector
**``struct TVector``** obsahuje dynamicky alokonné pole prvků ``TVectorElement *iValues`` a jeho velikost ``size_t iSize``

# TStack s polem
**``struct TStack``** obsahuje pole ``TStackElement iValues[STACK_MAXCOUNT]`` o maximální definované velikosti ``#define STACK_MAXCOUNT`` a počítadlo aktuálního posledního indexu ``size_t iCount``

# TStack se seznamem
**``struct TStack``** obsahuje odkaz na horní uzel zásobníku ``struct TStackNode *iTop``<br>
Ten pak obsahuje jeho hodnotu ``TStackElement iValue`` a odkaz na následující uzel zásobníku ``struct TStackNode *iNext``

# TQueue s polem
**``struct TQueue``** obsahuje pole prvků pevné šířky ``TQueueElement iValues[QUEUE_MAXCOUNT]`` a ukazatele na počáteční index ``size_t iFrontPos`` a končný index ``size_t iBackPos`` dat