#include "hnm.h"


void get_elf32_sym_hdrs(FILE *file, Elf32_Ehdr f_hdr, Elf32_Shdr *s_hdrs,
						Elf32_Shdr sym_hdrs[2])
{
	Elf32_Shdr sh_strtab_hdr = s_hdrs[f_hdr.e_shstrndx];
	char *sh_strtab = malloc(sh_strtab_hdr.sh_size);
	int i;

	fseek(file, sh_strtab_hdr.sh_offset, SEEK_SET);
	fread(sh_strtab, sh_strtab_hdr.sh_size, 1, file);

	for (i = 0; i < f_hdr.e_shnum; i++)
	{
		if (strcmp(".symtab", sh_strtab + s_hdrs[i].sh_name) == 0)
			sym_hdrs[0] = s_hdrs[i];
		if (strcmp(".strtab", sh_strtab + s_hdrs[i].sh_name) == 0)
			sym_hdrs[1] = s_hdrs[i];
	}
	free(sh_strtab);
}

void get_elf64_sym_hdrs(FILE *file, Elf64_Ehdr f_hdr, Elf64_Shdr *s_hdrs,
						Elf64_Shdr sym_hdrs[2])
{
	Elf64_Shdr sh_strtab_hdr = s_hdrs[f_hdr.e_shstrndx];
	char *sh_strtab = malloc(sh_strtab_hdr.sh_size);
	int i;

	fseek(file, sh_strtab_hdr.sh_offset, SEEK_SET);
	fread(sh_strtab, sh_strtab_hdr.sh_size, 1, file);

	for (i = 0; i < f_hdr.e_shnum; i++)
	{
		if (strcmp(".symtab", sh_strtab + s_hdrs[i].sh_name) == 0)
			sym_hdrs[0] = s_hdrs[i];
		if (strcmp(".strtab", sh_strtab + s_hdrs[i].sh_name) == 0)
			sym_hdrs[1] = s_hdrs[i];
	}
	free(sh_strtab);
}
