/*
 * File: more.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * interac - returns true if shell is interactive mode
 * @inf: struct address
 * Return: 1 if interactive, 0 otherwise
 */
int interac(info *inf)
{
	return (isatty(STDIN_FILENO) && inf->rfd <= 2);
}

/**
 * is_del - checks if character is delimeter
 * @s: char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_del(char s, char *del)
{
	while (*del)
		if (*del++ == s)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic char
 * @s: character to input
 * Return: 1 if s is alphabetic, 0 otherwise
 */
int is_alpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * __atoi - converts string to integer
 * @c: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int __atoi(char *c)
{
	int j, sgn = 1, f = 0, outpt;
	unsigned int rslt = 0;

	for (j = 0;  c[j] != '\0' && f != 2; j++)
	{
		if (c[j] == '-')
			sgn *= -1;
		if (c[j] >= '0' && c[j] <= '9')
		{
			f = 1;
			rslt *= 10;
			rslt += (c[j] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (sgn == -1)
		outpt = -rslt;
	else
		outpt = rslt;
	return (outpt);
}
