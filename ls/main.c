#include "custom_functions.h"

/**
 * is_valid_entry - Check if a file/directory entry is valid.
 * @path: Path of the file/directory entry.
 *
 * Return: true if the entry is a valid file/directory, false otherwise.
 */
bool is_valid_entry(const char *path)
{
	struct stat st;

	/* Check if the directory entry is valid */
	if (lstat(path, &st) == -1)
	{
		return (false);  /* Failed to stat, it is invalid */
	}
	return (true);
}

/**
 * check_entries - Check and modify argv entries.
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments.
 */
void check_entries(int argc, char **argv)
{
	int i;

	/* Iterate over argv, removing invalid entries */
	for (i = 1; i < argc; i++)
	{
		if (is_valid_entry(argv[i]) == false)
		{
			/* Invalid entry, print error and skip it */
			fprintf(stderr, "%s: cannot access '%s': ", argv[0], argv[i]);
			perror("");
			argv[i] = NULL;
		}
	}

}

/**
 * sort_entries - Sort argv entries.
 * @n_entries: Number of entries.
 * @argv: Pointer to the array of command-line arguments.
 */
void sort_entries(int n_entries, char ***argv)
{
	_qsort(&argv[1], n_entries, sizeof(char *), compare_types);
}

/**
 * process_entries - Execute the actual operations based on entries
 * @argc: Number of command-line arguments.
 * @argv: Pointer to the array of command-line arguments.
 * @is_mult_args: Boolean stating if there are multiple arguments or not
 */
void process_entries(int argc, char **argv, bool is_mult_args)
{
	char **names = NULL;
	int i;
	const char *dir_path;
	int count = 0;
	/* int n_entries = argc - 1; */
	/* struct stat st[argc]; */

	/* Sort entries alphabetically and by type */
	/* sort_entries(n_entries, &argv); */
	for (i = 1; i < argc; i++)
	{
		if (argv[i] == NULL)
		{
			continue;
		}
		if (i > 1)
		{
			printf("\n");
		}

		dir_path = argv[i];

		/* Read the contents of the specified directory */
		read_directory(dir_path, &names, &count);

		/* Print the sorted names */
		print_sorted_names(names, count, dir_path, is_mult_args);
	}
}

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
	bool is_mult_args = false;

	/* Check if a directory name is provided as a command-line argument */
	if (argc <= 1)
	{
		argv[1] = ".";
		argc++;
	}
	/* Check if there are multiple file/directory names provided */
	else if (argc > 2)
	{
		is_mult_args = true;
	}

	/* Check entries validity, remove invalids and print error */
	check_entries(argc, argv);

	/* Reorganize entries and print their content (or names for files) */
	process_entries(argc, argv, is_mult_args);

	return (0);
}
