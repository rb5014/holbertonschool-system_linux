#ifndef _GETLINE_H
#define _GETLINE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Macro defining the number of bytes to read at a time */
#define READ_SIZE BUFSIZ

char *_getline(const int fd);
char *find_newline(char *str);
char *read_line(const int fd, char **remainder);
char *check_remainder(char **remainder);
void append_buffer(char **line, char *buffer, size_t *len, size_t n_read);
void safe_move(char *dest, char *src, size_t n);
#endif /* _GETLINE_H */
