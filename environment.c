#include "simple_shell.h"

/**
 * _my_env - displays the current environment variables of the shell.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int _my_env(data_t *data)
{
	print_str_list(data->env);
	return (0);
}

/**
 * _get_env - retrieves the value of an environment variable.
 * @data: the structure holding parameters.
 * @var: the name of the environment variable.
 *
 * Return: the value of the specified environment variable
 * or NULL if not found.
 */
char *_get_env(data_t *data, const char *var)
{
	list_t *entry = data->env;
	char *position;

	while (entry)
	{
		position = begins_with(entry->str, var);
		if (position && *position)
			return (position);
		entry = entry->next;
	}
	return (NULL);
}

/**
 * _my_set_env - sets or modifies an environment variable.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int _my_set_env(data_t *data)
{
	if (data->arg_count != 3)
	{
		write_str_to_stderr("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(data, data->arg_vector[1], data->arg_vector[2]))
		return (0);
	return (1);
}

/**
 * _my_unset_env - unsets (deletes) an environment variable.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int _my_unset_env(data_t *data)
{
	int idx;

	if (data->arg_count == 1)
	{
		write_str_to_stderr("Too few arguements.\n");
		return (1);
	}
	for (idx = 1; idx <= data->arg_count; idx++)
		unset_env(data, data->arg_vector[idx]);

	return (0);
}

/**
 * init_env_list - creates and fills the environment linked list.
 * @data: the structure holding parameters.
 * Return: 0 (Always).
 */
int init_env_list(data_t *data)
{
	list_t *entry = NULL;
	size_t idx;

	for (idx = 0; environ[idx]; idx++)
		add_entry_end(&entry, environ[idx], 0);
	data->env = entry;
	return (0);
}
