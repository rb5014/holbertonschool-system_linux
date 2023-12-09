#include "main.h"

/**
 * free_files - Free an array of FileArg structs and all their 'name' member
 * that need to be freed too
 * @array: The array to be freed
 * @nb: Number of elements in the array
*/
void free_files(FileArg **array, int nb)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		free((*array)[i].name);
	}
	free(*array);
}

/**
 * free_dirs - Free an array of FileArg structs and all their 'name' member
 * AND their 'elements' member which is a FileArg array too
 * @dir_array: The dirs array to be freed
 * @nb_dir: Number of elements in the array
*/
void free_dirs(FileArg **dir_array, int nb_dir)
{
	int i;

	for (i = 0; i < nb_dir; i++)
	{
		free((*dir_array)[i].name);
		free_files(&(*dir_array)[i].elements, (*dir_array)[i].nb_elem);
	}
	free(*dir_array);
}

/**
 * free_all - Free all the FileArg struts that populates
 * the regular files and directories arrays.
 * @reg_array: Regular files array of FileArg structs
 * @dir_array: Directory files array of FileArg structs
 * @nb_reg: Number of regular files in array
 * @nb_dir: Number of directories in array
*/
void free_all(FileArg **reg_array, FileArg **dir_array, int nb_reg, int nb_dir)
{
	if (reg_array != NULL)
		free_files(reg_array, nb_reg);
	if (dir_array != NULL)
		free_dirs(dir_array, nb_dir);
}
