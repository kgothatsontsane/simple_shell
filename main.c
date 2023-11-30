#include "simple_shell.h"

/**
 * main - the entry point for my shell program
 * @a_c: the argument count
 * @a_v: the argument vector
 *
 * Return: 0 (Success), 1 (Error).
 */
int main(int a_c, char **a_v)
{
	data_t data[] = {DATA_INIT};
	int f_descriptor = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(f_descriptor)
		: "r"(f_descriptor));

	if (a_c == 2)
	{
		f_descriptor = open(a_v[1], O_RDONLY);
		if (f_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				write_str_to_stderr(a_v[0]);
				write_str_to_stderr(": 0: Can't open ");
				write_str_to_stderr(a_v[1]);
				write_ch_to_stderr('\n');
				write_ch_to_stderr(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readFileDescriptor = f_descriptor;
	}
	init_env_list(data);
	load_cmd_history(data);
	hsh(data, a_v);
	return (EXIT_SUCCESS);
}
