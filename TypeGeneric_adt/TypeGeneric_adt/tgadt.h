#ifndef TGADT_H
#define TGADT_H
/** \file tgadt.h
 *  \brief Implementation of the Type Generic ADT API macros for all BPC-ALD containers
 *  \author Petyovský
 *  \version 2026
 *  $Id: tgadt.h 3217 2026-03-02 15:36:06Z petyovsky $
 */

#if defined(DOXYGEN_PREPROCESSING)		// Enabled only during doxygen preprocessing
	#define TVECTOR_H
	#define TSTACK_H
	#define TQUEUE_H
	#define TSET_H
#endif

#if !defined(TVECTOR_H) && !defined(TSTACK_H) && !defined(TQUEUE_H) && !defined(TSET_H)
	#error "Missing previous include of any ADT headers"
#endif

// http://jhnet.co.uk/articles/cpp_magic
// https://github.com/JacksonAllan/CC/blob/main/articles/Better_C_Generics_Part_1_The_Extendible_Generic.md

// IF_DEF(macro)(code) includes the bracketed code only if the specified macro is defined (as empty).
#define COMMA()				,
#define ARG_2_(_1, _2, ...)	_2
#define ARG_2(...)			ARG_2_(__VA_ARGS__)
#define INCL(...)			__VA_ARGS__
#define OMIT(...)
#define IF_DEF(macro)		ARG_2(COMMA macro() INCL, OMIT,)


// Implementation of the Type Generic ADT API macros

/** \brief Default inicializace ADT
 *  \details Dynamicky alokuje paměť pro ADT a elementů, inicializuje elementy na hodnotu 0.
 *  \param[in,out] aT Ukazatel na místo v paměti určené pro inicializaci ADT
 *  \return \c true pokud byl ADT úspěšně vytvořen a inicializován
 */
#define init(aT)										\
	_Generic((aT)										\
		IF_DEF(TVECTOR_H)								\
			(											\
			,struct TVector*:				vector_init	\
			)											\
		IF_DEF(TSTACK_H)								\
			(											\
			,struct TStack*:				stack_init	\
			)											\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_init	\
			)											\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_init	\
			)											\
		)(aT)

#if defined(TVECTOR_H)
/** \brief Inicializace ADT a jeho elementů na náhodné hodnoty
 *  \details Dynamicky alokuje paměť pro ADT o zadaném počtu elementů, inicializuje elementy na náhodné hodnoty.
 *  \param[in,out] aT Ukazatel na místo v paměti určené pro inicializaci ADT
 *  \param[in] aSize Požadovaný počet elementů ADT
 *  \return \c true pokud byl ADT úspěšně alokován a inicializován
 */
#define init_random(aT, ...)									\
	_Generic((aT)												\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVector*:				vector_init_random	\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TVECTOR_H)
/** \brief Inicializace ADT a jeho elementů ze souboru
 *  \details Načte ze souboru počet elementů ADT, dynamicky alokuje paměť pro ADT o načteném počtu elementů, načte ze souboru hodnoty jednotlivých elementů.
 *  \param[in,out] aT Ukazatel na místo v paměti určené pro inicializaci ADT
 *  \param[in,out] aInputFile Ukazatel na soubor otevřený v módu pro čtení
 *  \return \c true pokud byl ADT z dat v souboru úspěšně alokován a inicializován
 */
#define init_file(aT, ...)										\
	_Generic((aT)												\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVector*:				vector_init_file	\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TVECTOR_H)
/** \brief Vytvoření úplné hodnotové kopie ADT
 *  \details Dynamicky alokuje paměť pro nový ADT o shodném počtu elementů, nakopíruje hodnoty všech elementů ze starého do nového ADT.
 *  \param[in] aT Ukazatel na místo v paměti obsahující zdrojový ADT
 *  \param[in,out] aTClone Ukazatel na místo v paměti určené pro vytvořenou hodnotovou kopii ADT
 *  \return \c true pokud byl nový ADT úspěšně alokován a inicializován
 */
