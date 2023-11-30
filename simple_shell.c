#include "simple_shell.h"

/**
 * hsh - my main custom shell loop.
 * @data: the structure holding parameters.
 * @a_v: the argument vector from the main() function.
 *
 * Return: 0 (success), 1 (error), or err_code.
 */
int hsh(data_t *data, char **a_v)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reset_data(data);
		if (isInteractiveShell(data))
			_puts("$ ");
		write_ch_to_stderr(BUFFER_FLUSH);
		r = get_user_input(data);
		if (r != -1)
		{
			init_data(data, a_v);
			builtin_ret = searchBuiltIn(data);
			if (builtin_ret == -1)
				searchCommand(data);
		}
		else if (isInteractiveShell(data))
			_putchar('\n');
		free_data(data, 0);
	}
	save_cmd_history(data);
	free_data(data, 1);
	if (!isInteractiveShell(data) && data->returnStatus)
		exit(data->returnStatus);
	if (builtin_ret == -2)
	{
		if (data->errorCode == -1)
			exit(data->returnStatus);
		exit(data->errorCode);
	}
	return (builtin_ret);
}

/**
 * searchBuiltIn - searches for a builtin command.
 * @data: the structure holding parameters.
 *
 * Return: -1 when builtin is not found
 *         0 when builtin is executed successfully
 *         1 when builtin is found but not executed successful
 *         2 when builtin signals the exit() command
 */
int searchBuiltIn(data_t *data)
{
	int idx, b_status = -1;
	builtin_table b_tbl[] = {
	    {"exit", _my_exit},
	    {"env", _my_env},
	    {"help", _my_help},
	    {"history", _my_history},
	    {"setenv", _my_set_env},
	    {"unsetenv", _my_unset_env},
	    {"cd", _my_cd},
	    {"alias", _my_alias},
	    {NULL, NULL}};

	for (idx = 0; b_tbl[idx].type; idx++)
		if (_strcmp(data->arg_vector[0], b_tbl[idx].type) == 0)
		{
			data->line_count++;
			b_status = b_tbl[idx].func(data);
			break;
		}
	return (b_status);
}

/**
 * searchCommand - searches for a command in the PATH environment.
 * @data: the structure holding parameters.
 *
 * Return: this function does not return a value (void).
 */
void searchCommand(data_t *data)
{
	char *path = NULL;
	int idx, kdx;

	data->path = data->arg_vector[0];
	if (data->countLineFlag == 1)
	{
		data->line_count++;
		data->countLineFlag = 0;
	}
	for (idx = 0, kdx = 0; data->argument[idx]; idx++)
		if (!isDelimiter(data->argument[idx], " \t\n"))
			kdx++;
	if (!kdx)
		return;

	path = find_exec_path(data, _get_env(data, "PATH="), data->arg_vector[0]);
	if (path)
	{
		data->path = path;
		exec_cmd_in_child(data);
	}
	else
	{
		if ((isInteractiveShell(data) || _get_env(data, "PATH=") || data->arg_vector[0][0] == '/')
		&& is_exec_cmd(data, data->arg_vector[0]))
			exec_cmd_in_child(data);
		else if (*(data->argument) != '\n')
		{
			data->returnStatus = 127;
			reportError(data, "not found\n");
		}
	}
}

/**
 * exec_cmd_in_child - forks a child process to execute a command.
 * @data: the structure holding parameters.
 *
 * Return: this function does not return a value (void)
 */
void exec_cmd_in_child(data_t *data)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (child_process_id == -1)
	{
		perror("Error:");
		return;
	}
	if (child_process_id == 0)
	{
		if (execve(data->path, data->arg_vector, get_env(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->returnStatus));
		if (WIFEXITED(data->returnStatus))
		{
			data->returnStatus = WEXITSTATUS(data->returnStatus);
			if (data->returnStatus == 126)
				reportError(data, "Permission denied\n");
		}
	}
}
