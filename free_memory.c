#include "simple_shell.h"

/**
 * free_ptr - deallocates memory for a pointer and NULLs the address.
 * @ptr: address of the pointer to deallocate memory for.
 * Return: 1 if deallocated, otherwise 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
