#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "custom_functions.h"

/**
 * main - Entry point for the "hls" program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Description:
 *   This function serves as the entry point for the "hls" program.
 *   It lists the content of a specified directory in lexicographical order.
 *   If no directory is provided,
 *   it lists the content of the current directory.
 *
 * Usage:
 *   hls [directory_path]
 *
 * Return:
 *   0 on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	/* Initialize variables */
	char **names = NULL;
	int count = 0;
	int nth_arg;
	bool is_mult_dirs = false;
	const char *dir_path;

	/* Check if a directory name is provided as a command-line argument */
	if (argc <= 1)
	{
		argv[1] = ".";

		/* argv[2] would be SHELL=/bin/bash in that case */
		argv[2] = NULL;
	} else
	{
		is_mult_dirs = true;
		_qsort(&argv[1], argc - 1, sizeof(char *), compare_names);
	}


	for (nth_arg = 1; argv[nth_arg] != NULL; nth_arg++)
	{
		dir_path = argv[nth_arg];

		/* Read the contents of the specified directory */
		read_directory(dir_path, &names, &count);

		/* Print the sorted names */
		print_sorted_names(names, count, dir_path, is_mult_dirs);
	}

	/* Clean up and exit */
	return (0);
}
