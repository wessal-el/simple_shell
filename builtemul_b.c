/*
 * File: builtemul_b.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * mhist - displays history list
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int mhist(info *inf)
{
	printl(inf->hist);
	return (0);
}

/**
 * unsetals - sets alias to str
 * @inf: parameter struct
 * @s: the string alias
 * Return: 0 on success, 1 on error
 */
int unsetals(info *inf, char *s)
{
	char *j, i;
	int r;

	j = str_chr(s, '=');
	if (!j)
		return (1);
	i = *j;
	*j = 0;
	r = del_node(&(inf->als),
		get_index(inf->als, node_start(inf->als, s, -1)));
	*j = i;
	return (r);
}

/**
 * setals - sets alias to str
 * @inf: parameter struct
 * @s: string alias
 * Return: 0 on success, 1 on error
 */
int setals(info *inf, char *s)
{
	char *j;

	j = str_chr(s, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (unsetals(inf, s));
	unsetals(inf, s);
	return (addnodeend(&(inf->als), s, 0) == NULL);
}

/**
 * printals - prints alias string
 * @nd: alias node
 * Return: 0 on success, 1 on error
 */
int printals(list *nd)
{
	char *j = NULL, *i = NULL;

	if (nd)
	{
		j = str_chr(nd->s, '=');
		for (i = nd->s; i <= j; i++)
			put_char(*i);
		put_char('\'');
		_put(j + 1);
		_put("'\n");
		return (0);
	}
	return (1);
}

/**
 * malias - mimics alias builtin
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int malias(info *inf)
{
	int x = 0;
	char *j = NULL;
	list *nd = NULL;

	if (inf->ac == 1)
	{
		nd = inf->als;
		while (nd)
		{
			printals(nd);
			nd = nd->nxt;
		}
		return (0);
	}
	for (x = 1; inf->av[x]; x++)
	{
		j = str_chr(inf->av[x], '=');
		if (j)
			setals(inf, inf->av[x]);
		else
			printals(node_start(inf->als, inf->av[x], '='));
	}
	return (0);
}
