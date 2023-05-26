/*
 * File: function_1.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * str_cpy - copies string
 * @d: destination
 * @s: source
 * Return: pointer to dest
 */
char *str_cpy(char *d, char *s)
{
	int j = 0;

	if (d == s || s == 0)
		return (d);
	while (s[j])
	{
		d[j] = s[j];
		j++;
	}
	d[j] = 0;
	return (d);
}

/**
 * str_dup - duplicates string
 * @s: string to duplicate
 * Return: pointer to duplicated string
 */
char *str_dup(const char *s)
{
	int len = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--s;
	return (r);
}

/**
 *_put - prints input string
 *@s: string to be printed
 */
void _put(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		put_char(s[j]);
		j++;
	}
}

/**
 * put_char - writes character c to stdout
 * @s: character to print
 * Return: On success 1 On error, -1, errno set appropriately
 */
int put_char(char s)
{
	static int j;
	static char buff[WBUFF_SIZE];

	if (s == FLUSH_BUFF || j >= WBUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (s != FLUSH_BUFF)
		buff[j++] = s;
	return (1);
}
