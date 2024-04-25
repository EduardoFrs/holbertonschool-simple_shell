#include "shell.h"

int main(int ac, char **argv)
{
	char *prompt = "(simple_shell) $ ";
	char *command = NULL, *command_copy = NULL, *token;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int i, num_tokens = 0;

	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&command, &n, stdin);

		if (nchars_read == -1)
		{
			return (-1);
		}

		command_copy = malloc(sizeof(char) * nchars_read);
		if (command_copy == NULL)
		{
			perror("memory allocation error");
			return (-1);
		}

		strcpy(command_copy, command);

		token = strtok(command, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(command_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		execmd(argv);

	}

	free(command_copy);
	free(command);

	return (0);
}


