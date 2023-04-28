#include "main.h"

/**
 * _strlen - Entry point
 * Description: using a function _strlen to return the
 * length of a string that passed to the function
 * @s: the address of the string
 * Return: return the length of the passed string
 */
int _strlen(char *s)
{
	int i = 0;

	for (i = 0; s[i] != '\0'; i++)
		;

	return (i);
}

