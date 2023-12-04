#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

/**
 * main - main - entry point
 * @argc: compteur d'arguments
 * @argv: pointeur de tableau de char pour les arguments
 * Return: 0 if successfull
*/
int main(int argc, char *argv[])
{
	DIR *dir;
	char *dir_name;
	struct dirent *read;

	if (argc > 1)
	{
		dir_name = argv[1];
	}
	else
	{
		dir_name = ".";
	}

	dir = opendir(dir_name);

	while ((read = readdir(dir)) != NULL)
	{
		if (read->d_name[0] != '.')
		{
			printf("%s\n", read->d_name);
		}
	}

	closedir(dir);

	return (0);
}
