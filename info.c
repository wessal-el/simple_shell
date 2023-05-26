/*
 * File: info.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * clr_inf - initializes struct
 * @inf: struct address
 */
void clr_inf(info *inf)
{
	inf->str = NULL;
	inf->av = NULL;
	inf->p = NULL;
	inf->ac = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @av: argument vector
 */
void set_inf(info *inf, char **av)
{
	int j = 0;

	inf->name = av[0];
	if (inf->str)
	{
		inf->av = str_tow(inf->str, " \t");
		if (!inf->av)
		{
			inf->av = malloc(sizeof(char *) * 2);
			if (inf->av)
			{
				inf->av[0] = str_dup(inf->str);
				inf->av[1] = NULL;
			}
		}
		for (j = 0; inf->av && inf->av[j]; j++)
			;
		inf->ac = j;
		rep_als(inf);
		rep_var(inf);
	}
}

/**
 * freeinf - frees struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void freeinf(info *inf, int al)
{
	f_free(inf->av);
	inf->av = NULL;
	inf->p = NULL;
	if (al)
	{
		if (!inf->cmdbuf)
			free(inf->str);
		if (inf->envt)
			freel(&(inf->envt));
		if (inf->hist)
			freel(&(inf->hist));
		if (inf->als)
			freel(&(inf->als));
		f_free(inf->envir);
			inf->envir = NULL;
		_free((void **)inf->cmdbuf);
		if (inf->rfd > 2)
			close(inf->rfd);
		put_char(FLUSH_BUFF);
	}
}
