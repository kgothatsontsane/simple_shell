#include "simple_shell.h"

/**
 * is_exec_cmd - checks whether a file is an executable command.
 * @data: the structure holding parameters.
 * @f_path: the path to the file to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise
 */
int is_exec_cmd(data_t *data, char *f_path)
{
	struct stat fileStat;

	(void)data; /* Unused parameter */
	if (!f_path || stat(f_path, &fileStat) != 0)
		return (0);

	/* Check if the file is a regular file and has execute permission */
	if (S_ISREG(fileStat.st_mode) && (fileStat.st_mode & S_IXUSR))
		return (1);

	return (0);
}

/**
 * extract_substring - extracts a substring from a given string.
 * @str_path: the path of the original string.
 * @start_idx: the starting index.
 * @stop_idx: the stopping index.
 *
 * Return: pointer to a new buffer containing the duplicated characters.
 */
char *extract_substring(char *str_path, int start_idx, int stop_idx)
{
	static char buffer[1024];
	int source_idx = 0, dest_idx = 0;

	for (source_idx = start_idx; source_idx < stop_idx; source_idx++)
		if (str_path[source_idx] != ':')
			buffer[dest_idx++] = str_path[source_idx];
	buffer[dest_idx] = 0;
	return (buffer);
}

/**
 * find_exec_path - locates an executable in the specified paths.
 * @data: the structure holding parameters.
 * @search_paths: the paths to search in.
 * @command: the command to find.
 *
 * Return: full path of the command if found, or NULL.
 */
char *find_exec_path(data_t *data, char *search_paths, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!search_paths)
		return (NULL);
	if ((_strlen(command) > 2) && begins_with(command, "./"))
	{
		if (is_exec_cmd(data, command))
			return (command);
	}
	while (1)
	{
		if (!search_paths[i] || search_paths[i] == ':')
		{
			path = extract_substring(search_paths, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_exec_cmd(data, path))
				return (path);
			if (!search_paths[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
