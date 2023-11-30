#include "simple_shell.h"

/**
 * isInteractiveShell - determines if the shell is in the interactive mode.
 * @data: the structure holding parameters.
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int isInteractiveShell(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readFileDescriptor <= 2);
}

/**
 * isDelimiter - determines whether a character is a delimeter.
 * @ch: the character to be checked.
 * @dlm: the delimiter string to compare against.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int isDelimiter(char ch, char *dlm)
{
	while (*dlm)
		if (*dlm++ == ch)
			return (1);
	return (0);
}

/**
 * isAlphabetic - determines whether a character is alphabetic.
 * @ch: the character to be checked.
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */

int isAlphabetic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_to_int - converts a string containing numbers to an integer.
 * @str: the string to be converted.
 * Return: the converted integer or 0 if no numbers are found.
 */
int str_to_int(char *str)
{
	int idx, sign = 1, flg = 0, converted;
	unsigned int calculation = 0;

	for (idx = 0; str[idx] != '\0' && flg != 2; idx++)
	{
		if (str[idx] == '-')
			sign *= -1;

		if (str[idx] >= '0' && str[idx] <= '9')
		{
			flg = 1;
			calculation *= 10;
			calculation += (str[idx] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sign == -1)
		converted = -calculation;
	else
		converted = calculation;

	return (converted);
}
