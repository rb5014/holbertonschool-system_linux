#include "custom_functions.h"


/**
 * print_sorted_names - Print the names in lexicographical order.
 * @names: Array of names.
 * @count: Number of names.
 * @dir_path: Path to the directory.
 * @is_mult_args: Boolean saying if there are one or more arguments
 * to display their content appropriately
 */
void print_sorted_names(char **names, int count,
						const char *dir_path, bool is_mult_args)
{
	int i;

	/*  _qsort(names, count, sizeof(char *), compare_names); */

	if (is_mult_args == true)
	{
		printf("%s:\n", dir_path);
	}

	for (i = 0; i < count; i++)
	{
		printf("%s  ", names[i]);
		free(names[i]);
	}
	printf("\n");
	free(names);
}