#define clone(aT, ...)										\
	_Generic((aT)											\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVector*:				vector_clone	\
			,const struct TVector*:			vector_clone	\
			)												\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TVECTOR_H)
 /** \brief Uložení ADT a jeho elementů do souboru
  *  \details Uloží do souboru počet elementů ADT a hodnoty jednotlivých elementů.
  *  \param[in] aT Ukazatel na existující ADT
  *  \param[in,out] aOutputFile Ukazatel na soubor otevřený v módu pro zápis
  *  \return \c true pokud byl ADT a jeho elementy úspěšně uloženy do souboru
  */
#define store_file(aT, ...)										\
	_Generic((aT)												\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVector*:				vector_store_file	\
			,const struct TVector*:			vector_store_file	\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TVECTOR_H) || defined(TSET_H)
/** \brief Přečtení počtu elementů ADT
 *  \details Vrací velikost (počet elementů) ADT.
 *  \param[in] aT Ukazatel na existující ADT
 *  \return Počet elementů ADT nebo hodnota 0 v případě chyby
 */
#define size(aT)										\
	_Generic((aT)										\
		IF_DEF(TVECTOR_H)								\
			(											\
			,struct TVector*:				vector_size	\
			,const struct TVector*:			vector_size	\
			)											\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_size	\
			,const struct TSet*:			set_size	\
			)											\
	)(aT)
#endif

/** \brief Zjištění, zda je ADT prázdný.
 *  \details Funkce (predikát) vracející \c bool hodnotu reprezentující test, zda je ADT prázdný (tj. má nulový počet elementů).
 *  \param[in] aT Ukazatel na existující ADT
 *  \return \c true pokud je ADT prázdný
 */
#define is_empty(aT)										\
	_Generic((aT)											\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVector*:				vector_is_empty	\
			,const struct TVector*:			vector_is_empty	\
			)												\
		IF_DEF(TSTACK_H)									\
			(												\
			,struct TStack*:				stack_is_empty	\
			,const struct TStack*:			stack_is_empty	\
			)												\
		IF_DEF(TQUEUE_H)									\
			(												\
			,struct TQueue*:				queue_is_empty	\
			,const struct TQueue*:			queue_is_empty	\
			)												\
		IF_DEF(TSET_H)										\
			(												\
			,struct TSet*:					set_is_empty	\
			,const struct TSet*:			set_is_empty	\
			)												\
	)(aT)

#if defined(TVECTOR_H)
/** \brief Změna velikosti existujícího ADT
 *  \details Změna počtu elementů ADT, alokace nové dynamické paměti pro ADT o novém počtu prvků, kopie prvků z původního ADT, inicializace doplněných prvků na hodnoty 0, dealokace dynamické paměti původního ADT.
 *  \param[in,out] aT Ukazatel na existující ADT
 *  \param[in] aNewSize Nový počet elementů ADT
 *  \return \c true pokud byl ADT úspěšně přealokován a všechny elementy nového ADT byly úspěšně inicializovány
 */
#define resize(aT, ...)										\
	_Generic((aT)											\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVector*:				vector_resize	\
			)												\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

/** \brief Přečtení hodnoty elementu z požadované pozice v ADT
 *  \details Přečtení hodnoty elementu z požadované pozice defv ADT pomocí indexu / iterátoru.
 *  \param[in,out] aT Ukazatel na existující ADT určený pro přečtení hodnoty elementu nebo iterátor do daného ADT
 */
#define value(aT, ...)												\
	_Generic((aT)													\
		IF_DEF(TVECTOR_H)											\
			(														\
			,struct TVector*:				vector_value			\
			,const struct TVector*:			vector_value			\
			,struct TVectorIterator*:		vector_iterator_value	\
			,const struct TVectorIterator*:	vector_iterator_value	\
			)														\
		IF_DEF(TSTACK_H)											\
			(														\
			,struct TStackIterator*:		stack_iterator_value	\
			,const struct TStackIterator*:	stack_iterator_value	\
			)														\
		IF_DEF(TQUEUE_H)											\
			(														\
			,struct TQueueIterator*:		queue_iterator_value	\
			,const struct TQueueIterator*:	queue_iterator_value	\
			)														\
		IF_DEF(TSET_H)												\
			(														\
			,struct TSetIterator*:			set_iterator_value		\
			,const struct TSetIterator*:	set_iterator_value		\
			)														\
	)(aT __VA_OPT__(,) __VA_ARGS__)

