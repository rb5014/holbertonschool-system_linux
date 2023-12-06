#include "custom_functions.h"

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
		return (3); /* it is a hidden file */
	}
	return (0); /* It is neither "." nor ".." */
}

/**
 * count_entries - Count the number of entries in a directory.
 * @path: Path to the directory.
 *
 * Return: Number of entries in the directory.
 */
int count_entries(const char *path)
{
	int count = 0;
	DIR *dir = opendir(path);
	struct dirent *entry;

	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		int dotType = is_dot_entry(entry);

		if (dotType > 0)
		{
			/* Exclude "." and ".." starting entries */
			continue;
		}

		count++;
	}

	closedir(dir);
	return (count);
}

/**
 * allocate_names - Allocate memory for an array of names.
 * @count: Number of names to allocate space for.
 *
 * Return: Pointer to the allocated array of names.
 */
char **allocate_names(int count)
{
	char **names = (char **)malloc(count * sizeof(char *));

	if (names == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	return (names);
}

/**
 * populate_names - Populate an array of names from a directory.
 * @path: Path to the directory.
 * @names: Pointer to the array of names.
 * @count: Pointer to the count of names.
 */
void populate_names(const char *path, char **names, int *count)
{
	DIR *dir = opendir(path);
	struct dirent *entry;

	if (dir == NULL)
	{
		perror("Error opening directory");
		exit(EXIT_FAILURE);
	}

	*count = 0;

	while ((entry = readdir(dir)) != NULL)
	{
		int dotType = is_dot_entry(entry);

		if (dotType > 0)
		{
			/* Exclude "." and ".." starting entries */
			continue;
		}

		/* Allocate memory for the name and copy it */
		names[*count] = malloc(_strlen(entry->d_name) + 1);
		if (names[*count] == NULL)
		{
			perror("Error allocating memory");
			exit(EXIT_FAILURE);
		}

		_strcpy(names[*count], entry->d_name);
		(*count)++;
	}

	closedir(dir);
}

/**
 * read_directory - Read a directory and populate an array of names.
 * @path: Path to the directory.
 * @names: Pointer to the array of names.
 * @count: Pointer to the count of names.
 * @prog_name: Name of the programme (argv[0])
 * Return: 0 if success, -1 otherwise
 */
int read_directory(const char *path, char ***names,
					int *count, const char *prog_name)
{
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		print_error(path, prog_name);
		return (-1);
	}
	*count = count_entries(path);
	*names = allocate_names(*count);
	populate_names(path, *names, count);

	return (0);
}
