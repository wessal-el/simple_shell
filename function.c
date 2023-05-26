/*
 * File: function.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * str_len - returns length of string
 * @c: string whose length to check
 * Return: int len of string
 */
int str_len(char *c)
{
	int j = 0;

	if (!c)
		return (0);
	while (*c++)
		j++;
	return (j);
}

/**
 * str_cmp - performs lexicogarphic comparison of 2 strings
 * @s_1: first string
 * @s_2: second string
 * Return: neg if s_1 < s_2, pos if s_1 > s_2, 0 if s_1 == s_2
 */
int str_cmp(char *s_1, char *s_2)
{
	while (*s_1 && *s_2)
	{
		if (*s_1 != *s_2)
			return (*s_1 - *s_2);
		s_1++;
		s_2++;
	}
	if (*s_1 == *s_2)
		return (0);
	else
		return (*s_1 < *s_2 ? -1 : 1);
}

/**
 * swith - Checks if needle starts with haystack
 * @hstack: string to search
 * @ndle: substring to find
 * Return: address of nxt char of haystack or NULL
 */
char *swith(const char *hstack, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * str_cat - Concatenates two strings
 * @d: destination buffer
 * @s: source buffer
 * Return: pointer to dest buffer
 */
char *str_cat(char *d, char *s)
{
	char *r = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (r);
}
