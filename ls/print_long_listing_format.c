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
		printf("%i ", st_uid);

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
		printf("%i ", st_gid);
}

/**
 * print_time - Print the time in a right format
 * @time: Time represented as a string
*/
void print_time(char *time)
{
	unsigned long int i;

	for (i = 4; i < (_strlen(time) - 1 - 8); i++)
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
 * @file: Array of files to print
*/
void print_long_listing_format(FileArg file)
{
	if (S_ISDIR(file.st.st_mode))
		printf("d");
	else
		printf("-");

	print_permissions(file.st.st_mode);

	printf("%li ", file.st.st_nlink);

	print_owner(file.st.st_uid);

	print_group(file.st.st_gid);

	printf("%li ", file.st.st_size);

	print_time(ctime(&(file.st.st_mtime)));

	printf("%s", file.name);
}
