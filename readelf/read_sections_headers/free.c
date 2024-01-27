#include "read_sections_headers.h"

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