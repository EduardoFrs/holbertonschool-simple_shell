#include "shell.h"

void execmd(char **argv){
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
			/* get the command */
			command = argv[0];

			/* generate the path to this command before passing it to execve */
			actual_command = get_location(command);

			/* execute the actual command with execve */
			if (execve(actual_command, argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
	}

	else
	{
		wait (&status);

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