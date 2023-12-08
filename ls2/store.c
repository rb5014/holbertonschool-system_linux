#include "main.h"

/**
 * store_file - Store file info in a FileArg struct and add it to array
 * @array: Array to update
 * @file: File to add to array
 * @nb: Number of elements in array (old)
*/
void store_file(FileArg **array, FileArg *file, int *nb)
{
	(*nb)++;
	*array = update_array(*file, array, *nb);
}

/**
 * store_dir - Store dir info in a FileArg struct and add it to dir_array
 * @prog_name: Name of the program
 * @path: path of the dir to read and add
 * @dir_array: Array to update
 * @dir_file: Dir to add to array
 * @nb: Number of elements in array (old)
*/
void store_dir(char *prog_name, char *path, FileArg **dir_array,
			   FileArg *dir_file, int *nb)
{
	DIR *dir;
	struct dirent *entry = NULL;
	struct stat st;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("Error opening directory");
		closedir(dir);
		free((*dir_file).name);
		exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		(*dir_file).nb_elem++;
		FileArg element;

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
		(*dir_file).elements = update_array(element, &(*dir_file).elements,
										    (*dir_file).nb_elem);
	}

	(*nb)++;
	*dir_array = update_array(*dir_file, dir_array, (*nb));

	closedir(dir);
}
