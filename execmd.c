#include "shell.h"

void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("Error:");
		free(argv);
	}

	if (pid == 0)
	{
		if (argv)
		{
			command = argv[0];

			actual_command = get_location(command);

			if (execve(actual_command, argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
	}

	else
	{
		wait(&status);

		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				free(argv);
				exit(1);
			}
		}

	}
}
