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

    // Check if the directory entry is valid
    if (lstat(path, &st) == -1) {
        return (false);  // Failed to stat, it is invalid
    }

    return (true);
}

/**
 * check_entries - Check and modify argv entries.
 * @argv: Pointer to the array of command-line arguments.
 */
int check_entries(char ***argv)
{
    int src, dest;

    // Iterate over argv, removing invalid entries
    for (src = 1, dest = 1; (*argv)[src] != NULL; src++)
	{
        if (is_valid_entry((*argv)[src]))
		{
            // Keep valid entry
            (*argv)[dest++] = (*argv)[src];
        } else {
            // Invalid entry, print error and skip it
            fprintf(stderr, "%s: cannot access '%s': ", (*argv)[0], (*argv)[src]);
			perror("");
        }
    }

    // Terminate the modified argv
    (*argv)[dest] = NULL;
	
	/* Return the new number of arguments validated, minus the name of the program */
	return (dest -1);
}

/**
 * sort_entries - Sort argv entries.
 * @n_args: Number of command-line arguments validated.
 * @argv: Pointer to the array of command-line arguments.
 */
void sort_entries(int n_args, char ***argv)
{
	_qsort(&argv[1], n_args, sizeof(char *), compare_names);
}

/**
 * process_entries - Execute the actual operations based on validated entries
 * @n_args: Number of command-line arguments validated.
 * @argv: Pointer to the array of command-line arguments.
 * @is_mult_args: Boolean stating if there are multiple arguments or not
 */
void process_entries(int n_args, char **argv, bool is_mult_args)
{
	char **names = NULL;
	int nth_arg;
	const char *dir_path;
	int count = 0;
	// struct stat st[n_args];

	/* Sort entries alphabetically and by type */
	sort_entries(n_args, &argv);
	for (nth_arg = 1; argv[nth_arg] != NULL; nth_arg++)
	{
		dir_path = argv[nth_arg];

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
		/* argv[2] would be SHELL=/bin/bash in that case */
		argv[2] = NULL;
	}
	/* Check if there are multiple file/directory names provided */
	else if (argc > 2)
	{
		is_mult_args = true;
	}

	/* Check if entry is valid, and print errors if not, also removing them from argv */
	check_entries(&argv);

	/* Reorganize entries and print their content (or names for files) */
	process_entries(argc, argv, is_mult_args);

	return (0);
}
