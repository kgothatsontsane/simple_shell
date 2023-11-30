#include "simple_shell.h"

/**
 * add_entry - adds a entry to the start of the list.
 * @l_head: address of pointer to the head of the list.
 * @str: the string field of an entry.
 * @e_index: the entry index used by history.
 *
 * Return: a pointer to the new head in the list.
 */
list_t *add_entry(list_t **l_head, const char *str, int e_index)
{
	list_t *new_head;

	if (!l_head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	fillMemory((void *)new_head, 0, sizeof(list_t));
	new_head->number = e_index;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *l_head;
	*l_head = new_head;
	return (new_head);
}

/**
 * add_entry_end - adds a entry to the end of the list.
 * @l_head: double pointer to head of the linked list.
 * @str: the str field of an entry.
 * @e_index: the entry index used by history.
 *
 * Return: a pointer to the new entry in the list.
 */
list_t *add_entry_end(list_t **l_head, const char *str, int e_index)
{
	list_t *new_entry, *entry;

	if (!l_head)
		return (NULL);

	entry = *l_head;
	new_entry = malloc(sizeof(list_t));
	if (!new_entry)
		return (NULL);
	fillMemory((void *)new_entry, 0, sizeof(list_t));
	new_entry->number = e_index;
	if (str)
	{
		new_entry->str = _strdup(str);
		if (!new_entry->str)
		{
			free(new_entry);
			return (NULL);
		}
	}
	if (entry)
	{
		while (entry->next)
			entry = entry->next;
		entry->next = new_entry;
	}
	else
		*l_head = new_entry;
	return (new_entry);
}

/**
 * print_str_list - prints only the str element of a list_t linked-list.
 * @l_head: a pointer to first entry of the list_t linked-list.
 * Return: the size of the linked list.
 */
size_t print_str_list(const list_t *l_head)
{
	size_t size = 0;

	while (l_head)
	{
		_puts(l_head->str ? l_head->str : "(nil)");
		_puts("\n");
		l_head = l_head->next;
		size++;
	}
	return (size);
}

/**
 * delete_entry_at_index - removes the entry at given index.
 * @l_head: address of the pointer to first entry.
 * @index: index of the entry to delete.
 * Return: 1 on success, 0 on failure.
 */
int delete_entry_at_index(list_t **l_head, unsigned int index)
{
	list_t *entry, *prev_entry;
	unsigned int size = 0;

	if (!l_head || !*l_head)
		return (0);

	if (!index)
	{
		entry = *l_head;
		*l_head = (*l_head)->next;
		free(entry->str);
		free(entry);
		return (1);
	}
	entry = *l_head;
	while (entry)
	{
		if (size == index)
		{
			prev_entry->next = entry->next;
			free(entry->str);
			free(entry);
			return (1);
		}
		size++;
		prev_entry = entry;
		entry = entry->next;
	}
	return (0);
}

/**
 * reset_list - frees all entrys of a list_t linked list.
 * @head_ptr: address of pointer to the of the head of the list.
 * Return: this function does not return a value (void).
 */
void reset_list(list_t **head_ptr)
{
	list_t *entry, *next_entry, *l_head;

	if (!head_ptr || !*head_ptr)
		return;
	l_head = *head_ptr;
	entry = l_head;
	while (entry)
	{
		next_entry = entry->next;
		free(entry->str);
		free(entry);
		entry = next_entry;
	}
	*head_ptr = NULL;
}
