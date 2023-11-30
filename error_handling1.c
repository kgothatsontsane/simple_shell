#include "simple_shell.h"

/**
 * parse_str_to_int - parses a string to an integer.
 * @str: the string to be parsed to an integer.
 * Return: the parsed integer if successful, 0 if no valid integer found,
 *         else -1 on error
 */
int parse_str_to_int(char *str)
{
	int idx = 0;
	unsigned long int conversion = 0;

	if (*str == '+')
		str++; /* FIX: why does this make main return 255? */
	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			conversion *= 10;
			conversion += (str[idx] - '0');
			if (conversion > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (conversion);
}

/**
 * reportError - prints an error message to standard error (stderr).
 * @data: the structure holding parameters.
 * @error_string: a string containing the specified error type.
 * Return: this function does not return a value (void).
 */
void reportError(data_t *data, char *error_string)
{
	write_str_to_stderr(data->programFilename);
	write_str_to_stderr(": ");
	printDecimal(data->line_count, STDERR_FILENO);
	write_str_to_stderr(": ");
	write_str_to_stderr(data->arg_vector[0]);
	write_str_to_stderr(": ");
	write_str_to_stderr(error_string);
}

/**
 * printDecimal - prints a decimal number in base 10.
 * @user_input: the user input to be printed.
 * @f_descriptor: the file descriptor to write to.
 * Return: the number of characters that was printed.
 */
int printDecimal(int user_input, int f_descriptor)
{
	int (*__putchar)(char) = _putchar;
	int idx, printed = 0;
	unsigned int abs_value, current;

	if (f_descriptor == STDERR_FILENO)
		__putchar = write_ch_to_stderr;
	if (user_input < 0)
	{
		abs_value = -user_input;
		__putchar('-');
		printed++;
	}
	else
		abs_value = user_input;
	current = abs_value;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (abs_value / idx)
		{
			__putchar('0' + current / idx);
			printed++;
		}
		current %= idx;
	}
	__putchar('0' + current);
	printed++;

	return (printed);
}

/**
 * number_to_string - converts a number to a string.
 * @number: the number to convert.
 * @b: the base for conversion.
 * @flgs: the conversion flags.
 * Return: the converted string.
 */
char *number_to_string(long int number, int b, int flgs)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *string;
	unsigned long num = number;

	if (!(flgs & CONVERT_UNSIGNED) && number < 0)
	{
		num = -number;
		sign = '-';
	}
	arr = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	string = &buffer[49];
	*string = '\0';

	do {
		*--string = arr[num % b];
		num /= b;
	} while (num != 0);

	if (sign)
		*--string = sign;
	return (string);
}

/**
 * stripComments - replaces the '#' comments with '\0'
 * @buffer: address of the buffer with string to modify
 *
 * Return: this function does not return a value (void)
 */
void stripComments(char *buffer)
{
	int idx;

	for (idx = 0; buffer[idx] != '\0'; idx++)
		if (buffer[idx] == '#' && (!idx || buffer[idx - 1] == ' '))
		{
			buffer[idx] = '\0';
			break;
		}
}
