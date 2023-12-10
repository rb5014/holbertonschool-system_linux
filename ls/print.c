#include "main.h"

/**
 * print_file - Print current file being processed in print_files
 * @file: FileArg to print
 * @current_index: Current index in the loop of print_files
 * @options: Options for formating
*/
void print_file(FileArg file, int current_index, Options options)
{
	if (options.long_listing_format == true)
	{
		if (current_index > 0)
			printf("\n");
		print_long_listing_format(file);
	}
	else
	{
		if (options.one_by_line == true)
		{
			if (current_index > 0)
				printf("\n");
			printf("%s", file.name);
		}
		else
			printf("%s  ", file.name);
	}
}
/**
 * print_files - Print each files/directories of a dir_array
 * @file_array: Array of files entries to print
 * @nb: Number of elements in that array
 * @options: Options struct containing the printing options
 * @mult_dirs: If true, then more than one dir is present in
 * the elements ( if the file is a dir it has elements)
 * It can either print the files that are arguments of the program,
 * or the entries found in the directories.
*/
void print_files(FileArg *file_array, int nb, Options options, bool mult_dirs)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		print_file(file_array[i], i, options);
	}
	printf("\n");
	for (i = 0; i < nb; i++)
	{
		if ((S_ISDIR(file_array[i].st.st_mode)) && (options.recursive == true))
		{
			if (i < (nb - 1))
				printf("\n");
			print_directory(file_array[i], options, mult_dirs);
		}
	}
}

/**
 * print_directory - Print each files/directories name of a directory
 * @dir: dir to print
 * @options: Options struct containing the printing options
 * @mult_dirs: If true, then more than one dir is present in the arguments
*/
void print_directory(FileArg dir, Options options, bool mult_dirs)
{
	if ((mult_dirs == true) || (options.recursive == true))
		printf("%s:\n", dir.name);
	print_files(dir.elements, dir.nb_elem, options, mult_dirs);
}

/**
 * print_all - Print all the elements
 * @dir_array: Array of dirs
 * @reg_array: Array of regular files to be printed first
 * @nb_dir: Number of elements of dir_array
 * @nb_reg: Number of elements of reg_array
 * @options: Options for printing
 * @mult_dirs: If true, then multiple dirs
 * or mixed file and dir args format activated
 *
*/
void print_all(FileArg *dir_array, FileArg *reg_array, int nb_dir,
			   int nb_reg, Options options, bool mult_dirs)
{
	if (nb_reg > 0)
		print_files(reg_array, nb_reg, options, false);
	if (nb_dir > 0)
	{
		int i;

		if (nb_reg > 0)
			printf("\n");
		for (i = 0; i < nb_dir; i++)
		{
			if (i > 0)
				printf("\n");
			print_directory(dir_array[i], options, mult_dirs);
		}
	}
}
