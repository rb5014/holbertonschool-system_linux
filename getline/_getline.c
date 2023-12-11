#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 * Return: the current line
*/

char *_getline(const int fd)
{
	int n_bytes_read = 0;
	char *line = malloc(READ_SIZE);

	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	n_bytes_read = read(fd, line, READ_SIZE);

	if (n_bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}

	/* read doesn't put a null-terminating char */
	line[n_bytes_read] = '\0';

	return (line);
}
