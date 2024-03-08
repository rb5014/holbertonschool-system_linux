#include "hnm.h"

Elf32_Shdr *get_elf32_all_sct_hdrs(FILE *file, Elf32_Ehdr f_hdr)
{
	int i;
	Elf32_Shdr *s_hdrs = malloc(sizeof(Elf32_Shdr) * f_hdr.e_shnum);

	fseek(file, f_hdr.e_shoff, SEEK_SET);
	fread(s_hdrs, sizeof(Elf32_Shdr), f_hdr.e_shnum, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr.e_shnum; i++)
			convert_elf32_s_hdr_endianness(&s_hdrs[i]);
	}
	return (s_hdrs);
}

Elf64_Shdr *get_elf64_all_sct_hdrs(FILE *file, Elf64_Ehdr f_hdr)
{
	int i;
	Elf64_Shdr *s_hdrs = malloc(sizeof(Elf64_Shdr) * f_hdr.e_shnum);

	fseek(file, f_hdr.e_shoff, SEEK_SET);
	fread(s_hdrs, sizeof(Elf64_Shdr), f_hdr.e_shnum, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr.e_shnum; i++)
			convert_elf64_s_hdr_endianness(&s_hdrs[i]);
	}
	return (s_hdrs);
}
