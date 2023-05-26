/*
 * File: getline.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * bufinput - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @l: address of len var
 * Return: bytes read
 */
ssize_t bufinput(info *inf, char **buff, size_t *l)
{
	ssize_t i = 0;
	size_t len = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, Handler);

#if USE_GETLINE
		i = getline(buff, &len, stdin);
#else
		i = mgetline(inf, buff, &len);
#endif
		if (i > 0)
		{
			if ((*buff)[i - 1] == '\n')
			{
				(*buff)[i - 1] = '\0';
				i--;
			}
			inf->lflag = 1;
			rmcomnt(*buff);
			buildhist(inf, *buff, inf->counthist++);
			{
				*l = i;
				inf->cmdbuf = buff;
			}
		}
	}
	return (i);
}

/**
 * get_inpt - gets line minus newline
 * @inf: parameter struct
 * Return: bytes read
 */
ssize_t get_inpt(info *inf)
{
	static char *buff;
	static size_t a, b, l;
	ssize_t i = 0;
	char **buf = &(inf->str), *j;

	put_char(FLUSH_BUFF);
	i = bufinput(inf, &buff, &l);
	if (i == -1)
		return (-1);
	if (l)
	{
		b = a;
		j = buff + a;
		check(inf, buff, &b, a, l);
		while (b < l)
		{
			if (ischain(inf, buff, &b))
				break;
			b++;
		}
		a = b + 1;
		if (a >= l)
		{
			a = l = 0;
			inf->buftype = _NORM;
		}
		*buf = j;
		return (str_len(j));
	}
	*buf = buff;
	return (i);
}

/**
 * rbuf - reads buffer
 * @inf: parameter struct
 * @buff: buffer
 * @a: size
 * Return: i
 */
ssize_t rbuf(info *inf, char *buff, size_t *a)
{
	ssize_t i = 0;

	if (*a)
		return (0);
	i = read(inf->rfd, buff, RBUFF_SIZE);
	if (i >= 0)
		*a = i;
	return (i);
}

/**
 * mgetline - gets the next line of input
 * @inf: parameter struct
 * @p: address of pointer to buff, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 * Return: c
 */
int mgetline(info *inf, char **p, size_t *len)
{
	static char buff[RBUFF_SIZE];
	static size_t j, l;
	size_t i;
	ssize_t s = 0, c = 0;
	char *a = NULL, *new = NULL, *b;

	a = *p;
	if (a && len)
		c = *len;
	if (j == l)
		j = l = 0;
	s = rbuf(inf, buff, &l);
	if (s == -1 || (s == 0 && l == 0))
		return (-1);
	b = str_chr(buff + j, '\n');
	i = b ? 1 + (unsigned int)(b - buff) : l;
	new = __realloc(a, c, c ? c + i : i + 1);
	if (!new)
		return (a ? free(a), -1 : -1);
	if (c)
		str_ncat(new, buff + j, i - j);
	else
		str_ncpy(new, buff + j, i - j + 1);
	c += i - j;
	j = i;
	a = new;
	if (len)
		*len = c;
	*p = a;
	return (c);
}

/**
 * Handler - blocks ctrl-C
 * @sig: signal number
 */
void Handler(__attribute__((unused))int sig)
{
	_put("\n");
	_put("$ ");
	put_char(FLUSH_BUFF);
}