/** \brief Zapsání hodnoty elementu do ADT na požadovanou pozici
 *  \details Zápis nové hodnoty elementu do ADT na požadovanou pozici (index/iterátor).
 *  \param[in,out] aT Ukazatel na existující ADT určený pro zapsání hodnoty elementu nebo iterátor do daného ADT
 *  \param[in] aValue Nová hodnota elementu
 */
#define set_value(aT, ...)												\
	_Generic((aT)														\
		IF_DEF(TVECTOR_H)												\
			(															\
			,struct TVector*:				vector_set_value			\
			,const struct TVector*:			vector_set_value			\
			,struct TVectorIterator*:		vector_iterator_set_value	\
			,const struct TVectorIterator*:	vector_iterator_set_value	\
			)															\
		/*																\
		IF_DEF(TSTACK_H)												\
			(															\
			,struct TStackIterator*:		stack_iterator_set_value	\
			,const struct TStackIterator*:	stack_iterator_set_value	\
			)															\
		*/																\
		IF_DEF(TQUEUE_H)												\
			(															\
			,struct TQueueIterator*:		queue_iterator_set_value	\
			,const struct TQueueIterator*:	queue_iterator_set_value	\
			)															\
	)(aT __VA_OPT__(,) __VA_ARGS__)

#if defined(TSTACK_H) || defined(TQUEUE_H)
/** \brief Získání hodnoty elementu z vrcholové pozice v ADT
 *  \details Přečte hodnotu elementu z vrcholové pozice v ADT.
 *  \param[in] aQueue Ukazatel na existující ADT
 *  \param[in,out] aValue Ukazatel na místo v paměti určené pro načtení hodnoty elementu z vrcholové pozice v ADT
 *  \return \c true pokud byla hodnota elementu z vrcholové pozice v ADT úspěšně načtena
 */
#define top(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TSTACK_H)								\
			(											\
			,struct TStack*:				stack_top	\
			,const struct TStack*:			stack_top	\
			)											\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_front	\
			,const struct TQueue*:			queue_front	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TQUEUE_H)
/** \brief Získání hodnoty elementu z počáteční pozice v ADT
 *  \details Přečte hodnotu elementu z počáteční pozice v ADT.
 *  \param[in] aQueue Ukazatel na existující ADT
 *  \param[in,out] aValue Ukazatel na místo v paměti určené pro načtení hodnoty elementu z počáteční pozice v ADT
 *  \return \c true pokud byla hodnota elementu z počáteční pozice v ADT úspěšně načtena
 */
#define front(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_front	\
			,const struct TQueue*:			queue_front	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TQUEUE_H)
/** \brief Získání hodnoty elementu z koncové pozice v ADT
 *  \details Přečte hodnotu elementu z koncové pozice v ADT.
 *  \param[in] aQueue Ukazatel na existující ADT
 *  \param[in,out] aValue Ukazatel na místo v paměti určené pro načtení hodnoty elementu z koncové pozice v ADT
 *  \return \c true pokud byla hodnota elementu z koncové pozice v ADT úspěšně načtena
 */
#define back(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_back	\
			,const struct TQueue*:			queue_back	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TSTACK_H) || defined(TQUEUE_H) || defined(TSET_H)
/** \brief Vložení elementu do ADT
 *  \details Vkládá hodnotu elementu do ADT.
 *  \param[in,out] aT Ukazatel na existující ADT určený pro vložení elementu
 *  \param[in] aValue Hodnota elementu vkládaná do ADT
 *  \return \c true pokud byla hodnota do ADT úspěšně vložena
 */
#define push(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TSTACK_H)								\
			(											\
			,struct TStack*:				stack_push	\
			)											\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_push	\
			)											\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_insert	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TSTACK_H) || defined(TQUEUE_H)
