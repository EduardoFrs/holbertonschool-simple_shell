#include "shell.h"

/**
 * check_path_executable - Checks if the file at path is executable.
 * @path: The path to the file.
 * Return: 1 if the file is executable, 0 otherwise.
 */

int check_path_executable(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR))
		{
			return (1);
		}
	}
	return (0);
}

/**
 * create_command_path - Creates a command path from the command input
 * @command: The command input user entered
 * Return: A pointer to the string containing the path, NULL if failed
 */

char *create_command_path(char *command)
{
	char *cmd_path = NULL;
	size_t len;

	if (command[0] == '/')
	{
		if (check_path_executable(command))
		{
			len = strlen(command) + 1;
			cmd_path = malloc(len);
			if (!cmd_path)
			{
				perror("malloc");
				return (NULL);
			}
			strcpy(cmd_path, command);
		}
	}
	else
	{
		cmd_path = find_command_in_path(command);
	}
	return (cmd_path);
}

/**
 * execute_in_child - Executes a command in the child process
 * @cmd_path: The path command to be executed
 * @parsed_command: The parsed command with all arguments
 * @env: The environment
 */

void execute_in_child(char *cmd_path, char **parsed_command, char **env)
{

	if (execve(cmd_path, parsed_command, env) == -1)
	{
		perror("execve");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_command - Forks the current process and executes a command
 * @parsed_command: The parsed command with all arguments
 * @program_name: The name of the program
 * @env: The environment
 */

void execute_command(char **parsed_command, char *program_name, char **env)
{
	char *cmd_path = create_command_path(parsed_command[0]);
	pid_t pid;
	int status;

	if (!cmd_path)
	{
		fprintf(stderr, "%s: ", program_name);
		perror(parsed_command[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		execute_in_child(cmd_path, parsed_command, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}
