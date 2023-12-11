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

	n_bytes_read = read(fd, line, READ_SIZE);

	if (n_bytes_read == 0)
	{
		return (NULL);
	}

	return (line);
}
