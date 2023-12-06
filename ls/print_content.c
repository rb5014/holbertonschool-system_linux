#include "custom_functions.h"

/**
 * print_error - print the error according to errno
 * @entry: entry string
 * @prog_name: name of the program
 *
*/
void print_error(const char *entry, const char *prog_name)
{
	switch (errno)
	{
		case EACCES:
			fprintf(stderr, "%s: cannot open directory %s: ", prog_name, entry);
			perror("");
			break;

		default:
			break;

	}
}

/**
 * print_dir_content - Print the names in lexicographical order.
 * @names: Array of names.
 * @count: Number of names.
 * @dir_path: Path to the directory.
 * @is_mult_args: Boolean saying if there are one or more arguments
 * to display their content appropriately
 */
void print_dir_content(char **names, int count,
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
