#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int ac, char **argv);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);
void execmd(char **argv);
char *get_location(char *command);
int stat(const char *pathname, struct stat *statbuf);

#endif