#include "simple_shell.h"

/**
 * read_and_buffer_input - reads and buffers input from the standard input.
 * @data: the structure holding parameters.
 * @buffer: address of the buffer to store the input.
 * @b_length: Address of the variable storing the buffer length.
 * Return: the number of bytes read (b_rd).
 *
 * This function reads input from the standard input and stores it in a buffer.
 * If there is existing data in the buffer, it will be cleared. The input is
 * read until a newline character is encountered or the buffer is filled.
 * If the input contains a newline character, it is removed from the stored
 * data. The function also handles command chaining and updates the command
 * history.
 */
ssize_t read_and_buffer_input(data_t *data, char **buffer, size_t *b_length)
{
	ssize_t b_rd = 0;
	size_t length_p = 0;

	if (!*b_length) /* if buffer is empty, fill it */
	{
		/*free_ptr((void **)data->commandBuffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_signal);
#if USE_GETLINE
		b_rd = getline(buffer, &length_p, stdin);
#else
		b_rd = get_next_line(data, buffer, &length_p);
#endif
		if (b_rd > 0)
		{
			if ((*buffer)[b_rd - 1] == '\n')
			{
				(*buffer)[b_rd - 1] = '\0';
				b_rd--;
			}
			data->countLineFlag = 1;
			stripComments(*buffer);
			add_history_entry(data, *buffer, data->historyLineCount++);
			/*ANSWER: if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*b_length = b_rd;
				data->commandBuffer = buffer;
			}
		}
	}
	return (b_rd);
}

/**
 * get_user_input - reads a line from input, excluding the newline character.
 * @data: the structure holding parameters.
 * Return: the number of bytes read (b_rd).
 */
ssize_t get_user_input(data_t *data)
{
	static char *buffer; /* the semi-colon command chain buffer */
	static size_t idx, jdx, b_length;
	ssize_t b_rd = 0;
	char **buffer_p = &(data->argument), *position;

	_putchar(BUFFER_FLUSH);
	b_rd = read_and_buffer_input(data, &buffer, &b_length);
	if (b_rd == -1) /* END OF FILE */
		return (-1);
	if (b_length) /* commands left in the chain buffer */
	{
		jdx = idx;       /* init the iterator to current buffer position */
		position = buffer + idx; /* get the pointer for return */

		checkStatus(data, buffer, &jdx, idx, b_length);
		while (jdx < b_length) /* iterate to semi-colon or end */
		{
			if (isCmdSep(data, buffer, &jdx))
				break;
			jdx++;
		}

		idx = jdx + 1;    /* increment past nulled ';'' */
		if (idx >= b_length) /* have we reached the end of buffer? */
		{
			idx = b_length = 0; /* reset position and length */
			data->commandBufferType = CMD_NORMAL;
		}

		*buffer_p = position;/* pass the pointer back to current command position */
		return (_strlen(position)); /* return length of current command */
	}

	*buffer_p = buffer;
	/* not a chain, pass the buffer back from get_next_line() */
	return (b_rd);   /* return length of buffer from get_next_line() */
}

/**
 * read_into_buffer - reads data into a buffer.
 * @data: the structure holding parameters.
 * @buffer: the buffer to store the read data.
 * @sz: the size of the buffer.
 *
 * Return: the number of bytes read (b_rd).
 */
ssize_t read_into_buffer(data_t *data, char *buffer, size_t *sz)
{
	ssize_t b_rd = 0;

	if (*sz)
		return (0);
	b_rd = read(data->readFileDescriptor, buffer, READ_BUFFER_SIZE);
	if (b_rd >= 0)
		*sz = b_rd;
	return (b_rd);
}

/**
 * get_next_line - reads the next line of input from the STANDARD INPUT.
 * @data: the structure holding parameters.
 * @line: the address of a pointer to the buffer, preallocated or NULL.
 * @length: the size of the preallocated line buffer if not NULL.
 *
 * Return: the number of characters read, or -1 on error.
 */
int get_next_line(data_t *data, char **line, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t idx, b_length;
	size_t l_size;
	ssize_t b_rd = 0, c_rd = 0;
	char *position = NULL, *new_line = NULL, *ch;

	position = *line;
	if (position && length)
		c_rd = *length;
	if (idx == b_length)
		idx = b_length = 0;

	b_rd = read_into_buffer(data, buffer, &b_length);
	if (b_rd == -1 || (b_rd == 0 && b_length == 0))
		return (-1);

	ch = _strchr(buffer + idx, '\n');
	l_size = ch ? 1 + (unsigned int)(ch - buffer) : b_length;
	new_line = my_realloc(position, c_rd, c_rd ? c_rd + l_size : l_size + 1);
	if (!new_line) /* MEMORY ALLOCATION FAILURE! */
		return (position ? free(position), -1 : -1);

	if (c_rd)
		_strncat(new_line, buffer + idx, l_size - idx);
	else
		_strncpy(new_line, buffer + idx, l_size - idx + 1);

	c_rd += l_size - idx;
	idx = l_size;
	position = new_line;

	if (length)
		*length = c_rd;
	*line = position;
	return (c_rd);
}

/**
 * handle_signal - handles the Ctrl-C signal.
 * @sig_number: the signal number (SIGINT).
 * Return: this function does not return a value (void).
 */
void handle_signal(__attribute__((unused)) int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
