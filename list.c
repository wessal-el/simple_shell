/*
 * File: list.c
 * Auth: wessal el hasnaui
 */

#include "shell.h"

/**
 * addnode - adds node to start of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @n: node index
 * Return: size of list
 */
list *addnode(list **h, const char *s, int n)
{
	list *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list));
	if (!new)
		return (NULL);
	mem_set((void *)new, 0, sizeof(list));
	new->n = n;
	if (s)
	{
		new->s = str_dup(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	new->nxt = *h;
	*h = new;
	return (new);
}

/**
 * addnodeend - adds node to the end of list
 * @h: address of pointer to head
 * @s: str field of node
 * @n: node index
 * Return: size of list
 */
list *addnodeend(list **h, const char *s, int n)
{
	list *new, *nd;

	if (!h)
		return (NULL);
	nd = *h;
	new = malloc(sizeof(list));
	if (!new)
		return (NULL);
	mem_set((void *)new, 0, sizeof(list));
	new->n = n;
	if (s)
	{
		new->s = str_dup(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->nxt)
			nd = nd->nxt;
		nd->nxt = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * printl_str - prints only str element of a list linked list
 * @f: pointer to first node
 * Return: size of list
 */
size_t printl_str(const list *f)
{
	size_t j = 0;

	while (f)
	{
		_put(f->s ? f->s : "(nil)");
		_put("\n");
		f = f->nxt;
		j++;
	}
	return (j);
}

/**
 * del_node - deletes node at given index
 * @h: address of pointer to first node
 * @i: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int del_node(list **h, unsigned int i)
{
	list *nd, *prev;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);
	if (!i)
	{
		nd = *h;
		*h = (*h)->nxt;
		free(nd->s);
		free(nd);
		return (1);
	}
	nd = *h;
	while (nd)
	{
		if (j == i)
		{
			prev->nxt = nd->nxt;
			free(nd->s);
			free(nd);
			return (1);
		}
		j++;
		prev = nd;
		nd = nd->nxt;
	}
	return (0);
}

/**
 * freel - frees all nodes of a list
 * @head: address of pointer to head node
 */
void freel(list **head)
{
	list *nd, *next, *h;

	if (!head || !*head)
		return;
	h = *head;
	nd = h;
	while (nd)
	{
		next = nd->nxt;
		free(nd->s);
		free(nd);
		nd = next;
	}
	*head = NULL;
}
