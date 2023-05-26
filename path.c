/*
 * File: path.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * iscmd - determines if file is executable command
 * @inf: info struct
 * @p: path to the file
 * Return: 1 if true, 0 otherwise
 */
int iscmd(info *inf, char *p)
{
	struct stat st;
	(void)inf;

	if (!p || stat(p, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dupchar - duplicates char
 * @path: PATH string
 * @strt: starting index
 * @stp: stopping index
 * Return: pointer to new buffer
 */
char *dupchar(char *path, int strt, int stp)
{
	static char buff[1024];
	int j = 0, i = 0;

	for (i = 0, j = strt; j < stp; j++)
		if (path[j] != ':')
			buff[i++] = path[j];
	buff[i] = 0;
	return (buff);
}

/**
 * _path - finds cmd in PATH string
 * @inf: info struct
 * @path: PATH string
 * @c: cmd to find
 * Return: full path of cmd or NULL
 */
char *_path(info *inf, char *path, char *c)
{
	int j = 0, curr = 0;
	char *p;

	if (!path)
		return (NULL);
	if ((str_len(c) > 2) && swith(c, "./"))
	{
		if (iscmd(inf, c))
			return (c);
	}
	while (1)
	{
		if (!path[j] || path[j] == ':')
		{
			p = dupchar(path, curr, j);
			if (!*p)
				str_cat(p, c);
			else
			{
				str_cat(p, "/");
				str_cat(p, c);
			}
			if (iscmd(inf, p))
				return (p);
			if (!path[j])
				break;
			curr = j;
		}
		j++;
	}
	return (NULL);
}
