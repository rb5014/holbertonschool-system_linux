#include "main.h"

/**
 * init_dir - Initialize a DIR pointer and check if valid
 * or have permissions to be read
 * @prog_name: Name of the program
 * @path: Path of the directory
 * @dir_name: Pointer to the name of the directory store in the FileArg struct
 * Return: The newly initialized DIR pointer to be read after
*/
DIR *init_dir(char *prog_name, char *path, char *dir_name)
{
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: cannot open directory %s: ", prog_name, path);
			perror("");
		}
		else
			perror("Error opening directory");

		closedir(dir);
		free(dir_name);
		exit(EXIT_FAILURE);
	}

	return (dir);
}

/**
 * read_entries - read the entries of the DIR dir that was initialized before
 * @prog_name: Name of the program
 * @dir: Pointer of the DIR to be read
 * @dir_path: String containing the path of the directory
 * @dir_arg: FileArg struct for the dir that
 * will get his member 'elements' updated
 * @options: Options for the printing and/or reading
*/
void read_entries(char *prog_name, DIR *dir, char *dir_path,
				  FileArg *dir_arg, Options *options)
{
	struct dirent *entry = NULL;
	struct stat st;
	char *full_path = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		FileArg element;

		full_path = malloc(sizeof(char) * (_strlen(dir_path) +
										   _strlen(entry->d_name) + 1 + 1));
		sprintf(full_path, "%s/%s", dir_path, entry->d_name);
		if (lstat((const char *)full_path, &st) == -1)
		{
			free(full_path);
			/* Invalid path, print error */
			fprintf(stderr, "%s: cannot access %s: ", prog_name, entry->d_name);
			perror("");
			return;
		}

		if ((_strcmp(".", entry->d_name) == 0) ||
		    (_strcmp("..", entry->d_name) == 0))
		{
			if (options->all == false)
			{
				free(full_path);
				continue;
			}
		} else if ((entry->d_name[0] == '.') && (options->all == false) &&
				   (options->almost_all == false))
		{
			free(full_path);
			continue;
		}
		element.name = malloc(sizeof(char) * (_strlen(entry->d_name) + 1));
		_strcpy(element.name, entry->d_name);
		element.st = st;
		store_struct(&(*dir_arg).elements, &element, &(*dir_arg).nb_elem);
		free(full_path);
	}
}

/**
 * read_directory - Read the directory and its elements then store them
 * @prog_name: Name of the program
 * @path: String containing the path of the directory
 * @dir_arg: FileArg struct for the dir that
 * will get his member 'elements' updated
 * @options: Options for the printing and/or reading
*/
void read_directory(char *prog_name, char *path,
					FileArg *dir_arg, Options *options)
{
	DIR *dir;


	dir = init_dir(prog_name, path, (*dir_arg).name);
	read_entries(prog_name, dir, path, dir_arg, options);
	closedir(dir);
}
