#include "main.h"

/**
 * free_array - Free memory allocated for an array of strings.
 * @array: Pointer to the array of strings to be freed.
 * @num: Number of elements in the array.
 *
 * This function frees the memory allocated for each string in the array and
 * then frees the memory allocated for the array itself. It checks for NULL
 * pointers to avoid issues with already freed or uninitialized memory.
 *
 * @array: Pointer to the array of strings.
 * @num: Number of elements in the array.
 */
void free_array(char ***array, Elf32_Half num)
{
	Elf32_Half i;

	if (!array)
		return;
	for (i = 0; i < num; i++)
	{
		if ((*array)[i])
			free((*array)[i]);
	}
	free(*array);
}
