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
	char *prompt = "$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	char *token;
	int num_tokens;
	int i;
	char *lineptr_copy;

	(void)ac;

	if (isatty(STDIN_FILENO))
	{
		printf("%s", prompt);
	}

	while ((nchars_read = getline(&lineptr, &n, stdin)) != -1)
	{
		if (nchars_read > 1)
		{
			argv = NULL;
			num_tokens = 0;
			lineptr_copy = strdup(lineptr);
			if (lineptr_copy == NULL)
			{
				perror("tsh: memory allocation error");
				free(lineptr);
				return -1;
			}

			token = strtok(lineptr_copy, delim);
			while (token != NULL)
			{
				num_tokens++;
				token = strtok(NULL, delim);
			}
			argv = calloc(num_tokens + 1, sizeof(char*));
			if (argv == NULL)
			{
				perror("Memory allocation failed");
				free(lineptr_copy);
				free(lineptr);
				return -1;
			}

			i = 0;
			token = strtok(lineptr_copy, delim);
			while (token != NULL)
			{
				argv[i++] = strdup(token);
				token = strtok(NULL, delim);
			}
			argv[i] = NULL;

			if (argv[0] != NULL && strcmp(argv[0], "exit") == 0)
			{
				for (i = 0; argv[i]; i++)
				{
					free(argv[i]);
				}
				free(argv);
				free(lineptr_copy);
				break;
			}

			execmd(argv);

			for (i = 0; argv[i]; i++)
			{
				free(argv[i]);
			}
			free(argv);
			free(lineptr_copy);
		}

		if (isatty(STDIN_FILENO))
		{
			printf("%s", prompt);
		}
	}

	free(lineptr);

	if (ferror(stdin))
	{
		perror("Error reading from input");
		return (-1);
	}

	return (0);
}
