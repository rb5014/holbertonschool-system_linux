#ifndef READ_SECTIONS_HEADERS_H
#define READ_SECTIONS_HEADERS_H

#include <elf.h>
#include "inttypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void free_array(char ***array, Elf32_Half num);

/* 32 bit */
void print_elf32_sections_headers(FILE *file, Elf32_Shdr *s_hdrs32,
								  Elf32_Off e_shoff, Elf32_Half e_shentsize,
								  Elf32_Half e_shnum, Elf32_Half e_shstrndx, char **names, char **types, char **flags);
char **get_elf32_s_flags(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum);
int binary(int **flags_vals_sep, int num);
char **get_elf32_s_types(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum);
char **get_elf32_s_names(FILE *file, int endianness, Elf32_Shdr *s_hdrs32, Elf32_Off e_shoff,
						 Elf32_Half e_shentsize, Elf32_Half e_shnum, Elf32_Half e_shstrndx);
void get_elf32_s_hdrs_info(FILE *file, int endianness, Elf32_Off *e_shoff,
						   Elf32_Half *e_shentsize, Elf32_Half *e_shnum,
						   Elf32_Half *e_shstrndx);
Elf32_Shdr *get_all_elf32_s_headers(FILE *file, int endianness,
			Elf32_Off e_shoff, Elf32_Half e_shentsize, Elf32_Half e_shnum);
void convert_elf32_s_hdr_endianness(Elf32_Shdr *s_hdr32);

/* 64 bit */
void print_elf64_sections_headers(Elf64_Shdr *s_hdrs64, Elf64_Off e_shoff,
								  Elf64_Half e_shnum, Elf64_Half e_shstrndx);
void get_elf64_s_hdrs_info(FILE *file, int endianness, Elf64_Off *e_shoff,
						   Elf64_Half *e_shentsize, Elf64_Half *e_shnum,
						   Elf64_Half *e_shstrndx);
Elf64_Shdr *get_all_elf64_s_headers(FILE *file, int endianness,
			Elf64_Off e_shoff, Elf64_Half e_shentsize, Elf64_Half e_shnum);
void convert_elf64_s_hdr_endianness(Elf64_Shdr *s_hdr64);

#endif /* READ_SECTIONS_HEADERS_H */
