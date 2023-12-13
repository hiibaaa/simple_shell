#include "simple_shell.h"

/**
 * get_last_exit - Track and retrieve the last exit status
 * @action: Action flag (1 for setting, 0 for retrieving)
 * @status: Exit status value to set (if action is 1)
 * Return: The last exit status.
 */

int get_last_exit(int action, int status)
{
	static int last_exit;

	if (action == 1)
		last_exit = status;
	return (last_exit);
}

/**
 * writerr - Print command not found error message
 * @tokens: Array of tokens representing the command
 * @argv: Array of command-line arguments
 * @error_counter: Pointer to the error counter
 */

void writerr(char **tokens, char **argv, int *error_counter)
{
	char *err_str;

	(*error_counter)++;
	err_str = _itoa(*error_counter);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_str, _strlen(err_str));
	write(STDERR_FILENO, ": ", 2);
	free(err_str);
	write(STDERR_FILENO, tokens[0], _strlen(tokens[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * is_file_in_path - Search for a file in directories specified by path
 * @path: Colon-separated list of directories
 * @file: The file to search for
 * Return: The full path to the file if found, otherwise NULL.
 */

char *is_file_in_path(char *path, char *file)
{
	int i = 0;
	char *full_path;
	char **dirs;
	char *base;

	dirs = ft_split(path, ":");
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		base = join(dirs[i], "/");
		full_path = join(base, file);
		free(base);
		if (access(full_path, F_OK) == 0)
		{
			free_tokens(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tokens(dirs);
	return (NULL);
}

/**
 * get_full_path - Get the full path of an executable file
 * @tokens: Array of tokens representing the command
 * Return: The full path of the executable file, or NULL if not found.
 */

char *get_full_path(char **tokens)
{
	char *path = _getenv("PATH");
	char *full_path = NULL;

	if (tokens[0][0] == '.' && tokens[0][1] ==
												'/' && access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else if (tokens[0][0] == '.' && tokens[0][1] ==
													'.' && tokens[0][1] == '.' && access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else if (tokens[0][0] == '/' && access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else
	{
		if (!path)
		{
			free(full_path);
			return (NULL);
		}
		full_path = is_file_in_path(path, tokens[0]);
	}
	return (full_path);
}

/**
 * run_command - Execute a command in a child process
 * @shell: Pointer to the shell structure
 * Return: The exit status of the executed command.
 */

int run_command(t_shell *shell)
{
	pid_t child_pid = 0;
	char *full_path;

	full_path = get_full_path(shell->tokens);
	if (access(full_path, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(shell->argv[0]);
			free(full_path);
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(full_path, shell->tokens, shell->env) == -1)
			{
				perror(shell->argv[0]);
				free(full_path);
				exit(127);
			}
		}
		else
		{
			wait(&shell->status);
		}
		free(full_path);
	}
	return (shell->status % 255);
}
