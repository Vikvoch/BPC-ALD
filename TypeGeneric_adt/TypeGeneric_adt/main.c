/** \file main.c
 *  \brief Hlavní program společně testující API jednotlivých ADT
 *  \author Petyovský
 *  \version 2026
 *  $Id: main.c 2914 2025-02-06 10:06:10Z petyovsky $
 */

#include <stdio.h>

int main_tg_vector(int argc, char *argv[]);
int main_tg_stack(int argc, char *argv[]);
int main_tg_queue(int argc, char *argv[]);

int main(int argc, char *argv[])
	{
	puts("\n************** main_tg_vector **************\n");
	int err = main_tg_vector(argc, argv);
	if(err)
		return err;

	puts("\n************** main_tg_stack ***************\n");
	err = main_tg_stack(argc, argv);
	if(err)
		return err;

	puts("\n************** main_tg_queue ***************\n");
	err = main_tg_queue(argc, argv);
	if(err)
		return err;

	return 0;
	}
