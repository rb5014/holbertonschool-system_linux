#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "custom_functions.h"

/**
 * compare_names - Compare two strings.
 * @a: First string.
 * @b: Second string.
 *
 * Return: 0 if strings are equal, positive if the first non-matching character
 * in a is greater than that of b, negative otherwise.
 */
int compare_names(const void *a, const void *b)
{
	return (_strcmp(*(const char **)a, *(const char **)b));
}

/**
 * is_dot_entry - Check if the directory entry is "." or "..".
 * @entry: Directory entry.
 *
 * Return: 1 if it is ".", 2 if it is "..", 0 otherwise.
 */
int is_dot_entry(const struct dirent *entry)
{
	if (entry->d_name[0] == '.')
	{
		if (entry->d_name[1] == '\0')
			return (1); /* It is "." */
		if (entry->d_name[1] == '.' && entry->d_name[2] == '\0')
			return (2); /* It is ".." */
	}
	return (0); /* It is neither "." nor ".." */
}

/**
 * read_directory - Read the contents of the directory, excluding "." and "..".
 * @dir_path: Path of the directory.
 * @names: Pointer to an array to store names.
 * @count: Pointer to the count of names.
 */
void read_directory(const char *dir_path, char ***names, int *count)
{
	DIR *dir = opendir(dir_path);
	struct dirent *entry;

	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE);
	}


	while ((entry = readdir(dir)) != NULL)
	{
		char *name;

		int dotType = is_dot_entry(entry);

		if (dotType > 0)
		{
			/* Exclude "." and ".." entry */
			continue;
		}

		name = malloc(_strlen(entry->d_name) + 1);

		_strcpy(name, entry->d_name);

		*names = _realloc(*names, (*count + 1) * sizeof(char *));
		(*names)[(*count)++] = name;
	}

	closedir(dir);
}

/**
 * print_sorted_names - Print the names in lexicographical order.
 * @names: Array of names.
 * @count: Number of names.
 */
void print_sorted_names(char **names, int count)
{
	int i;

	qsort(names, count, sizeof(char *), compare_names);

	for (i = 0; i < count; i++)
	{
		printf("%s\n", names[i]);
		free(names[i]);
	}
	free(names);
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
 *   0 on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	/* Initialize variables */
	char **names = NULL;
	int count = 0;

	/* Check if a directory name is provided as a command-line argument */
	const char *dir_path = (argc > 1) ? argv[1] : ".";

	/* Read the contents of the specified directory */
	read_directory(dir_path, &names, &count);

	/* Print the sorted names */
	print_sorted_names(names, count);

	/* Clean up and exit */
	return (0);
}
