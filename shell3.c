#include "simple_shell.h"

/**
* *_memcpy - function that copies memory area.
* @dest: memorye area destination
* @src: memory area source
* @n: number of bytes to copy
* Return: Returns a pointer to dest
*/

char *_memcpy(char *dest, char *src, unsigned int n)
{
unsigned int i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
		return (dest);
}

/**
 * ft_strjoin - joins two strings
 * @s1: the first string
 * @s2: the second  string
 * Return: the joined string
 */

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		size;

	if (!s1)
		s1 = _strdup("");
	size = _strlen(s1) + _strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	_memcpy(str, s1, _strlen(s1));
	_memcpy(str + _strlen(s1), s2, _strlen(s2));
	str[size] = '\0';
	free(s1);
	return (str);
}

/**
 * _isnumber - checks if a string is a number
 * @str: string to check
 * Return: 0 if number, 1 if not
 */

int _isnumber(char *str)
{
	int i = 0;

	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 * Return: pointer to the duplicated string
 */

char *_strdup(char *str)
{
	int i = 0;
	char *dup = NULL;

	if (str == NULL)
		return (NULL);
	dup = malloc(sizeof(char) * (_strlen(str) + 1));
	if (dup == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * sigintHandler - Handle the SIGINT (Ctrl+C) signal
 * @sig_num: The signal number (unused)
 */

void sigintHandler(int sig_num)
{
	(void)sig_num;
	signal(SIGINT, sigintHandler);
	fflush(stdout);
}
