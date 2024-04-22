#include "shell.h"

/**
 * execmd - function to execute a command
 * @argv: An array of arguments
 * Description: forks a new process and executes a command
 */

void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;
	pid_t pid = fork(); /* tout en dessous éxécuté deux fois */
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
	else /* pid > 0 donc c'est le code du parent */
	{
		wait(&status); /*wait for child to finish*/

		if (WIFEXITED(status)) /*check if child process exited normally*/
		{
			if (WEXITSTATUS(status) != 0) /*check status exit of child process*/
			{
				free(argv);
				exit(2);
			}
		}

	}
}