/** \brief Odstranění elementu z přední pozice v ADT
 *  \details Odstraní hodnotu elementu z přední pozice v ADT.
 *  \param[in,out] aT Ukazatel na existující ADT určený pro odstranění elementu
 *  \return \c true pokud byla hodnota z ADT úspěšně odstraněna
 */
#define pop(aT)											\
	_Generic((aT)										\
		IF_DEF(TSTACK_H)								\
			(											\
			,struct TStack*:				stack_pop	\
			)											\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_pop	\
			)											\
	)(aT)
#endif

#if defined(TSTACK_H) || defined(TQUEUE_H) || defined(TSET_H)
/** \brief Vložení elementu do ADT
 *  \details Vkládá hodnotu elementu do ADT.
 *  \param[in,out] aT Ukazatel na existující ADT
 *  \param[in] aValue Hodnota elementu vkládaná do ADT
 *  \return \c true pokud byla hodnota do ADT úspěšně vložena
 */
#define insert(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TSTACK_H)								\
			(											\
			,struct TStack*:				stack_push	\
			)											\
		IF_DEF(TQUEUE_H)								\
			(											\
			,struct TQueue*:				queue_push	\
			)											\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_insert	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TSET_H)
/** \brief Odstranění elementu z ADT
 *  \details Odstraní hodnotu elementu z ADT.
 *  \param[in,out] aT Ukazatel na existující ADT
 *  \param[in] aValue Hodnota elementu odebíraného z ADT
 *  \return \c true pokud byla hodnota z ADT úspěšně odstraněna
 */
#define erase(aT, ...)									\
	_Generic((aT)										\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_erase	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TSET_H)
/** \brief Zjištění, zda ADT obsahuje zadanou hodnotu elementu
 *  \details Funkce (predikát) vracející \c bool hodnotu reprezentující test, zda ADT obsahuje zadanou hodnotu elementu.
 *  \param[in] aT Ukazatel na existující ADT
 *  \param[in] aValue Hodnota elementu hledaná v ADT
 *  \return \c true pokud byl element se zadanou hodnotou v ADT nalezen
 */
