/*
 * File: moore.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * erratoi - converts string to integer
 * @c: string to be converted
 * Return: 0 if no num in str, converted num otherwise -1 on err
 */
int erratoi(char *c)
{
	int j = 0;
	unsigned long int rslt = 0;

	if (*c == '+')
		c++;
	for (j = 0;  c[j] != '\0'; j++)
	{
		if (c[j] >= '0' && c[j] <= '9')
		{
			rslt *= 10;
			rslt += (c[j] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * printerr - prints error message
 * @inf: parameter & return info struct
 * @es: string containing specified err type
 * Return: 0 if no num in str, converted num otherwise -1 on err
 */
void printerr(info *inf, char *es)
{
	_eput(inf->name);
	_eput(": ");
	printd(inf->lcount, STDERR_FILENO);
	_eput(": ");
	_eput(inf->av[0]);
	_eput(": ");
	_eput(es);
}

/**
 * printd - prints decimal (integer) number (base 10)
 * @inpt: input
 * @f: filedescriptor to write to
 * Return: number of char printed
 */
int printd(int inpt, int f)
{
	int (*_putchar)(char) = put_char;
	int j, c = 0;
	unsigned int _abs, curr;

	if (f == STDERR_FILENO)
		_putchar = eput_char;
	if (inpt < 0)
	{
		_abs = -inpt;
		_putchar('-');
		c++;
	}
	else
		_abs = inpt;
	curr = _abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs / j)
		{
			_putchar('0' + curr / j);
			c++;
		}
		curr %= j;
	}
	_putchar('0' + curr);
	c++;
	return (c);
}

/**
 * conv_num - converter funct, clone of itoa
 * @n: num
 * @b: base
 * @f: arg flags
 * Return: str
 */
char *conv_num(long int n, int b, int f)
{
	static char *a;
	static char buf[50];
	char sgn = 0;
	char *p;
	unsigned long i = n;

	if (!(f & _UNSIGNED) && n < 0)
	{
		i = -n;
		sgn = '-';
	}
	a = f & _LOWERCASE ? "0123456789abcdef"
		: "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';
	do {
		*--p = a[i % b];
		i /= b;
	} while (i != 0);
	if (sgn)
		*--p = sgn;
	return (p);
}

/**
 * rmcomnt - replaces first instance of '#' with '\0'
 * @buff: address of string to modify
 * Return: Always 0
 */
void rmcomnt(char *buff)
{
	int n;

	for (n = 0; buff[n] != '\0'; n++)
		if (buff[n] == '#' && (!n || buff[n - 1] == ' '))
		{
			buff[n] = '\0';
			break;
		}
}
