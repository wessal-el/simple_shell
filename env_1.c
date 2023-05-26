/*
 * File:  env_1.c
 * Auth: wessal el hasnaoui
 */
#include "shell.h"

/**
 * menv - prints current environment
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */
int menv(info *inf)
{
	printl(inf->envt);
	return (0);
}

/**
 * mgetenv - gets value of environ variable
 * @inf: Structure containing potential arguments
 * @n: env var name
 * Return: value
 */
char *mgetenv(info *inf, const char *n)
{
	list *nd = inf->envt;
	char *i;

	while (nd)
	{
		i = swith(nd->s, n);
		if (i && *i)
			return (i);
		nd = nd->nxt;
	}
	return (NULL);
}

/**
 * msetenv - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int msetenv(info *inf)
{
	if (inf->ac != 3)
	{
		_eput("incorrect number of arguements\n");
		return (1);
	}
	if (set_env(inf, inf->av[1], inf->av[2]))
		return (0);
	return (1);
}

/**
 * munsetenv - Remove environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int munsetenv(info *inf)
{
	int j;

	if (inf->ac == 1)
	{
		_eput("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->ac; j++)
		unset_env(inf, inf->av[j]);
	return (0);
}

/**
 * pop_env - populates env linked list
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */
int pop_env(info *inf)
{
	list *nd = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		addnodeend(&nd, environ[j], 0);
	inf->envt = nd;
	return (0);
}
