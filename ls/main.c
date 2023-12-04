#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

/**
 * cmpstringp - compare to strings
 * @p1: string pointer
 * @p2: string pointer
 *
 * Return: 0 if they are equal,
 * >0 if the first non-matching character in str1
 *  is greater (in ASCII) than that of str2,
 * <0 if the first non-matching character in str1
 *  is lower (in ASCII) than that of str2.
 *
*/
int cmpstringp(const void *p1, const void *p2)
{
	return (strcmp((const char *) p1, (const char *) p2));
}

/**
 * get_number_of_elements - return the number of elements in the directory
 * with the names of the elements it contains
 * @dir_name: directory name
 * Return: pointer to the "array" of string
*/
int get_number_of_elements(char *dir_name)
{
	DIR *dir;
	struct dirent *read;
	int i = 0;

	dir = opendir(dir_name);
	while ((read = readdir(dir)) != NULL)
	{
		i++;
	}
	closedir(dir);
	return (i);
}

/**
 * scan_dir - scan the directory argument and return an array of strings
 * with the names of the elements it contains
 *
 * @dir_name: directory name
 * @n_elems: number of elements
 *
 * Return: pointer to the "array" of string
*/
void scan_dir(char *dir_name, int n_elems)
{
	DIR *dir;
	struct dirent *read;
	int i;
	char name_list[n_elems][256];

	dir = opendir(dir_name);
	for (i = 0; (read = readdir(dir)) != NULL; i++)
	{
		strncpy(name_list[i], read->d_name, 256);
	}

	/* qsort(name_list, n_elems, sizeof(char *), cmpstringp); */
	closedir(dir);

	while (n_elems--)
	{
		if (name_list[n_elems][0] != '.')
		{
			printf("%s\n", name_list[n_elems]);
		}
	}
}


/**
 * main - main - entry point
 * @argc: compteur d'arguments
 * @argv: pointeur de tableau de char pour les arguments
 * Return: 0 if successfull
*/
int main(int argc, char *argv[])
{
	int n_elems = 0;
	char *dir_name = "";

	if (argc > 1)
	{
		dir_name = argv[1];
	}
	else
	{
		dir_name = ".";
	}

	n_elems = get_number_of_elements(dir_name);
	scan_dir(dir_name, n_elems);

	return (0);
}
