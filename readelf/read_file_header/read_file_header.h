#ifndef READ_FILE_HEADER_H
#define READ_FILE_HEADER_H

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
void choose_print_function(FILE *file, int elf_class, int endianness);
void convert_elf32_endianness(Elf32_Ehdr *header32);
void convert_elf64_endianness(Elf64_Ehdr *header64);
/* 32 bit */
void print_elf32_header(Elf32_Ehdr header);
void print_elf32_magic(Elf32_Ehdr header);
const char *get_elf32_machine(Elf32_Ehdr header);
const char *get_elf32_type(Elf32_Ehdr header);

/* 64 bit */
void print_elf64_header(Elf64_Ehdr header);
void print_elf64_magic(Elf64_Ehdr header);
const char *get_elf64_machine(Elf64_Ehdr header);
const char *get_elf64_type(Elf64_Ehdr header);

#endif /* READ_FILE_HEADER_H */
