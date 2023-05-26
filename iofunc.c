/*
 * File: iofunc.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * gethist - gets history file
 * @inf: parameter struct
 * Return: allocated string containg hist file
 */
char *gethist(info *inf)
{
	char *buff, *d;

	d = mgetenv(inf, "HOME=");
	if (!d)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(d) + str_len(FILE_HIS) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, d);
	str_cat(buff, "/");
	str_cat(buff, FILE_HIS);
	return (buff);
}

/**
 * whist - creates file or appends to existing file
 * @inf: parameter struct
 * Return: 1 on success, else -1
 */
int whist(info *inf)
{
	ssize_t f;
	char *name = gethist(inf);
	list *nd = NULL;

	if (!name)
		return (-1);
	f = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (f == -1)
		return (-1);
	for (nd = inf->hist; nd; nd = nd->nxt)
	{
		puts_fd(nd->s, f);
		put_fd('\n', f);
	}
	put_fd(FLUSH_BUFF, f);
	close(f);
	return (1);
}

/**
 * rhist - reads history from file
 * @inf: parameter struct
 * Return: history count on success, 0 otherwise
 */
int rhist(info *inf)
{
	int j, l = 0, lcount = 0;
	ssize_t f, len, size = 0;
	struct stat st;
	char *buff = NULL, *name = gethist(inf);

	if (!name)
		return (0);
	f = open(name, O_RDONLY);
	free(name);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (0);
	len = read(f, buff, size);
	buff[size] = 0;
	if (len <= 0)
		return (free(buff), 0);
	close(f);
	for (j = 0; j < size; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			buildhist(inf, buff + l, lcount++);
			l = j + 1;
		}
	if (l != j)
		buildhist(inf, buff + l, lcount++);
	free(buff);
	inf->counthist = lcount;
	while (inf->counthist-- >= MAX_HIS)
		del_node(&(inf->hist), 0);
	renumhist(inf);
	return (inf->counthist);
}

/**
 * buildhist - adds entry to history linked list
 * @inf: Structure containing potential arguments
 * @buff: buffer
 * @lcount: history linecount, counthist
 * Return: Always 0
 */
int buildhist(info *inf, char *buff, int lcount)
{
	list *nd = NULL;

	if (inf->hist)
		nd = inf->hist;
	addnodeend(&nd, buff, lcount);
	if (!inf->hist)
		inf->hist = nd;
	return (0);
}

/**
 * renumhist - renumbers history linked list after changes
 * @inf: Structure containing potential arguments
 * Return: new counthist
 */
int renumhist(info *inf)
{
	list *nd = inf->hist;
	int j = 0;

	while (nd)
	{
		nd->n = j++;
		nd = nd->nxt;
	}
	return (inf->counthist = j);
}
