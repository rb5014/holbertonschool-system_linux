#include "_getline.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/**
 * _getline - Reads an entire line from a file descriptor.
 * @fd: File descriptor to read from.
 * Return: Null-terminated string without newline,
 * or NULL if error or end of file.
 * Description: This function reads from the given file descriptor until
 *              a newline character is encountered. It handles any remaining
 *              characters from previous reads and dynamically allocates
 *              memory for the line being read.
 */
char *_getline(const int fd)
{
	static char **remainder;
	static int *fd_array, *eof_flag_array, nb_fd;
	char *line;
	int array_index = 0;

	if (fd == -1)
	{
		int j;

		for (j = 0; j < nb_fd; j++)
			free(remainder[j]);
		free(remainder), free(fd_array), free(eof_flag_array);
		remainder = NULL, fd_array = NULL, eof_flag_array = NULL, nb_fd = 0;
		return (NULL);
	}

	array_index = update_fd_arrays(fd, &fd_array, &remainder,
									   &eof_flag_array, &nb_fd);
	if (array_index == -1)
		return (NULL);

	line = check_remainder(&remainder[array_index]);
	if (line)
		return (line);

	if (eof_flag_array[array_index])
	{
		eof_flag_array[array_index] = 0;
		if (nb_fd == 1)
		{
			free(remainder[array_index]);
			nb_fd = 0;
			_getline(-1);
		}

		return (NULL);
	}

	line = read_line(fd, &remainder[array_index], &eof_flag_array[array_index]);
	return (line);
}

/**
 * update_fd_arrays - Updates or initializes arrays for file descriptors.
 * @fd: The file descriptor to add or update in the arrays.
 * @fd_array: Pointer to the array of file descriptors.
 * @remainder: Pointer to the array of remainders for each file descriptor.
 * @eof_flag_array: Pointer to the array of EOF flags for each file descriptor.
 * @nb_fd: Pointer to the number of file descriptors currently tracked.
 * Return: On success,
 * returns the index of the file descriptor in the fd_array.
 *         On failure, returns -1.
 */
int update_fd_arrays(int fd, int **fd_array, char ***remainder,
					 int **eof_flag_array, int *nb_fd)
{
	int *new_fd_array = NULL, *new_eof_flag_array = NULL, i = 0;
	char **new_remainder = NULL;

	for (i = 0; i < *nb_fd; i++)
	{
		if ((*fd_array)[i] == fd)
			return (i);
	}

	*nb_fd += 1;
	new_fd_array = realloc(*fd_array, sizeof(int) * (*nb_fd));
	new_remainder = realloc(*remainder, sizeof(char *) * (*nb_fd));
	new_eof_flag_array = realloc(*eof_flag_array, sizeof(int) * (*nb_fd));

	if (!new_fd_array || !new_remainder || !new_eof_flag_array)
		return (-1);

	*fd_array = new_fd_array;
	*remainder = new_remainder;
	*eof_flag_array = new_eof_flag_array;

	(*fd_array)[i] = fd;
	(*remainder)[i] = NULL;
	(*eof_flag_array)[i] = 0;
	return (i);
}

/**
 * check_remainder - Checks and processes any remainder from the previous read.
 * @remainder: Pointer to the remainder string.
 * Return: Line up to the newline, or NULL if no newline found.
 * Description: This function checks if there is a leftover part from the
 *              previous read. If a newline is found, it returns the line
 *              up to the newline. Otherwise, returns NULL.
 */
char *check_remainder(char **remainder)
{
	if (*remainder)
	{
		char *nl, *line = NULL;

		for (nl = *remainder; *nl; nl++)
		{
			if (*nl == '\n')
			{
				size_t len = 0;
				char *ptr;

				*nl = '\0';

				line = strdup(*remainder);
				for (ptr = nl + 1; *ptr; ptr++)
				{
					len++;
				}

				safe_move(*remainder, nl + 1, len + 1);
				return (line);
			}
		}
		line = strdup(*remainder);

		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	return (NULL);
}


/**
 * read_line - Reads a line from a file descriptor.
 * @fd: File descriptor to read from.
 * @remainder: Pointer to the remainder string.
 * @eof_flag: Pointer to static EOF flag when n_read < READ_SIZE
 * Return: Complete line read, or NULL on error or end of file.
 * Description: This function reads from the file descriptor in chunks
 *              and appends each chunk to the current line until a newline
 *              is found or the file ends.
 */
char *read_line(const int fd, char **remainder, int *eof_flag)
{
	static char buffer[READ_SIZE + 1]; /* Buffer for read chunks */
	char *line = NULL, *ptr = NULL;
	ssize_t n_read;
	size_t len = 0;

	while (1)
	{
		n_read = read(fd, buffer, READ_SIZE); /* Read chunk into buffer */

		/* Check for end of file or read error */
		if (n_read < READ_SIZE)
		{
			*eof_flag = 1; /* Set EOF indicator */
			if (n_read > 0 && buffer[n_read - 1] == '\n')
				buffer[n_read - 1] = '\0';
			if (n_read <= 0)
			{
				return (n_read == 0 ? line : NULL);
			}


		}

		buffer[n_read] = '\0'; /* Null-terminate the read chunk */
		append_buffer(&line, buffer, &len, n_read); /* Append chunk to line */

		/* Manually search for newline in the newly appended part of line */
		for (ptr = line + len - n_read; *ptr; ptr++)
		{
			if (*ptr == '\n') /* Newline found */
			{
				*ptr = '\0'; /* Terminate the line here */
				if (READ_SIZE != 1)
					*remainder = strdup(ptr + 1); /* Prepare the remainder */
				return (line);
			}
		}
	}
}


/**
 * append_buffer - Appends a buffer to a dynamically growing line.
 * @line: Pointer to the line being constructed.
 * @buffer: Buffer to append to the line.
 * @len: Pointer to the current length of the line.
 * @n_read: Number of bytes read into the buffer.
 * Description: This function reallocates the line to fit the new buffer
 *              and appends the buffer to the end of the line.
 */
void append_buffer(char **line, char *buffer, size_t *len, size_t n_read)
{
	/* Reallocate line for new buffer */
	char *temp = realloc(*line, *len + n_read + 1);

	if (!temp) /* Check for allocation failure */
	{
		free(*line); /* Free existing line on failure */
		*line = NULL;
		return;
	}

	*line = temp; /* Update line pointer */
	memcpy(*line + *len, buffer, n_read + 1); /* Append buffer to line */
	*len += n_read; /* Update line length */
}

/**
 * safe_move - Safely moves overlapping memory regions.
 * @dest: The destination address.
 * @src: The source address.
 * @n: The number of bytes to move.
 */
void safe_move(char *dest, char *src, size_t n)
{
	size_t i;

	if (dest < src)
	{
		for (i = 0; i < n; i++)
		{
			dest[i] = src[i];
		}
	}
	else
	{
		for (i = n; i != 0; i--)
		{
			dest[i - 1] = src[i - 1];
		}
	}
}
