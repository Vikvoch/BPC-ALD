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

# Datatypes

## TVector
**``struct TVector``** obsahuje dynamicky alokonné pole prvků ``TVectorElement *iValues`` a jeho velikost ``size_t iSize``

## TStack s polem
**``struct TStack``** obsahuje pole ``TStackElement iValues[STACK_MAXCOUNT]`` o maximální definované velikosti ``#define STACK_MAXCOUNT`` a počítadlo aktuálního posledního indexu ``size_t iCount``

## TStack se seznamem
**``struct TStack``** obsahuje odkaz na horní uzel zásobníku ``struct TStackNode *iTop``<br>
Ten pak obsahuje jeho hodnotu ``TStackElement iValue`` a odkaz na následující uzel zásobníku ``struct TStackNode *iNext``

## TQueue s polem
**``struct TQueue``** obsahuje pole prvků pevné šířky ``TQueueElement iValues[QUEUE_MAXCOUNT]`` a ukazatele na počáteční index ``size_t iFrontPos`` a končný index ``size_t iBackPos`` dat

# Basic_sorts

## Insert sort
Prosívá prvek dolů dokud je menší než předchozí

## Select sort
Hledá index minima v nesetříděné oblasti v listu, swapne ho na začátek nesetříděné oblasti

## Bubble sort
Postupně porovnává dvojice sousedních prvků od začátku listu. Pokud je vlevo větší, swapne. Tím se největší dostává nakonec

## Bubble sort optimized
Pokud při průchodu nejdojde k žádné výměně, je setříděno (nemusí se procházet pro kažný element)

## Bubble sort optimized 2
Hlídá si index posledního swapu -> zkracuje konec pole

## Shaker sort
Podobné jako bubble sort, ale jezdí od začátku (nese největší prvky) od konce (nese nejmenší prvky)

# Basic_sorts_element_struct
Umožňuje sortovat podle zvoleného parametru datatypů ve struktuře

# Fibonacci
Různé způsoby implementace počítačky fibonacciho posloupnosti

# Wildcard_match
Porovnávání řeťezců na základě wildcard znaků `*` a `?`

# Anvanced_sorts

## Shell sort
Postupně zmenšuje vzdálenost mezi prvky -> částečné setřídění -> finální setřídění

## Quick sort
Vybírá pivot -> rozděluje pole -> rekurzivně třídí obě části

# Anvanced_sorts_with_span
Doplňuje o Quick sort se spanem (lze sortit jen určitou část vektoru)

# Powerful_sorts

## Heap sort
Využívá binární strom. Obdoba bubble sortu

## Merge sort

# TSet_unsorted_dynamic_array
Postupně prochází list dokud nenarazí na hledaný prvek, nebo na konec

# TSet_sorted_dynamic_array
Využívá setříděnost pole

## LINEAR_SEARCH_OPTIMIZED
Lineárně prochází seznam a porovnává s požadovaným prvkem. Pokud je prvek větší než hledaný, hledání se ukončí (prvek tam nemůže být <-> je to setříděné)

## BINARY_SEARCH
Začíná na půlce, funguje na základě dělení intervalů

# TSet_unordered_hash_table
Využívá hashování pro vyhledávání prků v poli