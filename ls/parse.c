#include "main.h"

/**
 * parse_path - Parse the args accordingly to their type and validity
 * @prog_name: Name of the program
 * @path: Path to the file or directory
 * @reg_array: Pointer to FileArg structs pointer for regular files
 * @dir_array: Pointer to FileArg structs pointer for directories.
 * @nb_reg: number of files currently in reg_array array of struct
 * @nb_dir: number of directories currently in dir_array array of struct
 * @options: Options struct
 * @invalid_file_found: If true, then the file is invalid
*/
void parse_path(char *prog_name, char *path,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir,
				Options *options,
				bool *invalid_file_found)
{
	struct stat st;
	FileArg file;

	st.st_mode = 0;

	if (lstat(path, &st) == -1)
	{
		/* Invalid path, print error*/
		fprintf(stderr, "%s: cannot access %s: ", prog_name, path);
		perror("");
		*invalid_file_found = true;
		return;
	}


	file.name = malloc(sizeof(char) * (_strlen(path) + 1));
	_strcpy(file.name, path);
	file.st = st;
	file.elements = NULL;
	file.nb_elem = 0;

	if (S_ISREG(st.st_mode))
	{
		store_struct(reg_array, &file, nb_reg);
	}
	else if (S_ISDIR(st.st_mode))
	{
		store_dir_struct(prog_name, path, dir_array, &file, nb_dir, options);
	}
}

/**
 * parse_args - Parse the args to classify them by type, get options,
 * find invalid args, etc
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * @options: Pointer to Option struct
 * @reg_array: Pointer to FileArg structs pointer for regular files
 * @dir_array: Pointer to FileArg structs pointer for directories
 * @nb_reg: Number of elements in reg_array
 * @nb_dir: Number of elements in dir_array
 * @mult_dirs: If true, then more than one dir is present in the arguments
*/
void parse_args(int argc, char *argv[],
				Options *options,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir,
				bool *mult_dirs)
{
	int i;
	char *prog_name = argv[0];
	bool invalid_file_found = false;

	if (argc == 1)
	{
		argv[1] = ".";
		argc++;
	}

	for (i = 1; i < argc; i++)
	{
		/* Check if its an option (or multiple options) */
		if (argv[i][0] == '-')
			/* Update options struct */
			update_options(prog_name, &argv[i][1], options);
	}

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			continue;
		parse_path(prog_name, argv[i], reg_array, dir_array, nb_reg, nb_dir,
				   options, &invalid_file_found);
	}

	if ((*nb_dir > 1) || ((*nb_dir == 1) && (invalid_file_found == true)))
		*mult_dirs = true;
}
