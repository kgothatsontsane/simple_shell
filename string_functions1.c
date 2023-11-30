#include "simple_shell.h"

/**
 * _strcpy - copies the contents of one string to another one.
 * @destination: the destination string where the content will be copied.
 * @source: the source string from which content will be copied.
 *
 * Return: returns a pointer to the copied string.
 */
char *_strcpy(char *destination, char *source)

{int idx = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[idx])
	{
		destination[idx] = source[idx];
		idx++;
	}
	destination[idx] = 0;
	return (destination);
}

/**
 * _strdup - duplicates a string.
 * @str: the string to be duplicated.
 *
 * Return: a pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;

	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	dup = malloc(sizeof(char) * (length + 1));
	if (!dup)
		return (NULL);
	for (length++; length--;)
		dup[length] = *--str;
	return (dup);
}

/**
 * _puts - prints a string to the standard-output.
 * @str: the string to be printed.
 *
 * Return: this function has no return value (void).
 */
void _puts(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		_putchar(str[idx]);
		idx++;
	}
}

/**
 * _putchar - prints a character to the standard-output.
 * @ch: Tthe string to be printed.
 *
 * Return:  1 (Success)
 */
int _putchar(char ch)
{
	static int idx;

	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, idx);
		idx = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[idx++] = ch;
	return (1);
}
