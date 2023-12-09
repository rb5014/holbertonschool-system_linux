#include "main.h"
/**
 * print_time - print the time in a right format
 * @time: time represented as a string
*/
void print_time(char *time)
{
	unsigned long int i;

	for (i = 0; i < (_strlen(time) - 1); i++)
		printf("%c", time[i]);
	printf(" ");
}


/**
 * print_permissions - print the permissions of the current file
 * @st_mode: mode associated to the struct stat st member of the FileArg
*/
void print_permissions(mode_t st_mode)
{
	/* Owner permissions */
	printf((st_mode & S_IRUSR) ? "r" : "-");
	printf((st_mode & S_IWUSR) ? "w" : "-");
	printf((st_mode & S_IXUSR) ? "x" : "-");

	/* Group permissions */
	printf((st_mode & S_IRGRP) ? "r" : "-");
	printf((st_mode & S_IWGRP) ? "w" : "-");
	printf((st_mode & S_IXGRP) ? "x" : "-");

	/* Others permissions */
	printf((st_mode & S_IROTH) ? "r" : "-");
	printf((st_mode & S_IWOTH) ? "w" : "-");
	printf((st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
}

/**
 * print_long_listing_format - print files in long listing format
 * @file_array: array of files to print
 * @nb: nb of elements in the array
*/
void print_long_listing_format(FileArg *file_array, int nb)
{
	int i;

	for (i = 0; i < nb; i++)
	{
		if (S_ISDIR(file_array[i].st.st_mode))
			printf("d");
		else
			printf("-");
		print_permissions(file_array[i].st.st_mode);
		printf("%li ", file_array[i].st.st_nlink);


		printf("%s\n", file_array[i].name);
	}
}
