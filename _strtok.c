#include "main.h"

void perror_and_exit(char *prompt, char *error);
void copy_token(char *temp, char *token, unsigned int len);

/**
 * _strtok - tokenizing the given string.
 * @str: the string to tokenize.
 * @delim: the delimiter to tokenizing upon.
 * @len: set the len of the token into it
 * Return: Dynamiclly allocated pointer to null-terminated token (string),
 *         or NULL if no delim found
 */
char *_strtok(char *str, char delim, unsigned int *len)
{
	static char *s;
	char *temp, *token;

	*len = 0; /*reset the len variable to zero*/
	if (str != NULL)
		s = str;
	/* if str is NULL at 1st call or reach the last element in the array */
	if (*s == '\n' || *s == '\0')
		return (NULL);

	temp = s;
	while (*temp == delim)/* iterates until the first char isn't a delim*/
	{       /*reach end of str and no token found*/
		if (*temp == '\n' || *temp == '\0')
			return (NULL);
		temp++;
	}
	s = temp;
	while (*s != delim && *s != '\n' && *s != '\0')
	{
		*len = *len + 1;
		s++;
	}

	token = malloc(sizeof(char) * (*len + 1));
	if (token == NULL)
	{
		perror_and_exit("MY PROMPT", "ENOMEM");
	}
	copy_token(temp, token, *len);
	return (token);
}

/**
 * perror_and_exit - print an error message to stderr and exit the program.
 * @prompt: the prompt to print before the error message.
 * @error: the error message to print.
 */
void perror_and_exit(char *prompt, char *error)
{
	dprintf(STDOUT_FILENO, "%s: ", prompt);
	perror(error);
	exit(EXIT_FAILURE);
}

/**
 * copy_token - copy the characters from temp into token.
 * @temp: the source string to copy from.
 * @token: the destination string to copy into.
 * @len: the number of characters to copy.
 */
void copy_token(char *temp, char *token, unsigned int len)
{
	unsigned int i;

	for (i = 0 ; i < len ; i++)
	{
		token[i] = temp[i];
	}
	if (len > 0)
		token[len] = '\0';
	token = NULL;
}
