#include <stdlib.h>
#include <stdio.h>
#include "custom_functions.h"

/**
 * compare_names - Compare two strings.
 * @a: First string.
 * @b: Second string.
 *
 * Return: 0 if strings are equal, positive if the first non-matching character
 * in a is greater than that of b, negative otherwise.
 */
int compare_names(const void *a, const void *b)
{
	return (_strcmp_icase(*(const char **)a, *(const char **)b));
}

/**
 * print_sorted_names - Print the names in lexicographical order.
 * @names: Array of names.
 * @count: Number of names.
 * @dir_path: Path to the directory.
 * @is_mult_dirs: Boolean saying if theresone or more directories
 * to display their content appropriately
 */
void print_sorted_names(char **names, int count,
						const char *dir_path, bool is_mult_dirs)
{
	int i;

	_qsort(names, count, sizeof(char *), compare_names);

	if (is_mult_dirs == true)
	{
		printf("%s:\n", dir_path);
	}

	for (i = 0; i < count; i++)
	{
		printf("%s  ", names[i]);
		free(names[i]);
	}
	free(names);
	printf("\n");
}
