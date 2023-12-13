#include "simple_shell.h"

/**
 * execute - Execute a command in the shell
 * @shell: Pointer to the shell structure
 * Return: The exit status of the executed command.
 */

int execute(t_shell *shell)
{
	char *full_path = NULL;

	if (builtins(shell) == 0)
		return (shell->status);
	if (shell->tokens[0][0] == '/' && access(shell->tokens[0], F_OK) != 0)
	{
		writerr(shell->tokens, shell->argv, &shell->error_counter);
		return (get_last_exit(1, 127));
	}
	full_path = get_full_path(shell->tokens);
	if (!full_path || access(full_path, X_OK) != 0)
	{
		writerr(shell->tokens, shell->argv, &shell->error_counter);
		if (full_path)
			free(full_path);
		return (get_last_exit(1, 127));
	}
	free(full_path);
	shell->status = run_command(shell);
	return (shell->status % 255);
}

/**
 * read_to_stash - Read from a file descriptor into a stash string
 * @fd: File descriptor to read from
 * @stash: String to accumulate the read content
 * Return: The accumulated content in the stash string.
 */

char *read_to_stash(int fd, char *stash)
{
	int r;
	char *buffer;

	r = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			break;
		buffer[r] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (stash);
}

/**
 * get_line_from_stash - Extract a line from the stash string
 * @stash: String containing accumulated content
 * Return: The extracted line as a new string, or NULL if the stash is empty.
 */

char *get_line_from_stash(char *stash)
{
	int i;
	char *line;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

/**
 * get_new_stash - Get a new stash with content after the first line
 * @stash: String containing accumulated content
 * Return: The new stash with content after the first line,
 * or NULL if no content remains.
 */

char *get_new_stash(char *stash)
{
	int i;
	char *new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || (stash[i] == '\n' && !stash[i + 1]))
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, _strlen(stash) - i + 1);
	free(stash);
	return (new_stash);
}

/**
 * get_next_line - Read and return the next line from a file descriptor
 * @fd: File descriptor to read from
 * Return: The next line from the file descriptor, or NULL on EOF or error.
 */

char *get_next_line(int fd)
{
	static char *stash;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);

	stash = read_to_stash(fd, stash);

	if (!stash)
		return (NULL);

	line = get_line_from_stash(stash);
	stash = get_new_stash(stash);

	return (line);
