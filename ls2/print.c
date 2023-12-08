#include "main.h"
/**
 * print_files - Print each files/directories of a dir_array
 * @file_array: Array of files entries to print
 * @nb: Number of elements in that array
 * @options: Options struct containing the printing options
 *
 * It can either print the files that are arguments of the program,
 * or the entries found in the directories.
*/
void print_files(FileArg *file_array, int nb, Options options)
{
	int i;

	options = options;

	for (i = 0; i < nb; i++)
	{
		printf("%s  ", file_array[i].name);
	}
	printf("\n");
}

/**
 * print_directories - Print each files/directories of a dir_array
 * @dir_array: Array of dirs to print
 * @nb_dir: Number of elements in that array
 * @options: Options struct containing the printing options
*/
void print_directories(FileArg *dir_array, int nb_dir, Options options)
{
	if (nb_dir == 1)
	{
		print_files(dir_array[0].elements, dir_array[0].nb_elem, options);
	}
	else
	{
		int i;

		for (i = 0; i < nb_dir; i++)
		{
			if (i > 0)
				printf("\n");
			printf("%s:\n", dir_array[i].name);
			print_files(dir_array[i].elements, dir_array[i].nb_elem, options);
		}
	}
}
