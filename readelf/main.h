#ifndef MAIN_H
#define MAIN_H

#include <elf.h>
#include <stdio.h>
#include <string.h>

#if defined(__LP64__)
#define ElfW(type) Elf64_##type
#else
#define ElfW(type) Elf32_##type
#endif

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
void print_elf_header(ElfW(Ehdr) header);
void print_magic(ElfW(Ehdr) header);
const char *get_ABI(ElfW(Ehdr) header);
const char *get_type(ElfW(Ehdr) header);

#endif
