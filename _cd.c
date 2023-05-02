#include "main.h"

/**
 * _cd - a builtin function that change the current directory
 * @prog_name: the shell name to printed befor error
 * @args: the arguments passed to the command
 * Return: 0- in success non-zero other wise
 */

int _cd(char *prog_name, char **args)
{
char *dir;

	if (args[1] == NULL)/* if no arguments change to home*/
		dir = _getenv("HOME");
	else if (strcmp(args[1], "-") == 0)/*change to previous directory*/
	{
		dir = _getenv("OLDPWD");
		if (dir == NULL)
		{
			write(2, (void *)prog_name, _strlen(prog_name));
			write(2, ": cd: OLDPWD not set\n", 20);
			return (-1);
		}
	}
	else
		dir = args[1];
	if (chdir(dir) == -1) /* change directory */
	{
	write(2, (void *)prog_name, _strlen(prog_name));
	write(2, ": cd: ", 6);
	write(2, args[1], _strlen(args[1]));
	write(2, ": No such file or directory\n", 28);
	return (-1);
	}
	return (0);
}
