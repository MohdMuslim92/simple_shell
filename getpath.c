#include "main.h"

/**
 * get_path2 - check if the exefile is an executable file
 * @exefile: the file to be check
 * Return: pointer to the file path or NULL in failure
 */

char *get_path2(char *exefile)
{
	if (!access(exefile, F_OK | X_OK))
	{
		return (exefile);
	}
	return (NULL);
}
