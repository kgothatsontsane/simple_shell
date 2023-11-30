#include "simple_shell.h"

/**
 * _strncpy - copies a portion of one string into another.
 * @destination: the target string where the copy will be placed.
 * @source: the source string from which characters will be copied.
 * @num: the count of characters to be copied.
 * Return: a pointer to the modified target string.
 */
char *_strncpy(char *destination, char *source, int num)
{
	int idx, jdx;

	char *str = destination;

	idx = 0;
	while (source[idx] != '\0' && idx < num - 1)
	{
		destination[idx] = source[idx];
		idx++;
	}
	if (idx < num)
	{
		jdx = idx;
		while (jdx < num)
		{
			destination[jdx] = '\0';
			jdx++;
		}
	}
	return (str);
}

/**
 * _strncat - concatenates two strings up to a specified maximum length.
 * @destination: the target string to which the concatenation will occur.
 * @source: the source string from which characters will be appended.
 * @num: the maximum number of bytes to be utilized for concatenation.
 * Return: a pointer to the resulting concatenated string.
 */
char *_strncat(char *destination, char *source, int num)
{
	int idx, jdx;

	char *str = destination;

	idx = 0;
	jdx = 0;
	while (destination[idx] != '\0')
		idx++;
	while (source[jdx] != '\0' && jdx < num)
	{
		destination[idx] = source[jdx];
		idx++;
		jdx++;
	}
	if (jdx < num)
		destination[idx] = '\0';
	return (str);
}

/**
 * _strchr - finds the first occurrence of a character in a string.
 * @str: the string to search within.
 * @ch: the character to find.
 * Return: pointer to the first occurrence of 'ch' in 'str'
 *         NULL if not found.
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
