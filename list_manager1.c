#include "simple_shell.h"

/**
 * list_length - returns the length of the linked list.
 * @l_head: pointer to first entry in the list (head).
 *
 * Return: the size of the linked list.
 */
size_t list_length(const list_t *l_head)
{
	size_t size = 0;

	while (l_head)
	{
		l_head = l_head->next;
		size++;
	}
	return (size);
}

/**
 * list_to_arr_strings - returns an array of strings of the list_t->str.
 * @l_head: pointer to head of the list (first entry).
 *
 * Return: array of strings of list_t->str.
 */
char **list_to_arr_strings(list_t *l_head)
{
	list_t *entry = l_head;
	size_t idx = list_length(l_head), jdx;
	char **strings;
	char *str;

	if (!l_head || !idx)
		return (NULL);
	strings = malloc(sizeof(char *) * (idx + 1));
	if (!strings)
		return (NULL);
	for (idx = 0; entry; entry = entry->next, idx++)
	{
		str = malloc(_strlen(entry->str) + 1);
		if (!str)
		{
			for (jdx = 0; jdx < idx; jdx++)
				free(strings[jdx]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, entry->str);
		strings[idx] = str;
	}
	strings[idx] = NULL;
	return (strings);
}

/**
 * display_list - displays the elements of a list_t linked list.
 * @entry: pointer to the first element in the list.
 *
 * Return: number of elements printed (size of list).
 */
size_t display_list(const list_t *entry)
{
	size_t size = 0;

	while (entry)
	{
		_puts(number_to_string(entry->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(entry->str ? entry->str : "(nil)");
		_puts("\n");
		entry = entry->next;
		size++;
	}
	return (size);
}

/**
 * entry_starts_with - returns an entry whose string starts with a prefix.
 * @entry: pointer to l_head of the list.
 * @str_prefix: the string prefix which to match.
 * @ch: the next character after str_prefix to match.
 *
 * Return: matching entry with str_prefix or NULL.
 */
list_t *entry_starts_with(list_t *entry, char *str_prefix, char ch)
{
	char *position = NULL;

	while (entry)
	{
		position = begins_with(entry->str, str_prefix);
		if (position && ((ch == -1) || (*position == ch)))
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

/**
 * get_entry_index - gets the index of a entry.
 * @l_head: pointer to the l_head of the list.
 * @entry: pointer to the first entry in the list.
 *
 * Return: the index of the entry or -1 for failure.
 */
ssize_t get_entry_index(list_t *l_head, list_t *entry)
{
	size_t idx = 0;

	while (l_head)
	{
		if (l_head == entry)
			return (idx);
		l_head = l_head->next;
		idx++;
	}
	return (-1);
}
