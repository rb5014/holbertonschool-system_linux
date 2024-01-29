#ifndef READ_PROGRAM_HEADERS_H
#define READ_PROGRAM_HEADERS_H

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

void get_elf32_f_hdr(FILE *file, Elf32_Ehdr *f_hdr32);
void get_elf64_f_hdr(FILE *file, Elf64_Ehdr *f_hdr64);

const char *get_elf32_type(Elf32_Ehdr header);
const char *get_elf64_type(Elf64_Ehdr header);

Elf32_Phdr *get_all_elf32_p_hdrs(FILE *file, Elf32_Ehdr f_hdr32);
Elf64_Phdr *get_all_elf64_p_hdrs(FILE *file, Elf64_Ehdr f_hdr64);

void convert_elf32_p_hdr_endianness(Elf32_Phdr *p_hdr32);
void convert_elf64_p_hdr_endianness(Elf64_Phdr *p_hdr64);
void convert_elf32_s_hdr_endianness(Elf32_Shdr *s_hdr32);
void convert_elf64_s_hdr_endianness(Elf64_Shdr *s_hdr64);
void convert_elf32_file_header_endianness(Elf32_Ehdr *file_hdr32);
void convert_elf64_file_header_endianness(Elf64_Ehdr *file_hdr64);

char **get_elf32_p_types(Elf32_Phdr *p_hdrs32, Elf32_Half e_phnum);
char **get_elf64_p_types(Elf64_Phdr *p_hdrs64, Elf64_Half e_phnum);

char *get_elf32_interp_path(FILE *file, Elf32_Phdr *p_hdrs32,
						    Elf32_Half e_phnum);
char *get_elf64_interp_path(FILE *file, Elf64_Phdr *p_hdrs64,
							Elf64_Half e_phnum);

char ***get_elf32_segments_s_names(FILE *file, Elf32_Ehdr f_hdr32,
									    Elf32_Phdr *p_hdrs32);
char ***get_elf64_segments_s_names(FILE *file, Elf64_Ehdr f_hdr64,
								   Elf64_Phdr *p_hdrs64);

char **get_elf32_s_names(FILE *file, Elf32_Ehdr f_hdr32, Elf32_Shdr *s_hdrs32);
char **get_elf64_s_names(FILE *file, Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64);

char **get_elf32_p_flags(Elf32_Phdr *p_hdrs32, Elf32_Half e_phnum);
char **get_elf64_p_flags(Elf64_Phdr *p_hdrs64, Elf64_Half e_phnum);

void print_elf32_p_hdrs(Elf32_Ehdr f_hdr32, Elf32_Phdr *p_hdrs32,
						char **types, char **flags, char *interp_path, char ***segment_s_names);
void print_elf64_p_hdrs(Elf64_Ehdr f_hdr64, Elf64_Phdr *p_hdrs64,
						char **types, char **flags, char *interp_path, char ***segment_s_names);
#endif /* READ_PROGRAM_HEADERS_H */
