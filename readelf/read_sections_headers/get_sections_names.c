#include "main.h"

/**
 * get_elf32_s_names - Get section names for 32-bit ELF files.
 * @file: Pointer to the ELF file.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 * @s_hdrs32: Array of 32-bit section headers.
 *
 * This function retrieves section names for 32-bit ELF files.
 *
 * Return: Pointer to an array of section names.
 */
char **get_elf32_s_names(FILE *file, Elf32_Ehdr f_hdr32, Elf32_Shdr *s_hdrs32)
{
	Elf32_Half i;
	Elf32_Shdr sh_strtab_header;
	char *sh_strtab;
	char **section_names;

	fseek(file,
	 f_hdr32.e_shoff + f_hdr32.e_shentsize * f_hdr32.e_shstrndx, SEEK_SET);
	fread(&sh_strtab_header, sizeof(Elf32_Shdr), 1, file);
	if (f_hdr32.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf32_s_hdr_endianness(&sh_strtab_header);
	sh_strtab = malloc(sh_strtab_header.sh_size);

	fseek(file, sh_strtab_header.sh_offset, SEEK_SET);
	fread(sh_strtab, sh_strtab_header.sh_size, 1, file);
	section_names = malloc(f_hdr32.e_shnum * sizeof(char *));

	for (i = 0; i < f_hdr32.e_shnum; i++)
	{
		fseek(file, f_hdr32.e_shoff + i * f_hdr32.e_shentsize, SEEK_SET);

		section_names[i] = strdup(sh_strtab + s_hdrs32[i].sh_name);
	}

	free(sh_strtab);

	return (section_names);
}

/**
 * get_elf64_s_names - Read and return ELF64 section names.
 * @file: Pointer to ELF file.
 * @f_hdr64: ELF64_Ehdr structure containing ELF header information.
 * @s_hdrs64: Array of ELF64_Shdr structures.
 *
 * Reads and returns ELF64 section names based on the provided information.
 *
 * Return: Pointer to an array of strings representing section names.
 */
char **get_elf64_s_names(FILE *file, Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64)
{
	Elf32_Half i;
	Elf64_Shdr sh_strtab_header;
	char *sh_strtab;
	char **section_names;

	fseek(file,
	 f_hdr64.e_shoff + f_hdr64.e_shentsize * f_hdr64.e_shstrndx, SEEK_SET);
	fread(&sh_strtab_header, sizeof(Elf64_Shdr), 1, file);
	if (f_hdr64.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf64_s_hdr_endianness(&sh_strtab_header);
	sh_strtab = malloc(sh_strtab_header.sh_size);

	fseek(file, sh_strtab_header.sh_offset, SEEK_SET);
	fread(sh_strtab, sh_strtab_header.sh_size, 1, file);
	section_names = malloc(f_hdr64.e_shnum * sizeof(char *));

	for (i = 0; i < f_hdr64.e_shnum; i++)
	{
		fseek(file, f_hdr64.e_shoff + i * f_hdr64.e_shentsize, SEEK_SET);

		section_names[i] = strdup(sh_strtab + s_hdrs64[i].sh_name);
	}

	free(sh_strtab);

	return (section_names);
}
