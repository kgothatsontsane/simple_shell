#include "simple_shell.h"

/**
 * _my_history - displays the command history with line numbers.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int _my_history(data_t *data)
{
	display_list(data->historyEntries);
	return (0);
}

/**
 * alias_unset - removes an alias associated with a string.
 * @data: the structure holding parameters.
 * @str: the string representing the alias.
 * Return: 0 (Success), 1 (Error).
 */
int alias_unset(data_t *data, char *str)
{
	char *position, ch;
	int unset;

	position = _strchr(str, '=');
	if (!position)
		return (1);
	ch = *position;
	*position = 0;
	unset = delete_entry_at_index(&(data->alias),
		get_entry_index(data->alias, entry_starts_with(data->alias, str, -1)));
	*position = ch;
	return (unset);
}

/**
 * alias_set - associates an alias with a string.
 * @data: the structure holding parameters.
 * @str: the string representing the alias.
 * Return: 0 (Success), 1 (Error).
 */
int alias_set(data_t *data, char *str)
{
	char *position;

	position = _strchr(str, '=');
	if (!position)
		return (1);
	if (!*++position)
		return (alias_unset(data, str));

	alias_unset(data, str);
	return (add_entry_end(&(data->alias), str, 0) == NULL);
}

/**
 * alias_print - prints an alias along with its associated string.
 * @entry: the alias entry containing the alias and its string.
 * Return: 0 (Success), 1 (Error).
 */
int alias_print(list_t *entry)
{
	char *position = NULL, *a = NULL;

	if (entry)
	{
		position = _strchr(entry->str, '=');
		for (a = entry->str; a <= position; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - manages shell aliases, allowing definition and display.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int _my_alias(data_t *data)
{
	int idx = 0;
	char *position = NULL;
	list_t *entry = NULL;

	if (data->arg_count == 1)
	{
		entry = data->alias;
		while (entry)
		{
			alias_print(entry);
			entry = entry->next;
		}
		return (0);
	}
	for (idx = 1; data->arg_vector[idx]; idx++)
	{
		position = _strchr(data->arg_vector[idx], '=');
		if (position)
			alias_set(data, data->arg_vector[idx]);
		else
			alias_print(entry_starts_with(data->alias, data->arg_vector[idx], '='));
	}

	return (0);
}
