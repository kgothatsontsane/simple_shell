#include "simple_shell.h"

/**
 * _strlen - returns the length of a string.
 * @str: the string whose length to check.
 *
 * Return: the length of the string.
 */
int _strlen(char *str)
{
	int s_length = 0;

	if (!str)
		return (0);

	while (*str++)
		s_length++;
	return (s_length);
}

/**
 * _strcmp - compares two strings lexicographically
 * @str1: the first string to be compared.
 * @str2: the second string to be compared.
 *
 * Return: negative if str1 < str2,
 *         positive if str1 > str2, zero if str1 == str2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - determines if a string begins with a specified prefix.
 * @string: the string to search within.
 * @prefix: the prefix to check for at the beginning of the string.
 *
 * Return: pointer to the next character after the found prefix
 *         or NULL if not found.
 */
char *begins_with(const char *string, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *string++)
			return (NULL);
	return ((char *)string);
}

/**
 * _strcat - concatenates two strings.
 * @destination: the destination buffer.
 * @source: the source buffer.
 *
 * Return: the pointer to the destination buffer.
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
