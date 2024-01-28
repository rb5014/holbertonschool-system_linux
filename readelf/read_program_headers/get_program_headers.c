#include "main.h"

/**
 * get_all_elf32_p_hdrs - Read all 32-bit program headers from the file.
 * @file: Pointer to the ELF file.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 *
 * This function reads all 32-bit program headers from the file
 * and returns an array containing them.
 *
 * Return: Pointer to an array of 32-bit Elf32_Phdr headers.
 */
Elf32_Phdr *get_all_elf32_p_hdrs(FILE *file, Elf32_Ehdr f_hdr32)
{
	int i;
	Elf32_Phdr *p_hdrs32 = malloc(sizeof(Elf32_Phdr) * f_hdr32.e_phnum);

	fseek(file, f_hdr32.e_phoff, SEEK_SET);
	for (i = 0; i < f_hdr32.e_phnum; i++)
	{
		fread(&p_hdrs32[i], 1, f_hdr32.e_phentsize, file);
		if (f_hdr32.e_ident[EI_DATA] == ELFDATA2MSB)
			convert_elf32_p_hdr_endianness(&p_hdrs32[i]);
	}
	return (p_hdrs32);
}

/**
 * get_all_elf64_p_hdrs - Read and return all 64-bit ELF program headers.
 * @file: Pointer to ELF file.
 * @f_hdr64: ELF64_Ehdr structure containing ELF header information.
 *
 * Reads and returns all 64-bit ELF program headers from the file.
 *
 * Return: Pointer to an array of Elf64_Phdr structures.
 */
Elf64_Phdr *get_all_elf64_p_hdrs(FILE *file, Elf64_Ehdr f_hdr64)
{
	int i;
	Elf64_Phdr *p_hdrs64 = malloc(sizeof(Elf64_Phdr) * f_hdr64.e_phnum);

	fseek(file, f_hdr64.e_phoff, SEEK_SET);
	for (i = 0; i < f_hdr64.e_phnum; i++)
	{
		fread(&p_hdrs64[i], 1, f_hdr64.e_phentsize, file);
		if (f_hdr64.e_ident[EI_DATA] == ELFDATA2MSB)
			convert_elf64_p_hdr_endianness(&p_hdrs64[i]);
	}
	return (p_hdrs64);
}
