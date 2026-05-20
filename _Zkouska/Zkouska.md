# Generic type shit
## Složitost algoritmu
- Horní odhad složitosti $O(f(n))$: maximální možný čas, který bude algoritmus potřebovat
- Dolní odhad složitosti $\Omega(f(n))$: minimální možný čas, který bude algoritmus potřebovat
- Těsná odhad složitosti $\Theta(f(n))$: pouze pokud se horní a dolní odhad shoduje

Výpočet časové složitosti je závislý na počtu cyklů

# Datatypes
### Kontejnery
- Immutable = bez možnosti přidávání/odebírání
- Mutable = v průběhu lze přidávat/odebírat<br><br>
- Ordered
- Unordered
### First calss citizen
- Lze jej přiřadit do proměnné
- Lze jej předat jako parametr funkce
- Lze jej vrátit z funkce
- Lze je porovnávat

## Lineární datové typy
### Immutable pole
`int array[MAXSIZE];`
- Nelze upravovat počet hodnot v poli
- Snadný přístup k libovolnému prvku

### Dynamické pole
```
struct TStack {
	size_t size;
	int values[MAXCOUNT];
};
```
- Vytvářeno dynamickou alokací paměti
- Není efektivní pro úpravu počtu hodnot - zvláště z prostředka
- Při úpravě počtu elementů se musí pole realokovat

### Dynamické pole s amortizací
```
#define UPPER_RESIZE
#define LOWER_RESIZE
struct TStack {
	size_t size;
	int values[MAXCOUNT];
};
```
- Vytvářeno dynamickou alokací paměti
- Není efektivní pro úpravu počtu hodnot - zvláště z prostředka
- Nechávají se prázdné elementy na konci
- Velikost se realokuje (zdvojnásobuje / zmenšuje na polovinu) až když `size > UPPER_RESIZE` nebo `size < LOWER_RESIZE`

### Vázaný seznam
```
struct linkedList {
    int data;
    struct linkedList *nextNode;
};
```
- Každý node obsahuje jeho hodnotu adresu následujícího prvku, poslení node má `struct linkedList *nextNode == NULL`
- Je potřeba znát adresu prvního nodu
- Je možné mít i odkaz na předchozí
- Práce je složitější - nemáme přístup k libovolnému prvku
- Vhodné pokud budeme častu přídávat/odebírat hodnoty uprostřed<br>

![](linkedList.png)

### Kruhové pole
```
struct circularBuffer {
	size_t frontPos;
	size_t backPos;
	int values[MAXSIZE];
};
```
- Obsahuje 2 ukazatele (na začátek a na konec)
- Lze snadno přidávat/odebírat ze začátku i konce
- `frontPos == backPos` -> pole je prázdné
- `frontPos == backPos + 1` -> pole je plné
- **Lze mít kruhové pole s amortizací**<br>

![](circularBuffer.png)

### Porovnání časové složitosti jednotlivých lineárních datových typů
![](adtComparsion.png)

### Zásobník
- LIFO (last in first out)
- Lze implementovat polem / vázaným seznamem

### Fronta
- FIFO (first in first out)
- Posuvný registr
- Implementace polem / lineárně vázaným seznamem
- **Obousměrná fronta:** lze vkládat a odebírat ze začátku i konce, implementace kruhovým polem
- **Prioritní fronta:** prvek je přidán před všechny prvky s nižsí prioritou, ale za všechny prvky se stejnou nebo vyšší prioritou