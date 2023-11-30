#include "simple_shell.h"

/**
 * _my_exit - exits the shell with a specified exit status.
 * @data: the structure holding parameters.
 * Return: exit status else 0 if data.arg_vector[0] is not "exit".
 */
int _my_exit(data_t *data)
{
	int check_exit;

	if (data->arg_vector[1]) /* there exists an exit argument */
	{
		check_exit = parse_str_to_int(data->arg_vector[1]);
		if (check_exit == -1)
		{
			data->returnStatus = 2;
			reportError(data, "Illegal number: ");
			write_str_to_stderr(data->arg_vector[1]);
			write_ch_to_stderr('\n');
			return (1);
		}
		data->errorCode = parse_str_to_int(data->arg_vector[1]);
		return (-2);
	}
	data->errorCode = -1;
	return (-2);
}

/**
 * _my_cd - changes the current working directory of the process.
 * @data: the structure holding parameters.
 * Return: 0 (Always)
 */
int _my_cd(data_t *data)
{
	char *str, *new_dir, buffer[1024];
	int chdir_res;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("FIX: >>getcwd failure emsg here<<\n");
	if (!data->arg_vector[1])
	{
		new_dir = _get_env(data, "HOME=");
		if (!new_dir)
			chdir_res =
				chdir((new_dir = _get_env(data, "PWD=")) ? new_dir : "/");
		else
			chdir_res = chdir(new_dir);
	}
	else if (_strcmp(data->arg_vector[1], "-") == 0)
	{
		if (!_get_env(data, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(data, "OLDPWD=")), _putchar('\n');
		chdir_res =
			chdir((new_dir = _get_env(data, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_res = chdir(data->arg_vector[1]);
	if (chdir_res == -1)
	{
		reportError(data, "can't cd to ");
		write_str_to_stderr(data->arg_vector[1]), write_ch_to_stderr('\n');
	}
	else
	{
		set_env(data, "OLDPWD", _get_env(data, "PWD="));
		set_env(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - displays help information for the shell.
 * @data: the structure holding parameters.
 * Return: 0 (Always)
 */
int _my_help(data_t *data)
{
	char **arguments;

	arguments = data->arg_vector;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arguments); /* FIX: find workaround */
	return (0);
}
