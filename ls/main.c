#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

/**
 * cmpstringp - compare two strings for qsort
 * @p1: string pointer
 * @p2: string pointer
 *
 * Return: 0 if equal, >0 if str1 is greater, <0 if str1 is lower
 */
int cmpstringp(const void *p1, const void *p2)
{
	return (strcmp((const char *)p1, (const char *)p2));
}

/**
 * process_entry - process a directory entry
 * @entry: directory entry pointer
 * @name_list: pointer to array of strings
 * @current_index: pointer to the current index in the array
 *
 * Allocates memory for the entry name and copies it into the array.
 *
 * Returns: nothing
 */
void process_entry(struct dirent *entry, char ***name_list, int *current_index)
{
	int k = 0;

	(*name_list) = (char **)realloc((*name_list),
	 sizeof(char *) * ((*current_index) + 1));
	(*name_list)[(*current_index)] = (char *)malloc(MAX_NAME_LENGTH);

	if ((*name_list)[(*current_index)] == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE); /* Exit the program if memory allocation fails */
	}

	/* Manually copy characters */
	for (k = 0; entry->d_name[k] != '\0'; k++)
	{
		(*name_list)[(*current_index)][k] = entry->d_name[k];
	}
	(*name_list)[(*current_index)][k] = '\0'; /* Add the null terminator */
	(*current_index)++;
}

/**
 * scan_dir - scan a directory and return an array of entry names
 * @dir_name: directory name
 * @num_entries: pointer to store the number of entries
 *
 * Returns: an array of entry names
 */
char **scan_dir(char *dir_name, int *num_entries)
{
	DIR *dir;
	struct dirent *read;
	int j = 0;

	char **name_list = NULL;

	dir = opendir(dir_name);

	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE); /* Exit the program if directory cannot be opened */
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, "..") != 0)
		{
			process_entry(read, &name_list, &j);
		}
	}

	closedir(dir);
	*num_entries = j;

	return (name_list);
}

/**
 * print_and_free_entries - print and free entry names
 * @name_list: array of entry names
 * @num_entries: number of entries
 *
 * Prints and frees the entry names in reverse order.
 *
 * Returns: nothing
 */
void print_and_free_entries(char **name_list, int num_entries)
{
	int i;
	for (i = num_entries - 1; i >= 0; i--)
	{
		printf("%s\n", name_list[i]);
		free(name_list[i]);
	}

	free(name_list);
}

/**
 * main - entry point of the program
 * @argc: number of command-line arguments
 * @argv: array of command-line argument strings
 *
 * Returns: 0 on success
 */
int main(int argc, char *argv[])
{
	char *dir_name = ".";
	int num_entries = 0;
	char **entries;

	if (argc > 1)
	{
		dir_name = argv[1];
	}

	entries = scan_dir(dir_name, &num_entries);
	print_and_free_entries(entries, num_entries);

	return (0);
}