#define is_element_of(aT, ...)
	_Generic((aT)												\
		IF_DEF(TSET_H)											\
			(													\
			,struct TSet*:					set_is_element_of	\
			,const struct TSet *aSet:		set_is_element_of	\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TSET_H)
/** \brief Získání nového iterátoru ukazujícího na první element se zadanou hodnotou v ADT, pokud byl nalezen
 *  \details Funkce vracející nový iterátor směřující na první nalezený element se zadanou hodnotou, pokud nebyl element v ADT nalezen vrací neplatný iterátor.
 *  \param[in] aT Ukazatel na existující ADT
 *  \param[in] aValue Hodnota elementu hledaná v ADT
 *  \return Nový iterátor asociovaný s ADT \p aT směřující na první nalezený element se zadanou hodnotou, nebo neplatný iterátor
 */
#define find(aT, ...)
	_Generic((aT)										\
		IF_DEF(TSET_H)									\
			(											\
			,struct TSet*:					set_find	\
			,const struct TSet *aSet:		set_find	\
			)											\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

/** \brief Deinicializace a dealokace vnitřní částí ADT
 *  \details Dealokace vnitřní dynamicky alokované paměti, deinicializace ADT.
 *  \param[in,out] aT Ukazatel na existující ADT
 */
#define destroy(aT)											\
	_Generic((aT)											\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVector*:				vector_destroy	\
			)												\
		IF_DEF(TSTACK_H)									\
			(												\
			,struct TStack*:				stack_destroy	\
			)												\
		IF_DEF(TQUEUE_H)									\
			(												\
			,struct TQueue*:				queue_destroy	\
			)												\
		IF_DEF(TSET_H)										\
			(												\
			,struct TSet*:					set_destroy		\
			)												\
	)(aT)


// Implementation of the Type Generic ADT Iterators API macros

/** \brief Vytvoření nového iterátoru ukazujícího na první element ADT
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný ADT a ukazuje na jeho první element.
 *  \param[in] aT Ukazatel na existující ADT
 *  \return Nový iterátor asociovaný s ADT \p aT ukazující na jeho první element
 */
#define begin(aT)													\
	_Generic((aT)													\
		IF_DEF(TVECTOR_H)											\
			(														\
			,struct TVector*:				vector_iterator_begin	\
			,const struct TVector*:			vector_iterator_begin	\
			)														\
		IF_DEF(TSTACK_H)											\
			(														\
			,struct TStack*:				stack_iterator_begin	\
			,const struct TStack*:			stack_iterator_begin	\
			)														\
		IF_DEF(TQUEUE_H)											\
			(														\
			,struct TQueue*:				queue_iterator_begin	\
			,const struct TQueue*:			queue_iterator_begin	\
			)														\
		IF_DEF(TSET_H)												\
			(														\
			,struct TSet*:					set_iterator_begin		\
			,const struct TSet*:			set_iterator_begin		\
			)														\
	)(aT)

#if defined(TVECTOR_H)
/** \brief Vytvoření nového iterátoru ukazujícího na zadanou pozici v ADT
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný ADT a ukazuje na element na zadané pozici.
 *  \param[in] aT Ukazatel na existující ADT
 *  \param[in] aPos Zadaná pozice
 *  \return Nový iterátor asociovaný s ADT \p aT ukazující na element na zadané pozici \p aPos
 */
#define pos(aT, ...)											\
	_Generic((aT)												\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVector*:				vector_iterator_pos	\
			,const struct TVector*:			vector_iterator_pos	\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)
#endif

#if defined(TVECTOR_H)
/** \brief Vytvoření nového iterátoru ukazujícího na poslední element v ADT
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný ADT a ukazuje na jeho poslední element.
 *  \param[in] aT Ukazatel na existující ADT
 *  \return Nový iterátor asociovaný s ADT \p aT ukazující na poslední element ADT
 */
#define last(aT)													\
	_Generic((aT)													\
		IF_DEF(TVECTOR_H)											\
			(														\
			,struct TVector*:				vector_iterator_last	\
			,const struct TVector*:			vector_iterator_last	\
			)														\
	)(aT)
#endif

/** \brief Zjištění platnosti iterátoru
 *  \details Funkce (predikát) vracející \c bool hodnotu definující platnost iterátoru.
 *  \param[in] aT Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje na platné místo v asociovaném ADT
 */
#define is_valid(aT)													\
	_Generic((aT)														\
		IF_DEF(TVECTOR_H)												\
			(															\
			,struct TVectorIterator*:		vector_iterator_is_valid	\
			,const struct TVectorIterator*:	vector_iterator_is_valid	\
			)															\
		IF_DEF(TSTACK_H)												\
			(															\
			,struct TStackIterator*:		stack_iterator_is_valid		\
			,const struct TStackIterator*:	stack_iterator_is_valid		\
			)															\
		IF_DEF(TQUEUE_H)												\
			(															\
			,struct TQueueIterator*:		queue_iterator_is_valid		\
			,const struct TQueueIterator*:	queue_iterator_is_valid		\
			)															\
		IF_DEF(TSET_H)													\
			(															\
			,struct TSetIterator*:			set_iterator_is_valid		\
			,const struct TSetIterator*:	set_iterator_is_valid		\
			)															\
	)(aT)

/** \brief Posunutí iterátoru vpřed
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vpřed (tj. na následující element v asociovaném ADT).
 *  \param[in,out] aT Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném ADT
 */
#define to_next(aT)													\
	_Generic((aT)													\
		IF_DEF(TVECTOR_H)											\
			(														\
			,struct TVectorIterator*:		vector_iterator_to_next	\
			)														\
		IF_DEF(TSTACK_H)											\
			(														\
			,struct TStackIterator*:		stack_iterator_to_next	\
			)														\
		IF_DEF(TQUEUE_H)											\
			(														\
			,struct TQueueIterator*:		queue_iterator_to_next	\
			)														\
		IF_DEF(TSET_H)												\
			(														\
			,struct TSetIterator*:			set_iterator_to_next	\
			)														\
	)(aT)

#if defined(TVECTOR_H)
/** \brief Posunutí iterátoru vzad
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vzad (tj. na předchozí element v asociovaném ADT).
 *  \param[in,out] aT Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném ADT
 */
#define to_prev(aT)													\
	_Generic((aT)													\
		IF_DEF(TVECTOR_H)											\
			(														\
			,struct TVectorIterator*:		vector_iterator_to_prev	\
			)														\
	)(aT)
#endif

/** \brief Test shodnosti dvou iterátorů.
 *  \details Vzájemně porovná hodnotu dvou iterátorů. Oba iterátory musí vzniknout ze stejné instance ADT.
 *  \param[in] aT Levý iterátor
 *  \param[in] aR Pravý iterátor
 *  \return \c true pokud oba iterátory odkazují na element na stejné pozici a ve stejném instanci ADT, nebo pokud jsou oba iterátory neplatné
 */
#define is_equal(aT, ...)												\
	_Generic((aT)														\
		/*																\
		IF_DEF(TVECTOR_H)												\
			(															\
			,struct TVectorIterator:		vector_iterator_is_equal	\
			)															\
		IF_DEF(TSTACK_H)												\
			(															\
			,struct TStackIterator:			stack_iterator_is_equal		\
			)															\
		IF_DEF(TQUEUE_H)												\
			(															\
			,struct TQueueIterator:			queue_iterator_is_equal		\
			)															\
		*/																\
		IF_DEF(TSET_H)													\
			(															\
			,struct TQueueIterator:			set_iterator_is_equal		\
			)															\
	)(aT __VA_OPT__(,) __VA_ARGS__)


// Implementation of the Type Generic ADT Algorithms API macros

/** \brief Zavolání zvolené funkce na každý element ADT od pozice určené iterátorem až do posledního elementu ADT
 *  \details Zavolá zadanou funkci \p aOperation na každý element ADT v rozsahu od pozice určené iterátorem až do posledního elementu ADT včetně.
 *  \param[in] aT Ukazatel na existující iterátor
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 */
#define for_each(aT, ...)									\
	_Generic((aT)											\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVectorIterator:		vector_for_each	\
			)												\
		/*													\
		IF_DEF(TSTACK_H)									\
			(												\
			,struct TStackIterator:			stack_for_each	\
			)												\
		*/													\
		IF_DEF(TQUEUE_H)									\
			(												\
			,struct TQueueIterator:			queue_for_each	\
			)												\
		IF_DEF(TSET_H)										\
			(												\
			,struct TQueueIterator:			set_for_each	\
			)												\
	)(aT __VA_OPT__(,) __VA_ARGS__)

