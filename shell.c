/*
 * File: shell.c
 * Auth: wessal el hasnaoui 
 */

#include "shell.h"
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, \
	0, 0, NULL, 0, 0, 0}

/**
 * main - Entry point
 * @agc: args count
 * @agv: args vector
 * Return: 0 on success, 1 on error
 */
int main(int agc, char **agv)
{
	info inf[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f) : "r" (f));
	if (agc == 2)
	{
		f = open(agv[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eput(agv[0]);
				_eput(": 0: Can't open ");
				_eput(agv[1]);
				eput_char('\n');
				eput_char(FLUSH_BUFF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->rfd = f;
	}
	pop_env(inf);
	rhist(inf);
	h(inf, agv);
	return (EXIT_SUCCESS);
}
