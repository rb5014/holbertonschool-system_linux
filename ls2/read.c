#include "main.h"

DIR *init_dir(char *path, char *dir_name)
{
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("Error opening directory");
		closedir(dir);
		free(dir_name);
		exit(EXIT_FAILURE);
	}

	return (dir);
}

void read_entries(char *prog_name, DIR *dir,
				  FileArg *dir_arg, Options *options)
{
	struct dirent *entry = NULL;
	struct stat st;

	while ((entry = readdir(dir)) != NULL)
	{
		FileArg element;

		if (lstat(entry->d_name, &st) == 1)
		{
			/* Invalid path, print error */
			fprintf(stderr, "%s: cannot access %s: ", prog_name, entry->d_name);
			perror("");
			return;
		}

		if ((_strcmp(".", entry->d_name) == 0) ||
		    (_strcmp("..", entry->d_name) == 0))
		{
			if (options->all == false)
				continue;

		} else if ((entry->d_name[0] == '.') && (options->all == false) &&
				   (options->almost_all == false))
			continue;

		element.name = malloc(sizeof(char) * (_strlen(entry->d_name) + 1));
		_strcpy(element.name, entry->d_name);
		element.st = st;

		store_struct(&(*dir_arg).elements, &element, &(*dir_arg).nb_elem);

	}
}

void read_directory(char *prog_name, char *path,
					FileArg *dir_arg, Options *options)
{
	DIR *dir;


	dir = init_dir(path, (*dir_arg).name);
	read_entries(prog_name, dir, dir_arg, options);
	closedir(dir);
}
