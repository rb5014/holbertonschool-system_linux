#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

int cmpstringp(const void *p1, const void *p2)
{
    return strcmp((const char *)p1, (const char *)p2);
}

void scan_dir(char *dir_name)
{
    DIR *dir;
    struct dirent *read;
    int j = 0, k = 0;
    char **name_list = NULL;

    dir = opendir(dir_name);

    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    while ((read = readdir(dir)) != NULL)
    {
        if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, "..") != 0)
        {
            name_list = (char **)realloc(name_list, sizeof(char *) * (j + 1));
            name_list[j] = (char *)malloc(MAX_NAME_LENGTH);

            if (name_list[j] == NULL)
            {
                perror("Error allocating memory");
                break; // Exit the loop if memory allocation fails
            }

            // Manually copy characters
            for (k = 0; read->d_name[k] != '\0'; k++)
            {
                name_list[j][k] = read->d_name[k];
            }
            name_list[j][k] = '\0'; // Add the null terminator
            j++;
        }
    }

    // Print and free in the reverse order
    while (j--)
    {
        printf("%s\n", name_list[j]);
        free(name_list[j]);
    }

    free(name_list);
    closedir(dir);
}

int main(int argc, char *argv[])
{
    char *dir_name = "."; // Default directory

    if (argc > 1)
    {
        dir_name = argv[1];
    }

    scan_dir(dir_name);

    return 0;
}
