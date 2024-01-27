#include "main.h"

/**
 * get_all_elf32_s_hdrs - Read all 32-bit section headers from the file.
 * @file: Pointer to the ELF file.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 *
 * This function reads all 32-bit section headers from the file
 * and returns an array containing them.
 *
 * Return: Pointer to an array of 32-bit section headers.
 */
Elf32_Shdr *get_all_elf32_s_hdrs(FILE *file, Elf32_Ehdr f_hdr32)
{
	int i;
	Elf32_Shdr *s_hdrs32 = malloc(sizeof(Elf32_Shdr) * f_hdr32.e_shnum);

	fseek(file, f_hdr32.e_shoff, SEEK_SET);
	for (i = 0; i < f_hdr32.e_shnum; i++)
	{
		fread(&s_hdrs32[i], 1, f_hdr32.e_shentsize, file);
		if (f_hdr32.e_ident[EI_DATA] == ELFDATA2MSB)
			convert_elf32_s_hdr_endianness(&s_hdrs32[i]);
	}
	return (s_hdrs32);
}

/**
 * get_all_elf64_s_hdrs - Read and return all 64-bit ELF section headers.
 * @file: Pointer to ELF file.
 * @f_hdr64: ELF64_Ehdr structure containing ELF header information.
 *
 * Reads and returns all 64-bit ELF section headers from the file.
 *
 * Return: Pointer to an array of Elf64_Shdr structures.
 */
Elf64_Shdr *get_all_elf64_s_hdrs(FILE *file, Elf64_Ehdr f_hdr64)
{
	int i;
	Elf64_Shdr *s_hdrs64 = malloc(sizeof(Elf64_Shdr) * f_hdr64.e_shnum);

	fseek(file, f_hdr64.e_shoff, SEEK_SET);
	for (i = 0; i < f_hdr64.e_shnum; i++)
	{
		fread(&s_hdrs64[i], 1, f_hdr64.e_shentsize, file);
		if (f_hdr64.e_ident[EI_DATA] == ELFDATA2MSB)
			convert_elf64_s_hdr_endianness(&s_hdrs64[i]);
	}
	return (s_hdrs64);
}
