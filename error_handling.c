#include "simple_shell.h"

/**
 * write_str_to_stderr - writes a string to the standard error stream.
 * @str: the string to be printed to (stderr).
 * Return: this function does not return a value (void).
 */
void write_str_to_stderr(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		write_ch_to_stderr(str[idx]);
		idx++;
	}
}

/**
 * write_ch_to_stderr - writes a character to the (stderr) with buffering.
 * @ch: The character to write to (stderr).
 * Return: 1 on success, -1 on error (with error number set).
 */
int write_ch_to_stderr(char ch)
{
	static int idx;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, idx);
		idx = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[idx++] = ch;
	return (1);
}

/**
 * write_ch_to_fd - writes a character to a file descriptor using buffering.
 * @ch: The character to write to the file descriptor.
 * @f_descriptor: The filedescriptor to write to.
 * Return: - 1 on success, -1 on error with errno set accordingly.
 */
int write_ch_to_fd(char ch, int f_descriptor)
{
	static int idx;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(f_descriptor, buffer, idx);
		idx = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[idx++] = ch;
	return (1);
}

/**
 * write_str_to_fd - writes a string to a specified file descriptor.
 * @str: the string to print to the file descriptor.
 * @f_descriptor: the filedescriptor to write to.
 * Return: the number of characters printed.
 */
int write_str_to_fd(char *str, int f_descriptor)
{
	int idx = 0;

	if (!str)
		return (0);
	while (*str)
	{
		idx += write_ch_to_fd(*str++, f_descriptor);
	}
	return (idx);
}
