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
 * store_struct - Store FileArg struct and add it to array
 * @array: Array to update
 * @file: File to add to array
 * @nb: Number of elements in array (old)
*/
void store_struct(FileArg **array, FileArg *file, int *nb)
{
	(*nb)++;
	*array = update_array(*file, array, *nb);
}

/**
 * store_dir_struct - Store dir info in a FileArg struct
 * and add it to dir_array
 * @prog_name: Name of the program
 * @path: path of the dir to read and add
 * @dir_array: Array to update
 * @dir_arg: Dir to add to array
 * @nb: Number of elements in array (old)
 * @options: Options struct
*/
void store_dir_struct(char *prog_name, char *path, FileArg **dir_array,
			   FileArg *dir_arg, int *nb, Options *options)
{
	read_directory(prog_name, path, dir_arg, options);

	(*nb)++;
	*dir_array = update_array(*dir_arg, dir_array, (*nb));

}
