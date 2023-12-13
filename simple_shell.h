#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 5

/**
 * struct s_shell - shell struct
 * @argv: arguments
 * @env: environement
 * @line: the command line
 * @tokens: command tokens
 * @error_counter: number of the error
 * @status: the status code
 * Description: shell struct
*/

typedef struct s_shell
{
char **argv;
char **env;
char *line;
char **tokens;
int status;
int error_counter;
}   t_shell;

extern char **environ;


int     wordlen(char *s, char *delimiters);
char    **ft_split(char *s, char *delimiters);
void    print_env(void);
int     handle_exit(t_shell *shell);
int     builtins(t_shell *shell);
char    *_getenv(char *name);
int     get_last_exit(int action, int status);
void    writerr(char **tokens, char **argv, int *error_counter);
char    *is_file_in_path(char *path, char *file);
char    *get_full_path(char **tokens);
int     run_command(t_shell *shell);
int     execute(t_shell *shell);
char    *read_to_stash(int fd, char *stash);
char    *get_line_from_stash(char *stash);
char    *get_new_stash(char *stash);
char	*get_next_line(int fd);
char    *make_path(char *path, char *cmd);
char    *get_path(char *cmd);
int     _putchar(char c);
void    _putstr(char *str);
char    *_strncpy(char *dest, char *src, int n);
int     count_words(char *s, char *delimiters);
int     _strlen(char *s);
char    *_strchr(const char *s, int c);
char    *join(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char    *_strcpy(char *dest, char *src);
char    *_memcpy(char *dest, char *src, unsigned int n);
int     _isnumber(char *str);
char    *_strdup(char *str);
void    sigintHandler(int sig_num);
int     _atoi(char *str);
char    *_strcat(char *dest, char *src);
void    free_tokens(char **ptr);
void    cut_string(char *str);
int     ft_nbrlen(int n);
char    *_itoa(int n);
char    *ft_strjoin(char *s1, char *s2);
int     _strncmp(char *str1, char *str2, int n);

#endif
