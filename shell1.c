#include "simple_shell.h"

/**
 * _putchar - Write a character to the standard output
 * @c: The character to be written
 * Return: On success, 1 is returned; on error, -1 is returned.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _putstr - Write a string to the standard output
 * @str: The string to be written
 */

void _putstr(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str + 0);
		str++;
	}
}

/**
 * _strncpy - Copy at most n characters from source to destination
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of characters to copy
 * Return: A pointer to the destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;

	for (; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * count_words - Count the number of words in
 * a string using specified delimiters
 * @s: The input string
 * @delimiters: The string containing delimiter characters
 * Return: The number of words in the input string.
 */

int count_words(char *s, char *delimiters)
{
	int counter = 0;
	int found = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (_strchr(delimiters, s[i]) != NULL)
			found = 0;
		else if (found == 0)
		{
			found = 1;
			counter++;
		}
		i++;
	}
	return (counter);
}

/**
 * wordlen - Calculate the length of a word
 * in a string using specified delimiters
 * @s: The input string
 * @delimiters: The string containing delimiter characters
 * Return: The length of the word.
 */

int wordlen(char *s, char *delimiters)
{
	int i = 0;

	while (s[i] && !_strchr(delimiters, s[i]))
		i++;
	return (i);
}
