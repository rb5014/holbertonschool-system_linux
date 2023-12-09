#include "main.h"
/**
 * print_owner - Print the name of the owner of the file/dir
 * @st_uid: User name id
*/
void print_owner(uid_t st_uid)
{
	struct passwd *usr = getpwuid(st_uid);

	if (usr != NULL)
		printf("%s ", usr->pw_name);
	else
		printf("user kaboom");
}

/**
 * print_group - Print the name of the group of the file/dir
 * @st_gid: Group name id
*/
void print_group(uid_t st_gid)
{
	struct group *grp = getgrgid(st_gid);

	if (grp != NULL)
		printf("%s ", grp->gr_name);
	else
		printf("group kakaboom");

}

/**
 * print_time - Print the time in a right format
 * @time: Time represented as a string
*/
void print_time(char *time)
{
	unsigned long int i;

	for (i = 0; i < (_strlen(time) - 1); i++)
		printf("%c", time[i]);
	printf(" ");
}


/**
 * print_permissions - Print the permissions of the current file
 * @st_mode: Mode associated to the struct stat st member of the FileArg
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
 * print_long_listing_format - Print files in long listing format
 * @file_array: Array of files to print
 * @nb: Nb of elements in the array
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

		print_owner(file_array[i].st.st_uid);

		print_group(file_array[i].st.st_gid);

		printf("%li ", file_array[i].st.st_size);

		print_time(ctime(&(file_array[i].st.st_mtime)));

		printf("%s\n", file_array[i].name);
	}
}
