#include "simple_shell.h"

/**
 * reset_data - resets an data_t struct to its initial state.
 * @data: the structure holding parameters.
 * Return: this function does not return a value (void).
 */
void reset_data(data_t *data)
{
	data->argument = NULL;
	data->arg_vector = NULL;
	data->path = NULL;
	data->arg_count = 0;
}

/**
 * init_data - initialises an data_t struct with command-line arguments.
 * @data: the structure holding parameters.
 * @arg_vector: the argument vector containing command-line arguments.
 * Return: this function does not return a value (void).
 */
void init_data(data_t *data, char **arg_vector)
{
	int idx = 0;

	data->programFilename = arg_vector[0];
	if (data->argument)
	{
		data->arg_vector = strTokenize(data->argument, " \t");
		if (!data->arg_vector)
		{
			data->arg_vector = malloc(sizeof(char *) * 2);
			if (data->arg_vector)
			{
				data->arg_vector[0] = _strdup(data->argument);
				data->arg_vector[1] = NULL;
			}
		}
		for (idx = 0; data->arg_vector && data->arg_vector[idx]; idx++)
			;
		data->arg_count = idx;

		replaceAlias(data);
		replaceVars(data);
	}
}

/**
 * free_data - deallocates memory used by fields in the data_t struct.
 * @data: the structure holding parameters.
 * @free_all: true if freeing all fields (1), false otherwise(0).
 * Return: this function does not return a value (void).
 */
void free_data(data_t *data, int free_all)
{
	freeStringArray(data->arg_vector);
	data->arg_vector = NULL;
	data->path = NULL;
	if (free_all)
	{
		if (!data->commandBuffer)
			free(data->argument);
		if (data->env)
			reset_list(&(data->env));
		if (data->historyEntries)
			reset_list(&(data->historyEntries));
		if (data->alias)
			reset_list(&(data->alias));
		freeStringArray(data->environ);
			data->environ = NULL;
		free_ptr((void **)data->commandBuffer);
		if (data->readFileDescriptor > 2)
			close(data->readFileDescriptor);
		_putchar(BUFFER_FLUSH);
	}
}
