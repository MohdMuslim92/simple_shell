#include "main.h"

/**
 * _strpbrk - search string function
 * Description: a function that searches a string for any of a set
 * of bytes and when locates the first occurrence in the string it
 * returns a pointer to the byte that matches
 * or it returns NULL if the character is not found
 * @s: string passed to the function to search in
 * @accept: string passed to the function to search
 * Return: return a pointer to the first occurrence of the character
 */
char *_strpbrk(char *s, char *accept)
{
	int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
				return (s + i);
		}
	}

	return (NULL);
}
