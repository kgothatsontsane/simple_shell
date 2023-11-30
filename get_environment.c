#include "simple_shell.h"

/**
 * get_env - retrieves a copy of the environment variables.
 * @data: the structure holding parameters.
 * Return: string array of environment variables.
 */
char **get_env(data_t *data)
{
	if (!data->environ || data->environmentChanged)
	{
		data->environ = list_to_arr_strings(data->env);
		data->environmentChanged = 0;
	}

	return (data->environ);
}

/**
 * unset_env - deletes an environment variable.
 * @data: the structure holding parameters.
 * @var_name: the name of the environment variable to delete.
 * Return: 1 if the variable is successfully deleted
 *         0 if it's not found.
 */
int unset_env(data_t *data, char *var_name)
{
	list_t *entry = data->env;
	size_t idx = 0;
	char *position;

	if (!entry || !var_name)
		return (0);

	while (entry)
	{
		position = begins_with(entry->str, var_name);
		if (position && *position == '=')
		{
			data->environmentChanged = delete_entry_at_index(&(data->env), idx);
			idx = 0;
			entry = data->env;
			continue;
		}
		entry = entry->next;
		idx++;
	}
	return (data->environmentChanged);
}

/**
 * set_env - creates or updates an environment variable.
 * @data: the structure holding parameters.
 * @var_name: the name of the environment variable.
 * @var_value: the value to assign to the environment variable.
 * Return: 0 on success, 1 on error.
 */
int set_env(data_t *data, char *var_name, char *var_value)
{
	char *buffer = NULL;
	list_t *entry;
	char *position;

	if (!var_name || !var_value)
		return (0);

	buffer = malloc(_strlen(var_name) + _strlen(var_value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var_name);
	_strcat(buffer, "=");
	_strcat(buffer, var_value);
	entry = data->env;
	while (entry)
	{
		position = begins_with(entry->str, var_name);
		if (position && *position == '=')
		{
			free(entry->str);
			entry->str = buffer;
			data->environmentChanged = 1;
			return (0);
		}
		entry = entry->next;
	}
	add_entry_end(&(data->env), buffer, 0);
	free(buffer);
	data->environmentChanged = 1;
	return (0);
}
