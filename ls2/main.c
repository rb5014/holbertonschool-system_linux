#include "main.h"

void print_files(FileArg *reg_array, int nb_reg, Options options)
{
	int i;

	for (i = 0; i < nb_reg; i++)
	{
		printf("%s  ", reg_array[i].name);
	}
	printf("\n");
}

void print_directories(FileArg *dir_array, int nb_dir, Options options)
{
	int i;
	DIR *dir;
	struct dirent *entry;

	for (i = 0; i < nb_dir; i++)
	{
		dir = opendir(dir_array[i].name);

		if (dir == NULL)
		{
			perror("Error opening directory");
			exit(EXIT_FAILURE);
		}
		if (nb_dir > 1)
		{
			if (i > 0)
				printf("\n");
			printf("%s:\n", dir_array[i].name);
		}
		while ((entry = readdir(dir)) != NULL)
		{
			printf("%s  ", entry->d_name);
		}
	}
	printf("\n");
	closedir(dir);
}

void free_all(FileArg **reg_array, FileArg **dir_array, int nb_reg, int nb_dir)
{
	int i, j;

	for (i = 0; i < nb_reg; i++)
	{
		free((*reg_array)[i].name);
	}
	free(*reg_array);

	for (i = 0; i < nb_dir; i++)
	{
		free((*dir_array)[i].name);
	}
	free(*dir_array);
}

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

	if (lstat(path, &st) == 1)
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

	if (S_ISREG(st.st_mode))
	{
		(*nb_reg)++;
		*reg_array = update_array(file, reg_array, (*nb_reg));
	}
	else if (S_ISDIR(st.st_mode))
	{
		DIR *dir;
		struct dirent *entry = NULL;
		int nb_elem = 0;
		int i;

		dir = opendir(path);

		if (dir == NULL)
		{
			perror("Error opening directory");
			exit(EXIT_FAILURE);
		}
		while ((entry = readdir(dir)) != NULL)
		{
			FileArg element;

			nb_elem++;

			if (lstat(entry->d_name, &st) == 1)
			{
				/* Invalid path, print error*/
				fprintf(stderr, "%s: cannot access %s: ", prog_name, entry->d_name);
				perror("");
				return;
			}
			element.name = malloc(sizeof(char) * (_strlen(entry->d_name) + 1));
			_strcpy(element.name, entry->d_name);
			element.st = st;
			file.elements = update_array(element, &file.elements, nb_elem);
		}

		(*nb_dir)++;
		*dir_array = update_array(file, dir_array, (*nb_dir));

		for (i= 0; i < nb_elem; i++)
		{
			free(file.elements[i].name);
		}
		free(file.elements);	
		closedir(dir);
	}
}

/**
 * update_options - Update the Option (defined in "main.h") structure members
 * @prog_name: Name of the program
 * @arg: Argument containing the options code
 * @options: Option structure to be updated
*/
void update_options(char *prog_name, char *arg, Options *options)
{
	int i;

	for (i = 0; arg[i] != '\0'; i++)
	{
		switch (arg[i])
		{
			case '1':
				options->one_by_line = true;
				break;

			case 'a':
				options->all = true;
				break;

			case 'A':
				options->almost_all = true;
				break;

			case 'l':
				options->long_listing_format = true;
				break;

			default:
				fprintf(stderr, "%s: invalid option -- '%c'\n",
						prog_name, arg[i]);
				fprintf(stderr, "Try '%s --help' for more information.\n",
						prog_name);
				exit(EXIT_FAILURE);
		}
	}
}


/**
 * parse_args - Parse the args to classify them by type, get options,
 * find invalid args, etc
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * @options: Pointer to Option struct
 * @reg_array: Pointer to FileArg structs pointer for regular files
 * @dir_array: Pointer to FileArg structs pointer for directories.
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
 *   0 on success.
 */
int main(int argc, char *argv[])
{
	/* FileArg structure defined in "main.h" */
	FileArg *reg_array = NULL;
	FileArg *dir_array = NULL;
	int i;
	int nb_reg = 0;
	int nb_dir = 0;

	/* Options structure defined in "main.h" */
	Options options;

	options.one_by_line = false;
	options.all = false;
	options.almost_all = false;
	options.long_listing_format = false;

	parse_args(argc, argv, &options, &reg_array, &dir_array, &nb_reg, &nb_dir);

	if (nb_reg > 0)
		print_files(reg_array, nb_reg, options);

	if (nb_dir > 0)
		print_directories(dir_array, nb_dir, options);

	free_all(&reg_array, &dir_array, nb_reg, nb_dir);
	return (0);
}