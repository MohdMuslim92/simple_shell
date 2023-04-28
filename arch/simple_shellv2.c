#include "main.h"

long int get_arg_max(char **argv, char **env);
int _strcmp(char *str1, char *str2);
/**
 * main - entry point for the simple shell
 * @argc: arguments number
 * @argv: list of program arguments
 * @env: list of program environment variables
 * Return: 0 in success -1 otherwise
 */
int main(__attribute__((unused))int argc, char **argv, char **env)
{
	char *args[1024];

	char *line = NULL, *exefile = NULL;
	size_t arg_len = 0;
	int i = 0, pid = 0, status = 0, ernom = 1;
	unsigned int len = 0;

	do {
		i = 0, arg_len = 0;
		line = NULL;
		if (isatty(0))
			printf("$: ");
		if (getline(&line, &arg_len, stdin) == -1)
		{
			printf("\n");
			free(line);
			/*free(exefile);*/
			exit(EXIT_SUCCESS);
		}
		if (line[0] == '\n')/*strcmp(line, "\n") == 0)*/
		{
			free(line);
			continue;
		}
		exefile = _strtok(line, ' ', &len);
		if (exefile == NULL)
		{
			free(line);
			perror(argv[0]);
			continue;
		}
		if (_strcmp(exefile, "exit") == 0)
			break;
		args[0] = exefile;
		while (args[i] != NULL)
			args[++i] = _strtok(NULL, ' ', &len);
		exefile = get_path(exefile, env);
		if (exefile == NULL)
		{
			free(line);
			free(exefile);
			for (i = 1 ; args[i] ; i++)
				free(args[i]);
			dprintf(STDOUT_FILENO, "%s: %d: %s: ",
				argv[0], ernom, args[0]);
			dprintf(STDOUT_FILENO, "%s\n", error_no);
			ernom++;
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			i = execve(exefile, args, env);
			if (i < 0)
			{
				perror(args[0]);
				free(line);
				for (i = 0 ; args[i] ; i++)
					free(args[i]);
				perror(argv[0]);
				continue;
			}
		}
		i = wait(&status);
		free(exefile);
		for (i = 1 ; args[i] ; i++)
			free(args[i]);
		free(line);
	} while (1);
	free(exefile);
	free(line);
	return (0);
}

/**
 * get_arg_max - calculate maximum allowed number of args
 * @argv: array of program's arguments
 * @env: array of program's environment variables
 * Return: maximum allowed number of arguments
 */

long int get_arg_max(char **argv, char **env)
{
	unsigned int envc = 0, argc = 0, i = 0;

	while (env[i])
	{
		envc += strlen(env[i]);
		i++;
	}
	i = 0;
	while (argv[i])
	{
		argc += strlen(argv[i]);
		i++;
	}
	return (sysconf(SCHAR_MAX) - (long int)envc - 2048l);
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

	len2 = strlen(str2);
	for (i = 0 ; i < len2 ; i++)
		if (str1[i] != str2[i])
			return (-1);
	return (0);
}
