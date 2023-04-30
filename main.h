#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

char *get_path(char *exefile);
char *_getenv(const char *name);
int _env(void);
char *_strtok(char *str, char delim, unsigned int *len);
char *get_path2(char *exefile);
int _atoi(char *s);
int _strlen(char *s);
char *_strpbrk(char *s, char *accept);
#endif
