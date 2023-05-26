/*
 * File: error_str.c
 * Auth: wessal el hasnaoui
 */
#include "shell.h"

/**
 *_eput - prints input string
 * @s: string to be printed
 */
void _eput(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		eput_char(s[j]);
		j++;
	}
}

/**
 * eput_char - writes character c to stderr
 * @c: character to print
 * Return: On success 1, On error, -1
 */
int eput_char(char c)
{
	static int j;
	static char buff[WBUFF_SIZE];

	if (c == FLUSH_BUFF || j >= WBUFF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != FLUSH_BUFF)
		buff[j++] = c;
	return (1);
}

/**
 * put_fd - writes character c to given fd
 * @s: character to print
 * @FD: The filedescriptor to write to
 * Return: On success 1 On error, -1
 */
int put_fd(char s, int FD)
{
	static int j;
	static char buff[WBUFF_SIZE];

	if (s == FLUSH_BUFF || j >= WBUFF_SIZE)
	{
		write(FD, buff, j);
		j = 0;
	}
	if (s != FLUSH_BUFF)
		buff[j++] = s;
	return (1);
}

/**
 * puts_fd - prints input string
 * @s: string to be printed
 * @FD: file descriptor to write to
 * Return: number of chars put
 */
int puts_fd(char *s, int FD)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
		j += put_fd(*s++, FD);
	return (j);
}
