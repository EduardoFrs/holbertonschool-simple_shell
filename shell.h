#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int ac, char **av, char **env);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);

#endif