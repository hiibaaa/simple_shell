#include "simple_shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * free_tokens - frees a double pointer
 * @ptr: double pointer to be freed
 * Return: void
 */

void free_tokens(char **ptr)
{
	int i = 0;

	while (ptr[i])
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

/**
 * cut_string - cuts a string when # is encountered
 * @str: string to be cut
 */

void cut_string(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '#')
		{
			str[i] = '\0';
			return;
		}
		i++;
	}
}

/**
 * ft_nbrlen - counts the number of digits in q number
 * @n: the number
 * Return: the number of digits
 */

int	ft_nbrlen(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

/**
 * _strncmp - compares two strings
 * @str1: first string
 * @str2: second string
 * @n: number of bytes to compare
 * Return: 0 if strings are equal, -1 if not
 */

int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0' && i < n)
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (i == n)
		return (0);
	return (-1);
}
