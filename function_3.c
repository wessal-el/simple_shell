/*
 * File: function_3.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * str_tow - splits a string into words
 * @s: input string
 * @d: delimeter string
 * Return: pointer to array of strings, or NULL on failure
 */
char **str_tow(char *s, char *d)
{
	int i, j, k, n, words = 0;
	char **c;

	if (s  == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; s[k] != '\0'; k++)
		if (!is_del(s[k], d) && (is_del(s[k + 1], d)
					|| !s[k + 1]))
			words++;
	if (words == 0)
		return (NULL);
	c = malloc((1 + words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (k = 0, i = 0; i < words; i++)
	{
		while (is_del(s[k], d))
			k++;
		j = 0;
		while (!is_del(s[k + j], d) && s[k + j])
			j++;
		c[i] = malloc((j + 1) * sizeof(char));
		if (!c[i])
		{
			for (j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return (NULL);
		}
		for (n = 0; n < j; n++)
			c[i][n] = s[k++];
		c[i][n] = 0;
	}
	c[i] = NULL;
	return (c);
}

/**
 * str__tow - splits string into words
 * @s: input string
 * @d: delimeter
 * Return: pointer to array of strings, or NULL on failure
 */
char **str__tow(char *s, char d)
{
	int i, j, k, n, words = 0;
	char **c;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (k = 0; s[k] != '\0'; k++)
		if ((s[k] != d && s[k + 1] == d) ||
		    (s[k] != d && !s[k + 1]) || s[k + 1] == d)
			words++;
	if (words == 0)
		return (NULL);
	c = malloc((1 + words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (k = 0, i = 0; i < words; i++)
	{
		while (s[j] == d && s[k] != d)
			j++;
		j = 0;
		while (s[k + j] != d && s[k + j] && s[k + j] != d)
			j++;
		c[i] = malloc((j + 1) * sizeof(char));
		if (!c[i])
		{
			for (j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return (NULL);
		}
		for (n = 0; n < j; n++)
			c[i][n] = s[k++];
		c[i][n] = 0;
	}
	c[i] = NULL;
	return (c);
}
