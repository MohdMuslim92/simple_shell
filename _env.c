#include "main.h"

/**
 * _env - a builtin function that ientical to the shell env() function
 * Return: 0- in success non-zero othe wise
 */

int _env(void)
{
	int i = 0;

	if (environ == NULL)
		return (1);
	while (environ[i])
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
