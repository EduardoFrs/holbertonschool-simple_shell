#include "shell.h"

extern char **environ; /* environment variable */

int main(int ac, char **argv)
{
	char *prompt = "(Eshell) $ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	/* declaring void variables */
	(void)ac;

	/* Create a loop for the shell's prompt */
	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		/* check if the getline function failed or reached EOF or user use CTRL + D */
		if (nchars_read == -1)
		{
			printf("Exiting shell....\n");
			return (-1);
		}

		/* allocate space for a copy of the lineptr */
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		/* copy lineptr to lineptr_copy */
		strcpy(lineptr_copy, lineptr);

		/********** split the string (lineptr) into an array of words ********/
		/* calculate the total number of tokens */
		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* Allocate space to hold the array of strings */
		argv = malloc(sizeof(char *) * num_tokens);

		/* Store each token in the argv array */
		token = strtok(lineptr_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* check if arg is "exit"*/
		if (argv[0] != NULL && strcmp(argv[0], "exit") == 0)
		{
			printf("Exiting shell ...\n");
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

		/* execute the command */
		execmd(argv);

	}


	/* free up allocated memory */
	free(lineptr_copy);
	free(lineptr);

	return (0);
}
