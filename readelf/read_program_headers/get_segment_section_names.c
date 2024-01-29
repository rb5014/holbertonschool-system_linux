#include "main.h"

/**
 * get_elf32_s_names - Return array of all sections names.
 * @file: Pointer to the ELF file.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 * @s_hdrs32: Array of Section header structure for 32-bit ELF files.
 *
 * Return: Array of section names.
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
 * get_elf64_s_names - Return array of all sections names.
 * @file: Pointer to the ELF file.
 * @f_hdr64: ELF header structure for 64-bit ELF files.
 * @s_hdrs64: Array of Section header structure for 64-bit ELF files.
 *
 * Return: Array of section names.
*/
char **get_elf64_s_names(FILE *file, Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64)
{
	Elf64_Half i;
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

/**
 * get_elf32_segments_s_names - Return an array of arrays of strings
 * each containing a section name associated with the program.
 * @file: Pointer to the ELF file.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 * @p_hdrs32: Array of Program header structure for 32-bit ELF files.
 * Return: Array of arrays of strings
*/
char ***get_elf32_segments_s_names(FILE *file, Elf32_Ehdr f_hdr32,
								   Elf32_Phdr *p_hdrs32)
{
	char ***segments_s_names = malloc(sizeof(char **) * f_hdr32.e_phnum);
	char **s_names;
	Elf32_Shdr *s_hdrs32 = malloc(sizeof(Elf32_Shdr) * f_hdr32.e_shnum);
	unsigned int i, j, cur_nb_names;

	fseek(file, f_hdr32.e_shoff, SEEK_SET);
	fread(s_hdrs32, sizeof(Elf32_Shdr), f_hdr32.e_shnum, file);

	if (f_hdr32.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr32.e_shnum; i++)
			convert_elf32_s_hdr_endianness(&s_hdrs32[i]);
	}
	s_names = get_elf32_s_names(file, f_hdr32, s_hdrs32);

	for (i = 0; i < f_hdr32.e_phnum; i++)
	{
		cur_nb_names = 0;
		segments_s_names[i] = malloc(sizeof(char *) * 2);
		segments_s_names[i][0] = strdup("");
		segments_s_names[i][1] = NULL;
		for (j = 0; j < f_hdr32.e_shnum; j++)
		{
			if ((s_hdrs32[j].sh_addr) && (s_hdrs32[j].sh_size) &&
				(s_hdrs32[j].sh_addr >= p_hdrs32[i].p_vaddr) &&
				(s_hdrs32[j].sh_addr < (p_hdrs32[i].p_vaddr + p_hdrs32[i].p_memsz)))
			{
				cur_nb_names++;
				segments_s_names[i] = realloc(segments_s_names[i],
											  sizeof(char *) * (cur_nb_names + 1));
				segments_s_names[i][cur_nb_names - 1] = strdup(s_names[j]);
				segments_s_names[i][cur_nb_names] = NULL;
			}
		}
	}
	free(s_hdrs32);
	free_array(&s_names, f_hdr32.e_shnum);
	return (segments_s_names);
}

/**
 * get_elf64_segments_s_names - Return an array of arrays of strings
 * each containing a section name associated with the program.
 * @file: Pointer to the ELF file.
 * @f_hdr64: ELF header structure for 64-bit ELF files.
 * @p_hdrs64: Array of Program header structure for 64-bit ELF files.
 * Return: Array of arrays of strings
*/
char ***get_elf64_segments_s_names(FILE *file, Elf64_Ehdr f_hdr64,
								   Elf64_Phdr *p_hdrs64)
{
	char ***segments_s_names = malloc(sizeof(char **) * f_hdr64.e_phnum);
	char **s_names;
	Elf64_Shdr *s_hdrs64 = malloc(sizeof(Elf64_Shdr) * f_hdr64.e_shnum);
	unsigned int i, j, cur_nb_names;

	fseek(file, f_hdr64.e_shoff, SEEK_SET);
	fread(s_hdrs64, sizeof(Elf64_Shdr), f_hdr64.e_shnum, file);

	if (f_hdr64.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr64.e_shnum; i++)
			convert_elf64_s_hdr_endianness(&s_hdrs64[i]);
	}
	s_names = get_elf64_s_names(file, f_hdr64, s_hdrs64);

	for (i = 0; i < f_hdr64.e_phnum; i++)
	{
		cur_nb_names = 0;
		segments_s_names[i] = malloc(sizeof(char *) * 2);
		segments_s_names[i][0] = strdup("");
		segments_s_names[i][1] = NULL;
		for (j = 0; j < f_hdr64.e_shnum; j++)
		{
			if ((s_hdrs64[j].sh_addr) && (s_hdrs64[j].sh_size) &&
				(s_hdrs64[j].sh_addr >= p_hdrs64[i].p_vaddr) &&
				(s_hdrs64[j].sh_addr < (p_hdrs64[i].p_vaddr + p_hdrs64[i].p_memsz)))
			{
				cur_nb_names++;
				segments_s_names[i] = realloc(segments_s_names[i],
											  sizeof(char *) * (cur_nb_names + 1));
				segments_s_names[i][cur_nb_names - 1] = strdup(s_names[j]);
				segments_s_names[i][cur_nb_names] = NULL;
			}
		}
	}
	free(s_hdrs64);
	free_array(&s_names, f_hdr64.e_shnum);
	return (segments_s_names);
}
