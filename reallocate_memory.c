#include "simple_shell.h"

/**
* fillMemory - fills a memory area with a specified byte value.
* @memory: the pointer to the memory area to be filled.
* @b_value: the byte value to fill the memory area with.
* @b_size: the number of bytes to be filled.
* Return: a pointer to the filled memory area.
*/
char *fillMemory(char *memory, char b_value, unsigned int b_size)
{
	unsigned int i;

	for (i = 0; i < b_size; i++)
		memory[i] = b_value;
	return (memory);
}

/**
* freeStringArray - frees a dynamically allocated array of strings.
* @stringArray: the array of strings to be freed.
*/
void freeStringArray(char **stringArray)
{
	char **currentString = stringArray;

	if (!stringArray)
		return;
	while (*stringArray)
		free(*stringArray++);
	free(currentString);
}

/**
* my_realloc - reallocates a block of memory.
* @ptr: pointer to the previously allocated block.
* @oldSize: byte size of the previous block.
* @newSize: byte size of the new block.
*
* Return: pointer to the reallocated block, or NULL on failure.
*/
void *my_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *new_block;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	new_block = malloc(newSize);
	if (!new_block)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		new_block[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (new_block);
}
