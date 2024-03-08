#ifndef HNM_H
#define HNM_H

#include <elf.h>
#include "inttypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]);
void free_array(char ***array, uint16_t num);
void choose_print_function(FILE *file, int elf_class);

void process_elf32(FILE *file);
void process_elf64(FILE *file);

Elf32_Ehdr get_elf32_f_hdr(FILE *file);
Elf64_Ehdr get_elf64_f_hdr(FILE *file);


Elf32_Shdr *get_elf32_all_sct_hdrs(FILE *file, Elf32_Ehdr f_hdr);
Elf64_Shdr *get_elf64_all_sct_hdrs(FILE *file, Elf64_Ehdr f_hdr);

void get_elf32_sym_hdrs(FILE *file, Elf32_Ehdr f_hdr, Elf32_Shdr *s_hdrs,
						Elf32_Shdr sym_hdrs[2]);
void get_elf64_sym_hdrs(FILE *file, Elf64_Ehdr f_hdr, Elf64_Shdr *s_hdrs,
						Elf64_Shdr sym_hdrs[2]);
						
Elf32_Sym *get_elf32_sym_structs(FILE *file, Elf32_Ehdr f_hdr,
								 Elf32_Shdr symtab_hdr, unsigned long n_symbols);
Elf64_Sym *get_elf64_sym_structs(FILE *file, Elf64_Ehdr f_hdr,
								 Elf64_Shdr symtab_hdr, unsigned long n_symbols);

char *get_elf32_strtab(FILE *file, Elf32_Shdr strtab_hdr);
char *get_elf64_strtab(FILE *file, Elf64_Shdr strtab_hdr);

char get_elf32_sym_type(uint8_t info, Elf32_Sym sym, Elf32_Shdr *shdr);
char get_elf64_sym_type(uint8_t info, Elf64_Sym sym, Elf64_Shdr *shdr);

void convert_elf32_f_hdr_endianness(Elf32_Ehdr *f_hdr32);
void convert_elf64_f_hdr_endianness(Elf64_Ehdr *f_hdr64);

void convert_elf32_s_hdr_endianness(Elf32_Shdr *s_hdr32);
void convert_elf64_s_hdr_endianness(Elf64_Shdr *s_hdr64);

void print_elf32_symbols_info(Elf32_Shdr *s_hdrs, Elf32_Sym *symbols,
							  const char strtab[], unsigned long n_symbols);
void print_elf64_symbols_info(Elf64_Shdr *s_hdrs, Elf64_Sym *symbols,
							  const char strtab[], unsigned long n_symbols);				
#endif /* HNM_H */
