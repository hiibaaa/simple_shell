#include "simple_shell.h"

/**
 * ft_split - Split a string into words using specified delimiters
 * @s: The input string
 * @delimiters: The string containing delimiter characters
 *
 * Return: An array of strings (words) extracted from the input string,
 *         terminated by a NULL pointer.
 */

char **ft_split(char *s, char *delimiters)
{
	int counter = 0;
	char **words;
	char *word;

	counter = 0;
	words = (char **)malloc(sizeof(char *) * (count_words(s, delimiters) + 1));

	if (!words)
		return (NULL);

	while (*s)
	{
		while (*s && _strchr(delimiters, *s))
			s++;

		if (*s && !_strchr(delimiters, *s))
		{
			int word_length = wordlen(s, delimiters);

			word = (char *)malloc(sizeof(char) * (word_length + 1));

			if (!word)
			{
				free_tokens(words);
				return (NULL);
			}

			_strncpy(word, s, word_length);
			word[word_length] = '\0';
			words[counter] = word;
			counter++;
			s += word_length;
		}
	}

	words[counter] = NULL;
	return (words);
}

/**
 * print_env - Print the environment variables
 *
 * This function prints the environment variables to the standard output.
 * Each environment variable is printed on a separate line.
 */

void print_env(void)
{
	int i = 0;
	char **env = environ;

	while (env[i])
	{
		_putstr(env[i]);
		_putchar('\n');
		i++;
	}
}

/**
 * handle_exit - Handle the "exit" command in the shell
 * @shell: Pointer to the shell structure
 *
 * This function handles the "exit" command. It checks for valid arguments,
 * sets the exit status accordingly, and performs cleanup before exiting.
 *
 * Return: Exit status code (0 for success, 2 for error).
 */

int handle_exit(t_shell *shell)
{
	if (!shell->tokens[1])
	{
		free_tokens(shell->tokens);
		free(shell->line);
		exit(shell->status);
	}
	if (_isnumber(shell->tokens[1]))
	{
		shell->status = _atoi(shell->tokens[1]);
		free_tokens(shell->tokens);
		free(shell->line);
		exit(shell->status);
	}
	else
	{
		char *err_str;

		shell->error_counter++;
		err_str = _itoa(shell->error_counter);
		write(STDERR_FILENO, shell->argv[0], _strlen(shell->argv[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, err_str, _strlen(err_str));
		write(STDERR_FILENO, ": ", 2);
		free(err_str);
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, shell->tokens[1], _strlen(shell->tokens[1]));
		write(STDERR_FILENO, "\n", 1);
		shell->status = 2;
		return (2);
	}
	return (0);
}

/**
 * builtins - Handle built-in commands in the shell
 * @shell: Pointer to the shell structure
 * This function checks for and handles built-in commands
 * like "echo," "exit," and "env."
 * It executes the corresponding action for each command.
 * Return: 0 if the command is a built-in and was executed, 1 otherwise.
 */

int builtins(t_shell *shell)
{

	if (_strncmp(shell->tokens[0], "echo", 4) ==
												0 && _strncmp(shell->tokens[0], "$?", 2))
	{
		printf("%d\n", shell->status);
		return (0);
	}
	if (_strncmp(shell->tokens[0], "exit", 4) == 0)
	{
		handle_exit(shell);
		return (0);
	}
	if (_strncmp(shell->tokens[0], "env", 3) == 0)
	{
		print_env();
		return (0);
	}

	return (1);
}

/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable
 * This function searches for the environment variable with the specified name
 * and returns its value.
 * Return: The value of the environment variable, or NULL if not found.
 */

char *_getenv(char *name)
{
	char **env = NULL, *var = NULL, *value = NULL;
	int i = 0, j = 0, len = 0;

	env = environ;
	while (env[i])
	{
		var = env[i];
		len = _strlen(name);
		for (j = 0; j < len; j++)
		{
			if (name[j] != var[j])
				break;
		}
		if (j == len && var[j] == '=')
		{
			value = var + len + 1;
			break;
		}
		i++;
	}
	return (value);
}
