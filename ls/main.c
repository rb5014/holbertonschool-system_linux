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

	/* Check if a directory name is provided as a command-line argument */
	const char *dir_path = (argc > 1) ? argv[1] : ".";

	/* Read the contents of the specified directory */
	read_directory(dir_path, &names, &count);

	/* Print the sorted names */
	print_sorted_names(names, count);

	/* Clean up and exit */
	return (0);
}
