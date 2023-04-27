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
	int i = 0, j = 0, pid = 0, status = 0, new_line = 0;
	unsigned int len = 0;

	do {
		i = 0, j = 0, arg_len = 0, new_line = 0;
		line = NULL;
		if (isatty(0))
		{
			new_line = 1;
			printf("$: ");
		}
		if (getline(&line, &arg_len, stdin) == -1)
		{
			if (new_line)
				printf("\n");
			free(line);
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
			dprintf(STDOUT_FILENO, "%s: ", argv[0]);
			perror("");
			continue;
		}

/*		if (_strcmp(exefile, "exit") == 0)*/
/*			break;*/
		if (exefile[0] == '/')
			j = 1;
		args[0] = exefile;
		while (args[i] != NULL)
		{
			if (args[i][0] == '\0')
			{
				args[i] = NULL;
				break;
			}
			args[++i] = _strtok(NULL, ' ', &len);
		}
		exefile = get_path2(exefile);/*, env);*/
		if (exefile == NULL)
		{
			dprintf(STDOUT_FILENO, "%s: ", argv[0]);
			perror("");
			free(line);
			for (i = j ; args[i] ; i++)
				free(args[i]);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(exefile, args, env) < 0)
			{
				free(line);
				free(exefile);
				for (i = j ; args[i] ; i++)
					free(args[i]);
				continue;
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
