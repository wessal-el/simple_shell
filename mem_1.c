/*
 * File: mem_1.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * mem_set - fills memory with constant byte
 * @c: pointer to the memory area
 * @a: byte to fill *s with
 * @i: amount of bytes to be filled
 * Return: (c) a pointer to the memory area s
 */
char *mem_set(char *c, char a, unsigned int i)
{
	unsigned int n;

	for (n = 0; n < i; n++)
		c[n] = a;
	return (c);
}

/**
 * f_free - frees string of strings
 * @p: string of strings
 */
void f_free(char **p)
{
	char **i = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(i);
}

/**
 * __realloc - reallocates block of memory
 * @p: pointer to previous malloc block
 * @old: byte size of prev block
 * @new: byte size of new block
 * Return: pointer
 */
void *__realloc(void *p, unsigned int old, unsigned int new)
{
	char *i;

	if (!p)
		return (malloc(new));
	if (!new)
		return (free(p), NULL);
	if (new == old)
		return (p);
	i = malloc(new);
	if (!i)
		return (NULL);
	old = old < new ? old : new;
	while (old--)
		i[old] = ((char *)p)[old];
	free(p);
	return (i);
}
