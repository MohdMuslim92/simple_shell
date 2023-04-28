#include "main.h"
char *creat_path(char *path, unsigned int len, char *exefile);

/**
 * get_path - get the path of the executable file
 * @exefile: the name of the executable file
 * @environ: environment variables pointer
 * Return: the absolute path of exefile, or NULL if the name of the file
 *         is not in the PATH environment variable, and the ERROR_NO set
 */
char *get_path(char *exefile, char **environ)
{
	char *paths = NULL, *temp = NULL, *exe_path = NULL;
	int f_state = 0;
	unsigned int len = 0;

	paths = _getenv("PATH", environ);
	if (exefile[0] == '/')
	{
		if (!access(exefile, F_OK | X_OK))
			return (exefile);
		return (NULL);
	}
	temp = _strtok(paths, ':', &len);
	while (temp != NULL)
	{
		exe_path = creat_path(temp, len, exefile);
		if (exe_path == NULL)
		{
			free(temp);
			return (NULL);
		}
		f_state = access(exe_path, F_OK | X_OK);
		if (f_state == 0)
		{
			free(temp);
			return (exe_path);
		}
		free(temp);
		free(exe_path);
		temp = _strtok(NULL, ':', &len);
	}
	/*free(exe_path);*/
	return (NULL);
}
/**
 * creat_path - take the path and the exefile compianes them togither to
 *         creat the executable file apsolute path.
 * @path: the director to compain to.
 * @len: the length of the path string.
 * @exefile: the file to compined to directory.
 * Return: the apsolute path pointer or NULL in failure.
 */
char *creat_path(char *path, unsigned int len, char *exefile)
{
	char *exe_path;
	int i, j;

	exe_path = malloc(sizeof(char) *
			  (len + _strlen(exefile) + 2));
	if (exe_path == NULL)
		return (NULL);
	for (i = 0 ; path[i] ; i++)
		exe_path[i] = path[i];
	exe_path[i++] = '/';
	for (j = 0 ; exefile[j] ; j++, i++)
		exe_path[i] = exefile[j];
	exe_path[i] = '\0';
	return (exe_path);
}
