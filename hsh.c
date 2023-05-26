/*
 * File: hsh.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * h - main shell loop
 * @inf: parameter & return info struct
 * @agv: argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int h(info *inf, char **agv)
{
	ssize_t i = 0;
	int builtin = 0;

	while (i != -1 && builtin != -2)
	{
		clr_inf(inf);
		if (interac(inf))
			_put("$ ");
		eput_char(FLUSH_BUFF);
		i = get_inpt(inf);
		if (i != -1)
		{
			set_inf(inf, agv);
			builtin = _builtin(inf);
			if (builtin == -1)
				findcmd(inf);
		}
		else if (interac(inf))
			put_char('\n');
		freeinf(inf, 0);
	}
	whist(inf);
	freeinf(inf, 1);
	if (!interac(inf) && inf->stts)
		exit(inf->stts);
	if (builtin == -2)
	{
		if (inf->ernum == -1)
			exit(inf->stts);
		exit(inf->ernum);
	}
	return (builtin);
}

/**
 * _builtin - finds builtin command
 * @inf: parameter & return info struct
 * Return: -1 if builtin not found,
 *		0 if builtin executed successfully
 *		1 if builtin found but not successful
 *		-2 if builtin signals exit()
 */
int _builtin(info *inf)
{
	int j, built = -1;
	built_table builttbl[] = {
		{"exit", mexit},
		{"env", menv},
		{"help", mhelp},
		{"history", mhist},
		{"setenv", msetenv},
		{"unsetenv", munsetenv},
		{"cd", mcd},
		{"alias", malias},
		{NULL, NULL}
	};
	for (j = 0; builttbl[j].tp; j++)
		if (str_cmp(inf->av[0], builttbl[j].tp) == 0)
		{
			inf->lcount++;
			built = builttbl[j].funct(inf);
			break;
		}
	return (built);
}

/**
 * findcmd - finds command in PATH
 * @inf: the parameter & return info struct
 */
void findcmd(info *inf)
{
	char *p = NULL;
	int j, i;

	inf->p = inf->av[0];
	if (inf->lflag == 1)
	{
		inf->lcount++;
		inf->lflag = 0;
	}
	for (j = 0, i = 0; inf->str[j]; j++)
		if (!is_del(inf->str[j], " \t\n"))
			i++;
	if (!i)
		return;
	p = _path(inf, mgetenv(inf, "PATH="), inf->av[0]);
	if (p)
	{
		inf->p = p;
		forkcmd(inf);
	}
	else
	{
		if ((interac(inf) || mgetenv(inf, "PATH=")
			|| inf->av[0][0] == '/') && iscmd(inf, inf->av[0]))
			forkcmd(inf);
		else if (*(inf->str) != '\n')
		{
			inf->stts = 127;
			printerr(inf, "not found\n");
		}
	}
}

/**
 * forkcmd - forks exec thread to run cmd
 * @inf: the parameter & return info struct
 */
void forkcmd(info *inf)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return;
	}
	if (cpid == 0)
	{
		if (execve(inf->p, inf->av, get_envir(inf)) == -1)
		{
			freeinf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->stts));
		if (WIFEXITED(inf->stts))
		{
			inf->stts = WEXITSTATUS(inf->stts);
			if (inf->stts == 126)
				printerr(inf, "Permission denied\n");
		}
	}
}
