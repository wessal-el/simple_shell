/*
 * File: env_2.c
 * Auth: wessal el hasnaoui
 */
#include "shell.h"

/**
 * get_envir - returns string array copy of our environ
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */
char **get_envir(info *inf)
{
	if (!inf->envir || inf->chenv)
	{
		inf->envir = liststr(inf->envt);
		inf->chenv = 0;
	}
	return (inf->envir);
}

/**
 * unset_env - Remove environment variable
 * @inf: Structure containing potential arguments
 * @v: string env var property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env(info *inf, char *v)
{
	list *nd = inf->envt;
	size_t j = 0;
	char *i;

	if (!nd || !v)
		return (0);
	while (nd)
	{
		i = swith(nd->s, v);
		if (i && *i == '=')
		{
			inf->chenv = del_node(&(inf->envt), j);
			j = 0;
			nd = inf->envt;
			continue;
		}
		nd = nd->nxt;
		j++;
	}
	return (inf->chenv);
}

/**
 * set_env - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 * @v: string env var property
 * @val: string env var value
 * Return: Always 0
 */
int set_env(info *inf, char *v, char *val)
{
	char *buff = NULL;
	list *nd;
	char *i;

	if (!v || !val)
		return (0);
	buff = malloc(str_len(v) + str_len(val) + 2);
	if (!buff)
		return (1);
	str_cpy(buff, v);
	str_cat(buff, "=");
	str_cat(buff, val);
	nd = inf->envt;
	while (nd)
	{
		i = swith(nd->s, v);
		if (i && *i == '=')
		{
			free(nd->s);
			nd->s = buff;
			inf->chenv = 1;
			return (0);
		}
		nd = nd->nxt;
	}
	addnodeend(&(inf->envt), buff, 0);
	free(buff);
	inf->chenv = 1;
	return (0);
}