/** \brief Zavolání zvolené funkce na každý element ADT v zadaném rozsahu pozic určených dvěma iterátory
 *  \details Zavolá zadanou funkci \p aOperation na každý element ADT v rozsahu od pozice určené iterátorem až do elementu v zadaném rozsahu.
 *  \param[in] aT Ukazatel na existující iterátor definující počáteční element v rozsahu
 *  \param[in] aLT Ukazatel na existující iterátor definující poslední element v rozsahu
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 */
#define for_range(aT, ...)										\
	_Generic((aT)												\
		/*														\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVectorIterator:		vector_for_range	\
			)													\
		IF_DEF(TSTACK_H)										\
			(													\
			,struct TStackIterator:			stack_for_range		\
			)													\
		IF_DEF(TQUEUE_H)										\
			(													\
			,struct TQueueIterator:			queue_for_range		\
			)													\
		*/														\
		IF_DEF(TSET_H)											\
			(													\
			,struct TQueueIterator:			set_for_range		\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)

/** \brief Zavolání zvolené funkce na prvních N elementů ADT od pozice určené iterátorem
 *  \details Zavolá zadanou funkci \p aOperation na prvních \p aN elementů ADT od počáteční pozice určené iterátorem. Pokud má ADT méně než \p aN elementů, funkce se ukončí dříve a vrátí neplatný iterátor.
 *  \param[in] aT Ukazatel na existující iterátor
 *  \param[in] aN Hodnota udávající prvních N elementů ADT, na které se má zavolat funkce \p aOperation
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 *  \return Hodnota iterátoru ukazujícího za `aN`-tý element ADT, nebo neplatný iterátor pokud ADT nemá další elementy.
 */
#define for_each_n(aT, ...)										\
	_Generic((aT)												\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVectorIterator:		vector_for_each_n	\
			)													\
		/*														\
		IF_DEF(TSTACK_H)										\
			(													\
			,struct TStackIterator:			stack_for_each_n	\
			)													\
		IF_DEF(TQUEUE_H)										\
			(													\
			,struct TQueueIterator:			queue_for_each_n	\
			)													\
		*/														\
		IF_DEF(TSET_H)											\
			(													\
			,struct TSetIterator:			set_for_each_n		\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)

/** \brief Vyhledání prvního elementu ADT splňujícího zadaný predikát
 *  \details Vyhledá první element ADT splňující zadaný predikát \p aPredicate. Vyhledávání probíhá od elementu určeného iterátorem \p aT, až do konce ADT.
 *  \param[in] aT Ukazatel na existující iterátor, jenž je předem asociovaný se zvoleným ADT a který tak definuje počáteční element pro zvolenou operaci
 *  \param[in] aPredicate Ukazatel na predikátovou funkci (funkci vracející \c bool a mající jeden parametr typu ukazatel na iterátor)
 *  \return Hodnota iterátoru ukazujícího na první nalezený element ADT splňující zadaný predikát \p aPredicate, nebo neplatný iterátor, pokud nebyl nalezen žádný vhodný element.
 */
#define find_if(aT, ...)									\
	_Generic((aT)											\
		/*													\
		IF_DEF(TVECTOR_H)									\
			(												\
			,struct TVectorIterator:		vector_find_if	\
			)												\
		IF_DEF(TSTACK_H)									\
			(												\
			,struct TStackIterator:			stack_find_if	\
			)												\
		*/													\
		IF_DEF(TQUEUE_H)									\
			(												\
			,struct TQueueIterator:			queue_find_if	\
			)												\
		IF_DEF(TSET_H)										\
			(												\
			,struct TSetIterator:			set_find_if		\
			)												\
	)(aT __VA_OPT__(,) __VA_ARGS__)

/** \brief Vyhledání prvního elementu ADT nesplňujícího zadaný predikát
 *  \details Vyhledá první element ADT nesplňující zadaný predikát \p aPredicate. Vyhledávání probíhá od elementu určeného iterátorem \p aIter, až do konce ADT.
 *  \param[in] aIter Ukazatel na existující iterátor, jenž je předem asociovaný se zvoleným ADT a který tak definuje počáteční element pro zvolenou operaci
 *  \param[in] aPredicate Ukazatel na predikátovou funkci (funkci vracející \c bool a mající jeden parametr typu ukazatel na iterátor)
 *  \return Hodnota iterátoru ukazujícího na první nalezený element ADT nesplňující zadaný predikát \p aPredicate, nebo neplatný iterátor, pokud nebyl nalezen žádný vhodný element.
 */
#define find_if_not(aT, ...)									\
	_Generic((aT)												\
		/*														\
		IF_DEF(TVECTOR_H)										\
			(													\
			,struct TVectorIterator:		vector_find_if_not	\
			)													\
		IF_DEF(TSTACK_H)										\
			(													\
			,struct TStackIterator:			stack_find_if_not	\
			)													\
		*/														\
		IF_DEF(TQUEUE_H)										\
			(													\
			,struct TQueueIterator:			queue_find_if_not	\
			)													\
		IF_DEF(TSET_H)											\
			(													\
			,struct TSetIterator:			set_find_if_not		\
			)													\
	)(aT __VA_OPT__(,) __VA_ARGS__)

#endif /* TGADT_H */
