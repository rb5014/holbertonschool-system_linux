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
	return (_strcmp(*(const char **)a, *(const char **)b));
}

/**
 * print_sorted_names - Print the names in lexicographical order.
 * @names: Array of names.
 * @count: Number of names.
 */
void print_sorted_names(char **names, int count)
{
	int i;

	_qsort(names, count, sizeof(char *), compare_names);

	for (i = 0; i < count; i++)
	{
		printf("%s\n", names[i]);
		free(names[i]);
	}
	free(names);
}
