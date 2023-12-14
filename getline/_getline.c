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
	static char *remainder;  /* Static remainder from previous reads */
	static int eof_flag; /* Static flag for EOF, 1 when n_read < READ_SIZE */
	char *line = check_remainder(&remainder); /* Check for any remaining lines */

	if (fd == -1)
		return (NULL);
	if (line)
		return (line);

	if (eof_flag && !remainder)
		return (NULL); /* Return NULL if EOF flag is set and no remainder */

	/* Read new line from file descriptor */
	return (read_line(fd, &remainder, &eof_flag));
}


/**
 * find_newline - Finds the first occurrence of a newline character
 * in a string.
 * @str: The string to search.
 * Return: Pointer to the first occurrence of a newline character,
 * or NULL if none found.
 */
char *find_newline(char *str)
{
	while (*str) /* Iterate through the string */
	{
		if (*str == '\n') /* Check for newline character */
			return (str);
		str++;
	}
	return (NULL);
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
	char *newline_pos, *line = NULL;

	if (*remainder)
	{
		newline_pos = find_newline(*remainder); /* Find newline in remainder */
		if (newline_pos) /* Split at the newline if found */
		{
			size_t len = 0;
			char *ptr;

			/* Calculate the length of the string after the newline */
			for (ptr = newline_pos + 1; *ptr; ptr++)
			{
				len++;
			}

			*newline_pos = '\0';
			line = strdup(*remainder);
			/* Move the string after the newline to the start of remainder */
			safe_move(*remainder, newline_pos + 1, len + 1);

			return (line);
		}

		line = strdup(*remainder); /* Copy remainder to line */
		free(*remainder); /* Free old remainder */
		*remainder = NULL;
	}
	return (line);
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
	char *line = NULL;
	ssize_t n_read;
	size_t len = 0;


	while (1)
	{
		char *newline_pos = NULL;

		n_read = read(fd, buffer, READ_SIZE); /* Read chunk into buffer */

		/* Check for end of file or read error */
		if (n_read < READ_SIZE)
		{
			*eof_flag = 1; /* Set EOF indicator */
			if (buffer[n_read - 1] == '\n')
				buffer[n_read - 1] = '\0';
			if (n_read <= 0)
				return (n_read == 0 ? line : NULL);
		}

		buffer[n_read] = '\0'; /* Null-terminate the read chunk */
		append_buffer(&line, buffer, &len, n_read); /* Append chunk to line */

		newline_pos = find_newline(line); /* Check for newline in line */

		if (newline_pos) /* Split line at newline and prepare remainder */
		{
			*newline_pos = '\0';
			if (READ_SIZE != 1)
				*remainder = strdup(newline_pos + 1);
			return (line);
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
