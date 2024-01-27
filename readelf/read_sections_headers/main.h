#ifndef READ_SECTIONS_HEADERS_H
#define READ_SECTIONS_HEADERS_H

#include <elf.h>
#include "inttypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * struct dict_s32 - Represents a dictionary entry with an
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
typedef struct dict_s32
{
	int value;
	const char *name;
} dict_t32;

/**
 * struct dict_s64 - Represents a dictionary entry with an
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
typedef struct dict_s64
{
	uint64_t value;
	const char *name;
} dict_t64;

int main(int argc, char *argv[]);
void choose_print_function(FILE *file, int elf_class);

void free_array(char ***array, uint16_t num);

void print_elf32_s_hdrs(Elf32_Ehdr f_hdr32, Elf32_Shdr *s_hdrs32,
						char **names, char **types, char **flags);
void print_elf64_s_hdrs(Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64,
						char **names, char **types, char **flags);


char **get_elf32_s_names(FILE *file, Elf32_Ehdr f_hdr32, Elf32_Shdr *s_hdrs32);
char **get_elf64_s_names(FILE *file, Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64);

unsigned int binary_32(unsigned int **flags_vals_sep, unsigned int num);
Elf64_Xword binary_64(Elf64_Xword **flags_vals_sep, Elf64_Xword num);
char **get_elf32_s_flags(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum);
char **get_elf64_s_flags(Elf64_Shdr *s_hdrs64, Elf64_Half e_shnum);

char **get_elf32_s_types(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum);
char **get_elf64_s_types(Elf64_Shdr *s_hdrs64, Elf64_Half e_shnum);

void get_elf32_s_hdrs_info(FILE *file, Elf32_Ehdr *f_hdr32);
void get_elf64_s_hdrs_info(FILE *file, Elf64_Ehdr *f_hdr64);

Elf32_Shdr *get_all_elf32_s_hdrs(FILE *file, Elf32_Ehdr f_hdr32);
Elf64_Shdr *get_all_elf64_s_hdrs(FILE *file, Elf64_Ehdr f_hdr64);

void convert_elf32_s_hdr_endianness(Elf32_Shdr *s_hdr32);
void convert_elf64_s_hdr_endianness(Elf64_Shdr *s_hdr64);

#endif /* READ_SECTIONS_HEADERS_H */
