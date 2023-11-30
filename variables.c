#include "simple_shell.h"
/**
 * isCmdSep - checks if current character in text is a command separator
 * @data: the structure holding parameters.
 * @buffer: the character buffer being analyzed
 * @position: the current position within the text
 * Return: 1 if it's a separator, 0 otherwise
 */
int isCmdSep(data_t *data, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->commandBufferType = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->commandBufferType = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of command */
	{
		buffer[j] = 0; /* replace ";" with NULL */
		data->commandBufferType = CMD_CHAIN;
	}
	else
		return (0);

	*position = j;
	return (1);
}

/**
 * checkStatus - checks we should continue chaining based on last status
 * @data: the structure holding parameters.
 * @buffer: the character buffer being cheked
 * @position: the current position within the text
 * @start: the starting position in the buffer
 * @b_length: the length of the buffer
 *
 * Return:  this function does not return a value (void)
 */
void checkStatus(data_t *data, char *buffer, size_t *position,
	size_t start, size_t b_length)
{
	size_t j = *position;

	if (data->commandBufferType == CMD_AND)
	{
		if (data->returnStatus)
		{
			buffer[start] = 0;
			j = b_length;
		}
	}
	if (data->commandBufferType == CMD_OR)
	{
		if (!data->returnStatus)
		{
			buffer[start] = 0;
			j = b_length;
		}
	}
	*position = j;
}

/**
 * replaceAlias - updates an alias in the tokenized string
 * @data: the structure holding parameters.
 *
 * Return: 1 if updated, 0 otherwise
 */
int replaceAlias(data_t *data)
{
	int i;
	list_t *entry;
	char *position;

	for (i = 0; i < 10; i++)
	{
		entry = entry_starts_with(data->alias, data->arg_vector[0], '=');

		if (!entry)
			return (0);

		free(data->arg_vector[0]);
		position = _strchr(entry->str, '=');

		if (!position)
			return (0);
		position = _strdup(position + 1);

		if (!position)
			return (0);
		data->arg_vector[0] = position;
	}
	return (1);
}

/**
 * replaceVars - updates vars in the tokenized string
 * @data: the structure holding parameters.
 *
 * Return: 1 if updated, 0 otherwise
 */
int replaceVars(data_t *data)
{
	int i = 0;
	list_t *entry;

	for (i = 0; data->arg_vector[i]; i++)
	{
		if (data->arg_vector[i][0] != '$' || !data->arg_vector[i][1])
			continue;
		if (!_strcmp(data->arg_vector[i], "$?"))
		{
			replaceStr(&(data->arg_vector[i]),
				       _strdup(number_to_string(data->returnStatus, 10, 0)));
			continue;
		}
		if (!_strcmp(data->arg_vector[i], "$$"))
		{
			replaceStr(&(data->arg_vector[i]),
				       _strdup(number_to_string(getpid(), 10, 0)));
			continue;
		}
		entry = entry_starts_with(data->env, &data->arg_vector[i][1], '=');
		if (entry)
		{
			replaceStr(&(data->arg_vector[i]),
				       _strdup(_strchr(entry->str, '=') + 1));
			continue;
		}
		replaceStr(&data->arg_vector[i], _strdup(""));
	}
	return (0);
}
/**
 * replaceStr - replaces oldString with newString.
 * @oldString: the address of the old string content.
 * @newString: the new string content to replace the old one.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceStr(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}
