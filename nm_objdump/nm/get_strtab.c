#include "hnm.h"

/**
 * get_elf32_strtab - Get the symbol names in a string
 * @file: Pointer to ELF32 file
 * @strtab_hdr: "strtab" section header
 * Return: String contained in the ".strtab" section
*/
char *get_elf32_strtab(FILE *file, Elf32_Shdr strtab_hdr)
{
	char *strtab = malloc(strtab_hdr.sh_size);

	fseek(file, strtab_hdr.sh_offset, SEEK_SET);
	fread(strtab, strtab_hdr.sh_size, 1, file);

	return (strtab);
}

/**
 * get_elf64_strtab - Get the symbol names in a string
 * @file: Pointer to ELF64 file
 * @strtab_hdr: "strtab" section header
 * Return: String contained in the ".strtab" section
*/
char *get_elf64_strtab(FILE *file, Elf64_Shdr strtab_hdr)
{
	char *strtab = malloc(strtab_hdr.sh_size);

	fseek(file, strtab_hdr.sh_offset, SEEK_SET);
	fread(strtab, strtab_hdr.sh_size, 1, file);

	return (strtab);
}
