/** \file fibonacci.c
 *  \brief Definice rùzných variant implementace výpoètu hodnot Fibonacciho posloupnosti
 *  \author Petyovský
 *  \version 2026
 *  $Id: fibonacci.c 3307 2026-03-30 14:12:07Z petyovsky $
 */

#include "fibonacci.h"

 //-----------------------------------------------------------------------
 // Implementace stromovou rekurzí
unsigned fibonacci1(unsigned n)
{
	if(n < 2)
		return n;
	return fibonacci1(n-1) + fibonacci1(n-2);
}

//-----------------------------------------------------------------------
// Implementace iterací
unsigned fibonacci2(unsigned n)
{
	if(n < 2)
		return n;
	unsigned fibN1 = 1;
	unsigned fibN2 = 0;
	for(unsigned i = 2; i <= n; ++i)
	{
		unsigned fibCurr = fibN1 + fibN2;
		fibN2 = fibN1;
		fibN1 = fibCurr;
	}
	return fibN1;
}

//-----------------------------------------------------------------------
// Implementace stromovou rekurzí s memoizací
struct TMemoizer m_fibonacci3 = { 0, };	// Instance memoizeru pro funkci fibonacci3()

unsigned fibonacci3(unsigned n)
{
	if(n < 2)
		return n;
	return memoizer_eval(&m_fibonacci3, n-1) + memoizer_eval(&m_fibonacci3, n-2);
}

unsigned fibonacci3_wrapper(unsigned n)
{
	return memoizer_eval(&m_fibonacci3, n);
}

//-----------------------------------------------------------------------
// Implementace s koncovou rekurzí
/** \brief Vnitøní, lokální pracovní funkce realizující koncovou rekurzi
 */
[[nodiscard]] static unsigned fibonacci4_worker(unsigned n, unsigned fib_n_1, unsigned fib_n_2)
{
	if(n == 0)
		return fib_n_2;  // F(0) = 0
	if(n == 1)
		return fib_n_1;  // F(1) = 1

	// Poslední operace je VOLÁNÍ SEBE SAMA ? Tail call!
	return fibonacci4_worker(n - 1, fib_n_1 + fib_n_2, fib_n_1);
}

unsigned fibonacci4(unsigned n)
{
	return fibonacci4_worker(n, 1, 0);
}
