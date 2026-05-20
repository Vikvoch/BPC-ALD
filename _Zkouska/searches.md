[<- Back](Zkouska.md)
# Vyhledávání
- Od kdy je lepší nejprve setřídit a pak až vyhledávat<br>

![](searchVsSort.png)
## Linear probing
- Postupně prochází lineární seznam/pole dokud nenajde požadovaný prvek, nebo nedojde na konec = hledaný prvek tam není
- Množina je z pravidla nesetříděná (ale není to nutné)

## Binární vyhledávání
- Vyžaduje setříděnou množinu
- využívá metody postupné aproximace půlením intervalu

## Binary search tree
- Využívá binární strom
- Sestaví se z množiny *in-order* průchodem
- **Vyšší hledaná hodnota:** posun doleva dolů
- **Nižší hledaná hodnota:** posun doprava dolů
```
1 2 4 5 7 8 15 28 31 39
// Hledáme: 15

       |7|              //  7 < 15 -> doprava
    /       \
   2       |28|         // 28 > 15 -> doleva
  / \      /  \
 1   4   |8|  31        //  8 < 15 -> doprava
      \    \    \
       5  |15|  39      // 15 = 15 -> máme hodnotu       
```

## AVL strom


## B strom

## SkipList
- Ze slova Skip v názvu této vyhledávací metody je patrné, že se má skipnout, neboli přeskočit
- Vzhledem k tomu že tato metoda využívá náhodu, tak i já toto nechám na náhodu

## Hashování

## Porovnání vyhledávacích funkcí
![](searchComparsion.png)