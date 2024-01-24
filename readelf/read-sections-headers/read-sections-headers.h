#ifndef READ_SECTIONS_HEADERS_H
#define READ_SECTIONS_HEADERS_H

#include <elf.h>
#include "inttypes.h"
#include <stdio.h>
#include <string.h>

/**
 * struct dict_s - Represents a dictionary entry with an
 * integer value and a string name.
 * @value: The integer value associated with the entry.
 * @name: The string name associated with the entry.
 *
 * Description: This structure defines a key-value pair
 * commonly used in dictionary-like data structures.
 * The 'value' field holds an integer value,
 * and the 'name' field is a pointer to a string providing
 * a human-readable name or description associated with the value.
 */
typedef struct dict_s
{
	int value;
	const char *name;
} dict_t;

int main(int argc, char *argv[]);

#endif /* READ_SECTIONS_HEADERS_H */
