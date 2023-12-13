#include "simple_shell.h"

/**
* _strlen - function that returns the length of a string
* @s: the string that we will return its length
* Return: return the string length
*/

int _strlen(char *s)
{
	 int length;

	for (length = 0; *s != '\0'; s++)
	{
	length++;
	}
	return (length);
}

/**
 * _strchr - Locate character in string
 * @s: The string to search
 * @c: The character to find
 * Return: Pointer to the first occurrence of character c in string s,
 * or NULL if the character is not found.
 */

char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * join - join two string
 * @s1: string one
 * @s2: string two
 * Return: the joined string
 */

char *join(char *s1, char *s2)
{
	int size = _strlen(s1) + _strlen(s2);
	char *str = malloc(sizeof(char) * (size + 1));
	int i = 0;
	int j = 0;

	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/**
* ft_substr - finds a substring
* @s: the string in hand
* @start: where to start substring
* @len: the length of the substring
* Return: the substring
*/

char	*ft_substr(char *s, int start, int len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > _strlen(s))
		return (_strdup(""));
	if (start + len > _strlen(s))
		len = _strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/**
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = -1;

	do {
		i++;
		dest[i] = src[i];
	} while (src[i] != '\0');

	return (dest);
}
