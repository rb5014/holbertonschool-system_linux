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
	struct dirent **dir_name_list;
	int n;

	if (argc > 1)
	{
		char *dir_name = argv[1];

		n = scandir(dir_name, &dir_name_list, 0, alphasort);

		if (n < 0)
		{
			perror("scandir error");
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				printf("%s\n", dir_name_list[i]->d_name);
				free(dir_name_list[i]);
			}
			free(dir_name_list);
		}
	}
	else
	{
		printf("no arguments\n");
	}
	return (0);
}
