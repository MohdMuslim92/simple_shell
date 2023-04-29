#include "main.h"

int _strcmp(char *str1, char *str2);
int _empty(char *buffer);
void _perror(char *prog_name, int err_nom, char *command);
void print_num(int num);

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
	pid_t r_val = 0;
	int i = 0, j = 0, pid = 0, status = 0, new_line = 0, err_nom = 1;
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
			exit(r_val);
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
			write(2, (void *)argv[0], _strlen(argv[0]));
			write(2, ": ", 2);
			perror("");
			r_val = 132;
			continue;
		}
		if (exefile[0] == '/' || exefile[0] == '.')
			j = 1;
		args[0] = exefile;
		i = 0;
		while (args[i++] != NULL)
			args[i] = _strtok(NULL, ' ', &len);
		if (_strcmp(exefile, "exit") == 0)
		{
			free(line);
			if (args[1])
			{
				if (args[1][0] < 48 || args[1][0] > 57)
				{
					_perror(argv[0], err_nom, "exit");
					write(2, args[1], _strlen(args[1]));
					write(2, "\n", 1);
					r_val = 2;
					for (i = j ; args[i] ; i++)
						free(args[i]);
					continue;
				}
				status = _atoi(args[1]);
				for (i = j ; args[i] ; i++)
					free(args[i]);
				if  (status < 0)
				{
					_perror(argv[0], err_nom, "exit");
					write(2, "-", 1);
					print_num(-1 * status);
					write(2, "\n", 1);
					r_val = 2;
					continue;
				}
				/*free(exefile);*/
				exit(status & 0xff);
			}
			free(exefile);
			exit(r_val);
		}
		exefile = get_path(exefile);
		if (exefile == NULL)
		{
			_perror(argv[0], err_nom, args[0]);
			err_nom++;
			r_val = 127; /*command not found errnom*/
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
		r_val = wait(&status);
		if (WIFEXITED(status))
			r_val = WEXITSTATUS(status);
		free(exefile);
		for (i = j ; args[i] ; i++)
			free(args[i]);
		free(line);
	} while (1);
	return (r_val);
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

/**
 * _perror - write error message to the stderror
 * @prog_name: name of the program
 * @err_nom: error number
 * @command: name of the command
 * Return: void
 */
void _perror(char *prog_name, int err_nom, char *command)
{
	write(2, (void *)prog_name, _strlen(prog_name));
	write(2, ": ", 2);
	print_num(err_nom);
	write(2, ": ", 2);
	write(2, command, _strlen(command));
	if (_strcmp(command, "exit") == 0)
	{
		write(2, ": illigal number", 20);
	}
	else
		write(2, ": not found\n", 12);
}

/**
 * print_num - print an intger number n
 * @num: intger number arg1
 * Return: void
 */

void print_num(int num)
{
	if (num > 9)
	{
		print_num(num / 10);
	}
	num = num % 10 + '0';
	write(2, &num, 1);
}
