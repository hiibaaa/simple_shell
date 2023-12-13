#include "simple_shell.h"

/**
 * init_shell_struct - Initialize the shell structure
 * @shell: Pointer to the shell structure to be initialized
 * @argv: Command-line argument array
 * @env: Environment variable array
 */

void init_shell_struct(t_shell *shell, char **argv, char **env)
{
	shell->argv = argv;
	shell->env = env;
	shell->error_counter = 0;
	shell->status = 0;
}

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * @env: Array of environment variable strings
 * Return: The exit status of the shell.
 */

int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	t_shell shell;

	init_shell_struct(&shell, argv, env);

	sigintHandler(0);

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			_putstr("$ ");
		}

		shell.line = get_next_line(STDIN_FILENO);

		if (!shell.line)
		{
			if (isatty(STDIN_FILENO))
			{
				_putchar('\n');
			}
			break;
		}

		cut_string(shell.line);
		shell.tokens = ft_split(shell.line, " \t\r\n");

		if (shell.tokens)
		{
			if (shell.tokens[0])
			{
				shell.status = execute(&shell);
			}

			free_tokens(shell.tokens);
		}

		free(shell.line);
	}
	return (shell.status);
}
