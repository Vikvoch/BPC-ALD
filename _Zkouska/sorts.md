[<- Back](Zkouska.md)
# Třídění
- **Stabilní třízení:** Stejné prvky jsou zachovány v půvpdním pořadí
- **Nestabilní třízení:** Stejné prvky mohou být přehazovány<br><br>
- **In-place:** třízení probíhá v prostoru paměti třízených dat
- **Out-of-place:** je potřeba vnější<br><br>
- **^=^:** operátor porovnání bez prohození
- **^-^:** operátor porovnání s prohozením

## Insert sort
- Postupně posouváme každý prvek dokud není menší než předchozí prvek<br>
```
5|2 4 1 3
^-^
2 5|4 1 3
  ^-^
2 4 5|1 3
^=^
2 4 5|1 3
    ^-^
2 4 1 5|3
  ^-^
2 1 4 5|3
^-^
1 2 4 5|3
      ^-^
1 2 4 3|5
    ^-^
1 2 3 4|5
  ^=^
1 2 4 3|5
^=^
```

## Bubble sort
- Největší prvek probublává vzhůru
- Postupně porovnáváme dvojice sousedních prvků a v případě špatného pořadí swapujeme
- Největší se při každém průchodu dostane na konec -> při dalším průchodu můžeme skončit o prvek dříve
- Optimalizace možná ukončením pokud nedojde k žádné výměně<br>
```
5 2 4 1 3
^-^
2 5 4 1 3
  ^-^
2 4 5 1 3
    ^-^
2 4 1 5 3
      ^-^
2 4 1 3|5
^=^
2 4 1 3|5
  ^-^
2 1 4 3|5
    ^-^
2 1 3|4 5
^-^
1 2 3|4 5
  ^=^
1 2|3 4 5
^=^
```

## Shaker sort
- obdoba bubble sortu, ale střídá směr z vrchu a zespodu
```
5 2 4 1 3
^-^
2 5 4 1 3
  ^-^
2 4 5 1 3
    ^-^
2 4 1 5 3
      ^-^
2 4 1 3|5
    ^=^
2 4 1 3|5
  ^-^
2 1 4 3|5
^-^
1|2 4 3|5
  ^=^
1|2 4 3|5
    ^-^
1 2|3|4 5
```

## Select sort
- Hledá index minima v celé nesetřízené oblasti a ten na konci swapne s prvním nesetřízeným prvkem
- V ukázce indexace od 0
```
5 2 4 1 3 -> [3]
^-----^
1 2 4 5 3 -> [1]
  ^
1 2 4 5 3 -> [4]
    ^---^
1 2 3 5 4 -> [3]
      ^-^
1 2 3 4 5
```

## Shell sort
- Insert sort na steroidech
- Oblasti se dělí na polovinu
```
8 5 3 1|4 7 6 2
^-------^
4 5 3 1|8 7 6 2
  ^=======^
4 5 3 1|8 7 6 2
    ^=======^
4 5 3 1|8 7 6 2
      ^=======^
4 5|3 1|8 7|6 2
^---^
3 5|4 1|8 7|6 2
  ^---^
3 1|4 5|8 7|6 2
        ^---^
3 1|4 5|6 7|8 2
          ^---^
3|1 4 5 6 2 8 7   // odtud classic insert sort
^-^
1 3|4 5 6 2 8 7
  ^=^
1 3 4|5 6 2 8 7
    ^=^
1 3 4 5|6 2 8 7
      ^=^
1 3 4 5 6|2 8 7
        ^-^
1 3 4 5 2 6|8 7
      ^-^
1 3 4 2 5 6|8 7
    ^-^
1 3 2 4 5 6|8 7
  ^-^
1 2 3 4 5 6|8 7
          ^=^
1 2 3 4 5 6 8|7
            ^-^
1 2 3 4 5 6 7 8
```

## Porovnání třídících algoritmů
![](basicSorts.png)