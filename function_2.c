/*
 * File: function_2.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * str_ncpy - copies a string
 * @d: destination string to be copied to
 * @s: source string
 * @i: amount of characters to be copied
 * Return: concatenated string
 */
char *str_ncpy(char *d, char *s, int i)
{
	int j, k;
	char *c = d;

	j = 0;
	while (s[j] != '\0' && j < i - 1)
	{
		d[j] = s[j];
		j++;
	}
	if (j < i)
	{
		k = j;
		while (k < i)
		{
			d[k] = '\0';
			k++;
		}
	}
	return (c);
}

/**
 * str_ncat - concatenates 2 strings
 * @d: first string
 * @s: second string
 * @i: amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *str_ncat(char *d, char *s, int i)
{
	int k = 0, j = 0;
	char *c = d;

	while (d[j] != '\0')
		j++;
	while (s[k] != '\0' && k < i)
	{
		d[j] = s[k];
		j++;
		k++;
	}
	if (k < i)
		d[j] = '\0';
	return (c);
}

/**
 * str_chr - locates a character in a string
 * @c: string to be parsed
 * @s: character to look for
 * Return: (c) a pointer to the memory area s
 */
char *str_chr(char *c, char s)
{
	do {
		if (*c == s)
			return (c);
	} while (*c++ != '\0');
	return (NULL);
}
