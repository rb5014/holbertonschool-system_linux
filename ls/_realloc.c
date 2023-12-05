#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "custom_functions.h"

/**
 * _realloc - Allocate or reallocate memory.
 * @ptr: Pointer to the memory block to reallocate.
 * @size: Size of the memory block.
 *
 * Return: Pointer to the allocated memory.
 */
void *_realloc(void *ptr, size_t size)
{
	void *new_ptr = malloc(size);

	if (new_ptr == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	if (ptr != NULL)
	{
		_memcpy(new_ptr, ptr, size);
		free(ptr);
	}

	return (new_ptr);
}
