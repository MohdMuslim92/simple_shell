#include "main.h"

/**
 * _getenv - search for name in env and return its value
 * @name: pointer to the variable name
 * Return: pointer to name's value, or NULL if there no variable in name name
 */
char *_getenv(const char *name)
{
	char *value;
	int i, match;
	unsigned int len, j;

	if (name == NULL)
	{
		dprintf(STDOUT_FILENO, "%s: ", "MY PROMPT");
		perror("EINVAL");
		return (NULL);
	}
	len = strlen(name);
	/*loop over all the environment variables searching for the name*/
	i = 0;
	while (environ[i] != NULL)
	{
		for (j = 0 ; j < len ; j++)
		{
			/*if the name did not match the current env break*/
			if (name[j] != environ[i][j])
			{
				match = 0;
				break;
			}
			match = 1;
		}
		if (match)
		{
			/*return the first '=' in the matched env*/
			value = _strpbrk(environ[i], "=");
			if (value == NULL)
				return (NULL);
			/*++ because the returned pointer is including = sign*/
			return (++value);
		}
		i++;
	}
	dprintf(STDOUT_FILENO, "%s: ", "MY PROMPT");
	perror("EINVAL");
	return (NULL);
}
