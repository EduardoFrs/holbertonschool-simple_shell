#include "shell.h"

/**
 * main - Entry point for the shell program
 * @ac: Number of arguments passed to the program
 * @argv: An array of pointers to the arguments
 *
 * Return: If an error occurs, return -1. Otherwise 0
 */

int main(int ac, char **argv)
{
    /*	char *prompt = "$ ";*/
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	(void)ac;

	while (1)
	{
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
            /*printf("%s", prompt);*/
            perror("Error reading input");
            free(lineptr);
			return (-1);
		}

		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lineptr_copy, lineptr);

		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(lineptr_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		if (argv[0] != NULL && strcmp(argv[0], "exit") == 0)
		{
			break;
		}

		if (argv[0] != NULL && strcmp(argv[0], "env") == 0)
		{
			char **env = environ;

			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
			continue;
		}
		execmd(argv);
	}
	free(lineptr_copy);
	free(lineptr);

	return (0);
}
