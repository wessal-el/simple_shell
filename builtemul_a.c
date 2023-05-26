/*
 * File: builtemul_a.c
 * Auth: wessal el hasnaoui
 */

#include "shell.h"

/**
 * mexit - exits shell
 * @inf: Structure containing potential arguments
 *  Return: (0) if info.argv[0] != "exit"
 */
int mexit(info *inf)
{
	int check;

	if (inf->av[1])
	{
		check = erratoi(inf->av[1]);
		if (check == -1)
		{
			inf->stts = 2;
			printerr(inf, "illegal number: ");
			_eput(inf->av[1]);
			eput_char('\n');
			return (1);
		}
		inf->ernum = erratoi(inf->av[1]);
		return (-2);
	}
	inf->ernum = -1;
	return (-2);
}

/**
 * mcd - changes current directory
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int mcd(info *inf)
{
	char *c, *d, buf[1024];
	int chdir_;

	c = getcwd(buf, 1024);
	if (!c)
		_put("TODO: >>getcwd failure msg here<<\n");
	if (!inf->av[1])
	{
		d = mgetenv(inf, "HOME=");
		if (!d)
			chdir_ = chdir((d = mgetenv(inf, "PWD="))
					? d : "/");
		else
			chdir_ = chdir(d);
	}
	else if (str_cmp(inf->av[1], "-") == 0)
	{
		if (!mgetenv(inf, "OLDPWD="))
		{
			_put(c);
			put_char('\n');
			return (1);
		}
		_put(mgetenv(inf, "OLDPWD=")), put_char('\n');
		chdir_ = chdir((d = mgetenv(inf, "OLDPWD="))
				? d : "/");
	}
	else
		chdir_ = chdir(inf->av[1]);
	if (chdir_ == -1)
	{
		printerr(inf, "Can't cd to ");
		_eput(inf->av[1]), eput_char('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", mgetenv(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * mhelp - changes current directory
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int mhelp(info *inf)
{
	char **array;

	array = inf->av;
	_put("Help call works. Function not yet implemented \n");
	if (0)
		_put(*array);
	return (0);
}
