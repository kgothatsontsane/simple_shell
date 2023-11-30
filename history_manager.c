#include "simple_shell.h"

/**
 * get_history_f_path - retrieves the filepath to the history file.
 * @data: the structure holding parameters.
 * Return: a  string containing the path to the history file
 *         or NULL if the path cannot be determined.
 */
char *get_history_f_path(data_t *data)
{
	char *buffer, *f_path;

	f_path = _get_env(data, "HOME=");
	if (!f_path)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(f_path) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, f_path);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * save_cmd_history - saves the command history to a file
 *                    or appends an existing one.
 * @data: the structure holding parameters.
 * Return: 1 if the operation is successful, -1 on failure.
 */
int save_cmd_history(data_t *data)
{
	ssize_t f_descriptor;
	char *f_name = get_history_f_path(data);
	list_t *entry = NULL;

	if (!f_name)
		return (-1);

	f_descriptor = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (f_descriptor == -1)
		return (-1);
	for (entry = data->historyEntries; entry; entry = entry->next)
	{
		write_str_to_fd(entry->str, f_descriptor);
		write_ch_to_fd('\n', f_descriptor);
	}
	write_ch_to_fd(BUFFER_FLUSH, f_descriptor);
	close(f_descriptor);
	return (1);
}

/**
 * load_cmd_history - Reads command history from a file
 *                    and populates the history linked list.
 * @data: the structure holding parameters.
 * Return: the number of history entries read on success, 0 otherwise.
 */
int load_cmd_history(data_t *data)
{
	int idx, lst = 0, line_count = 0;
	ssize_t f_descriptor, rd_length, f_size = 0;
	struct stat fileStat;
	char *buffer = NULL, *f_name = get_history_f_path(data);

	if (!f_name)
		return (0);

	f_descriptor = open(f_name, O_RDONLY);
	free(f_name);
	if (f_descriptor == -1)
		return (0);
	if (!fstat(f_descriptor, &fileStat))
		f_size = fileStat.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	rd_length = read(f_descriptor, buffer, f_size);
	buffer[f_size] = 0;
	if (rd_length <= 0)
		return (free(buffer), 0);
	close(f_descriptor);
	for (idx = 0; idx < f_size; idx++)
		if (buffer[idx] == '\n')
		{
			buffer[idx] = 0;
			add_history_entry(data, buffer + lst, line_count++);
			lst = idx + 1;
		}
	if (lst != idx)
		add_history_entry(data, buffer + lst, line_count++);
	free(buffer);
	data->historyLineCount = line_count;
	while (data->historyLineCount-- >= HISTORY_MAX)
		delete_entry_at_index(&(data->historyEntries), 0);
	sort_history(data);
	return (data->historyLineCount);
}

/**
 * add_history_entry - adds a new entry to the history linked list.
 * @data: the structure holding parameters.
 * @command: the command to add to the history.
 * @line_number: the line number of the history entry.
 * Return: 0 (Always).
 */
int add_history_entry(data_t *data, char *command, int line_number)
{
	list_t *entry = NULL;

	if (data->historyEntries)
		entry = data->historyEntries;
	add_entry_end(&entry, command, line_number);

	if (!data->historyEntries)
		data->historyEntries = entry;
	return (0);
}

/**
 * sort_history - sorts the history linked list after changes.
 * @data: the structure holding parameters.
 * Return: the number of entries in the history (new_line_count).
 */
int sort_history(data_t *data)
{
	list_t *entry = data->historyEntries;
	int new_line_count = 0;

	while (entry)
	{
		entry->number = new_line_count++;
		entry = entry->next;
	}
	data->historyLineCount = new_line_count;
	return (new_line_count);
}
