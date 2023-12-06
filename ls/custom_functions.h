#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* Define the boolean type*/
typedef int bool;
#define true 1
#define false 0

/* Define the comparison function type */
typedef int (*cmp_func)(const void*, const void*);
void check_entries(int argc, char **argv);
void process_entries(int n_args, char **argv, bool is_mult_dirs);
void sort_entries(int n_args, char ***argv);
int read_directory(const char *path, char ***names,
				    int *count, const char *prog_name);

void print_error(const char *entry, const char *prog_name);
void print_dir_content(char **names, int count,
						const char *path, bool is_mult_dirs);

int compare_names(const void *a, const void *b);
int compare_types(const void *a, const void *b);
int _strcmp_icase(const char *a, const char *b);
int _strcmp(const char *s1, const char *s2);
void *_realloc(void *ptr, size_t size);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
void _qsort(void *array, int count, int size, cmp_func cmp);
void *_memcpy(void *dest, const void *src, size_t n);
#endif  /* CUSTOM_FUNCTIONS_H */
