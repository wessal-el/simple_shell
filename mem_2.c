/*
 * File: mem_2.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * _free - frees pointer and NULLs the address
 * @p: address of pointer to free
 * Return: 1 if freed, otherwise 0
 */
int _free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
