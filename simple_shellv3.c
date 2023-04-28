#include "main.h"

int _strcmp(char *str1, char *str2);
int _empty(char *buffer);
/**
 * main - entry point for the simple shell
 * @argc: arguments number
 * @argv: list of program arguments
 * Return: 0 in success -1 otherwise
 */
int main(__attribute__((unused))int argc, char **argv)
{
	char *args[1024];

	char *line = NULL, *exefile = NULL;
	size_t arg_len = 0;
	int i = 0, j = 0, pid = 0, status = 0, new_line = 0;
	unsigned int len = 0;

	do {
		i = 0, j = 0, arg_len = 0, new_line = 0;
		line = NULL;
		if (isatty(0))
		{
			new_line = 1;
			write(1, "$: ", 3);
		}
		if (getline(&line, &arg_len, stdin) == -1)
		{
			if (new_line)
				write(1, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (_empty(line))
		{
			free(line);
			continue;
		}
		exefile = _strtok(line, ' ', &len);
		if (exefile == NULL)
		{
			free(line);
			write(1, (void *)argv[0], _strlen(argv[0]));
			write(1, ": ", 2);
			perror("");
			continue;
		}
		if (_strcmp(exefile, "exit") == 0)
			break;
		if (exefile[0] == '/')
			j = 1;
		args[0] = exefile;
		i = 0;
		while (args[i++] != NULL)
			args[i] = _strtok(NULL, ' ', &len);
		exefile = get_path(exefile);
		if (exefile == NULL)
		{
			write(1, (void *)argv[0], _strlen(argv[0]));
			write(1, ": ", 2);
			perror("");
			free(line);
			for (i = j ; args[i] ; i++)
				free(args[i]);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(exefile, args, environ) < 0)
			{
				free(line);
				free(exefile);
				for (i = j ; args[i] ; i++)
					free(args[i]);
				exit(EXIT_FAILURE);
			}
		}
		i = wait(&status);
		free(exefile);
		for (i = j ; args[i] ; i++)
			free(args[i]);
		free(line);
	} while (1);
	free(exefile);
	free(line);
	return (0);
}

/**
 * _strcmp - compiare two string
 * @str1: first string
 * @str2: second string
 * Return: 0 if match, non-zero other wise
 */
int _strcmp(char *str1, char *str2)
{
	unsigned int len2, i;

	len2 = _strlen(str2);
	for (i = 0 ; i < len2 ; i++)
		if (str1[i] != str2[i])
			return (-1);
	return (0);
}

/**
 * _empty - check if the the buffer is all spaces "empty buffer"
 * @buffer: pointer to the buffer to check
 * Return: 1 if empty, 0 other-wise
 */
int _empty(char *buffer)
{
	int i = 0;

	if (buffer == NULL)
		return (1);
	for (i = 0 ; buffer[i] != '\n' && buffer[i] != '\0' ; i++)
	{
		if (buffer[i] != ' ')
			return (0);
	}
	return (1);
}
