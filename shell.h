#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
char *read_prompt(const char *prompt);
char *get_location(char *command);
int tokenize(char *lineptr);
int getLenghtToken(char *lineptr, const char *delim);
void free_tokens(char **tokens, int num_tokens);
void execmd(char **argv);
extern char **environ;

#endif
