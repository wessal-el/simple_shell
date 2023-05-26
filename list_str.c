/*
 * File: list_str.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * listlen - determines len of linked list
 * @f: pointer to first node
 * Return: size of list
 */
size_t listlen(const list *f)
{
	size_t j = 0;

	while (f)
	{
		f = f->nxt;
		j++;
	}
	return (j);
}

/**
 * liststr - returns array of strings of the list->s
 * @h: pointer to first node
 * Return: array of strings
 */
char **liststr(list *h)
{
	list *nd = h;
	size_t j = listlen(h), i;
	char **str;
	char *strs;

	if (!h || !j)
		return (NULL);
	str = malloc(sizeof(char *) * (j + 1));
	if (!str)
		return (NULL);
	for (j = 0; nd; nd = nd->nxt, j++)
	{
		strs = malloc(str_len(nd->s) + 1);
		if (!strs)
		{
			for (i = 0; i < j; i++)
				free(str[i]);
			free(str);
			return (NULL);
		}
		strs = str_cpy(strs, nd->s);
		str[j] = strs;
	}
	str[j] = NULL;
	return (str);
}

/**
 * printl - prints all elements of a list linked list
 * @f: pointer to first node
 * Return: size of list
 */
size_t printl(const list *f)
{
	size_t j = 0;

	while (f)
	{
		_put(conv_num(f->n, 10, 0));
		put_char(':');
		put_char(' ');
		_put(f->s ? f->s : "(nil)");
		_put("\n");
		f = f->nxt;
		j++;
	}
	return (j);
}

/**
 * node_start - returns node whose str starts with prefix
 * @nd: pointer to list head
 * @pref: string to match
 * @s: the next character after prefix
 * Return: match node or null
 */
list *node_start(list *nd, char *pref, char s)
{
	char *i = NULL;

	while (nd)
	{
		i = swith(nd->s, pref);
		if (i && ((s == -1) || (*i == s)))
			return (nd);
		nd = nd->nxt;
	}
	return (NULL);
}

/**
 * get_index - gets index of node
 * @h: pointer to list head
 * @nd: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_index(list *h, list *nd)
{
	size_t j = 0;

	while (h)
	{
		if (h == nd)
			return (j);
		h = h->nxt;
		j++;
	}
	return (-1);
}
