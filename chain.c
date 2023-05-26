/*
 * File: chain.c
 * Auth: wessal el hasnaoui
 */
#include "shell.h"

/**
 * ischain - test if current char in buffer is chain delimeter
 * @inf: parameter struct
 * @buff: char buffer
 * @ad: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ischain(info *inf, char *buff, size_t *ad)
{
	size_t i = *ad;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		inf->buftype = _OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		inf->buftype = _AND;
	}
	else if (buff[i] == ';')
	{
		buff[i] = 0;
		inf->buftype = _CHAIN;
	}
	else
		return (0);
	*ad = i;
	return (1);
}

/**
 * check - checks we should continue chaining
 * @inf: parameter struct
 * @buff: char buffer
 * @ad: address of current position in buf
 * @j: starting position
 * @l: length of buf
 */
void check(info *inf, char *buff, size_t *ad, size_t j, size_t l)
{
	size_t i = *ad;

	if (inf->buftype == _AND)
	{
		if (inf->stts)
		{
			buff[j] = 0;
			i = l;
		}
	}
	if (inf->buftype == _OR)
	{
		if (!inf->stts)
		{
			buff[j] = 0;
			i = l;
		}
	}
	*ad = i;
}

/**
 * rep_als - replaces alias in tokenized string
 * @inf: parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int rep_als(info *inf)
{
	int j;
	list *nd;
	char *ad;

	for (j = 0; j < 10; j++)
	{
		nd = node_start(inf->als, inf->av[0], '=');
		if (!nd)
			return (0);
		free(inf->av[0]);
		ad = str_chr(nd->s, '=');
		if (!ad)
			return (0);
		ad = str_dup(ad + 1);
		if (!ad)
			return (0);
		inf->av[0] = ad;
	}
	return (1);
}

/**
 * rep_var - replaces var in tokenized string
 * @inf: parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int rep_var(info *inf)
{
	int j = 0;
	list *nd;

	for (j = 0; inf->av[j]; j++)
	{
		if (inf->av[j][0] != '$' || !inf->av[j][1])
			continue;
		if (!str_cmp(inf->av[j], "$?"))
		{
			rep_str(&(inf->av[j]),
				str_dup(conv_num(inf->stts, 10, 0)));
			continue;
		}
		if (!str_cmp(inf->av[j], "$$"))
		{
			rep_str(&(inf->av[j]),
				str_dup(conv_num(getpid(), 10, 0)));
			continue;
		}
		nd = node_start(inf->envt, &inf->av[j][1], '=');
		if (nd)
		{
			rep_str(&(inf->av[j]),
				str_dup(str_chr(nd->s, '=') + 1));
			continue;
		}
		rep_str(&inf->av[j], str_dup(""));
	}
	return (0);
}

/**
 * rep_str - replace string
 * @o: address of old string
 * @n: new string
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
