#include "main.h"
/**
 * print_long_listing_format - print files in long listing format
 * @file_array: array of files to print
 * @nb: nb of elements in the array
*/
void print_long_listing_format(FileArg *file_array, int nb)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		printf("%s\n", file_array[i].name);
	}
}

/**
 * print_one_by_line - print files one by line
 * @file_array: array of files to print
 * @nb: nb of elements in the array
*/
void print_one_by_line(FileArg *file_array, int nb)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		printf("%s\n", file_array[i].name);

	}
}

/**
 * print_no_opt - print normal without options
 * @file_array: array of files to print
 * @nb: nb of elements in the array
*/
void print_no_opt(FileArg *file_array, int nb)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		printf("%s  ", file_array[i].name);

	}
	printf("\n");
}

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
	if (options.long_listing_format == true)
		print_long_listing_format(file_array, nb);
	else if (options.one_by_line == true)
		print_one_by_line(file_array, nb);
	else
		print_no_opt(file_array, nb);
}

/**
 * print_directories - Print each files/directories of a dir_array
 * @dir_array: Array of dirs to print
 * @nb_dir: Number of elements in that array
 * @nb_reg: Number of elements in reg_array, to know if we have to add
 * a newline between the two arrays
 * @options: Options struct containing the printing options
 * @mult_dirs: If true, then more than one dir is present in the arguments
*/
void print_directories(FileArg *dir_array, int nb_dir,
					   int nb_reg, Options options, bool mult_dirs)
{
	int i;

	for (i = 0; i < nb_dir; i++)
	{
		if ((i > 0) || (nb_reg > 0))
			printf("\n");
		if (mult_dirs == true)
			printf("%s:\n", dir_array[i].name);
		print_files(dir_array[i].elements, dir_array[i].nb_elem, options);
	}
}
