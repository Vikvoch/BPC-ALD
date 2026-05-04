/** \file wildcard_match.c
 *  \brief Definice funkce wildcard_match() realizující test na shodu øetìzcù z nichž jeden obsahuje žolíkové znaky
 *  \author Petyovský
 *  \version 2026
 *  $Id: wildcard_match.c 3307 2026-03-30 14:12:07Z petyovsky $
 */
#include "wildcard_match.h"
#include <stdio.h>

bool wildcard_match(const char aWildCardStr[], const char aStr[])
{
	if(*aWildCardStr == '\0' && *aStr == '\0') // obì jsou prázdné
		return true;
	if(*aWildCardStr == '*') // je tam *
	{
		return wildcard_match(aWildCardStr + 1, aStr) || (*aStr != '\0' && wildcard_match(aWildCardStr, aStr + 1));
	}
	if(*aWildCardStr == *aStr || (*aWildCardStr == '?' && *aStr != '\0')) // není tam * -> shodné / je ?(=neøeším znak pokud tam ještì je)
	{
		return wildcard_match(aWildCardStr + 1, aStr + 1); // jdu na další
	}
	return false;
}
