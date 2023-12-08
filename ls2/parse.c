#include "main.h"

/**
 * update_array - Ann a new element to one of the arrays of structs FileArg
 * @file: file arg to add to the array
 * @file_array: array to be updated
 * @nb_elem: number of elements in the array
 * Return: A newly updated array cotaning the old elements + the new one
*/
FileArg *update_array(FileArg file, FileArg **file_array, int nb_elem)
{
	FileArg *new_array = malloc(sizeof(FileArg) * nb_elem);

	if (new_array == NULL)
	{
	/* Allocation failed, return the original pointer */
		return (NULL);
	}
	if (*file_array != NULL)
	{
		_memcpy(new_array, *file_array, sizeof(FileArg) * (nb_elem - 1));
		free(*file_array);
	}
	new_array[nb_elem - 1] = file;

	return (new_array);
}



/**
 * parse_path - Parse the args accordingly to their type and validity
 * @prog_name: Name of the program
 * @path: Path to the file or directory
 * @reg_array: Pointer to FileArg structs pointer for regular files
 * @dir_array: Pointer to FileArg structs pointer for directories.
 * @nb_reg: number of files currently in reg_array array of struct
 * @nb_dir: number of directories currently in dir_array array of struct
*/
void parse_path(char *prog_name, char *path,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir)
{
	struct stat st;

	st.st_mode = 0;

	if (lstat(path, &st) == -1)
	{
		/* Invalid path, print error*/
		fprintf(stderr, "%s: cannot access %s: ", prog_name, path);
		perror("");
		return;
	}

	FileArg file;

	file.name = malloc(sizeof(char) * (_strlen(path) + 1));
	_strcpy(file.name, path);
	file.st = st;
	file.elements = NULL;
	file.nb_elem = 0;

	if (S_ISREG(st.st_mode))
	{
		store_file(reg_array, &file, nb_reg);
	}
	else if (S_ISDIR(st.st_mode))
	{
		store_dir(prog_name, path, dir_array, &file, nb_dir);
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
*/
void parse_args(int argc, char *argv[],
				Options *options,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir)
{
	int i;
	char *prog_name = argv[0];

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
		else
		{
			parse_path(prog_name, argv[i], reg_array, dir_array, nb_reg, nb_dir);
		}
	}
}
