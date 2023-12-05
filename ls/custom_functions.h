#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <stddef.h>

/* Define the comparison function type */
typedef int (*cmp_func)(const void*, const void*);

void read_directory(const char *dir_path, char ***names, int *count);
void print_sorted_names(char **names, int count);
int _strcmp(const char *a, const char *b);
void *_realloc(void *ptr, size_t size);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
void _qsort(void *array, int count, int size, cmp_func cmp);
void *_memcpy(void *dest, const void *src, size_t n);
#endif  /* CUSTOM_FUNCTIONS_H */
