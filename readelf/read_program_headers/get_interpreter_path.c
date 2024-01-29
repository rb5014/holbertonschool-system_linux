#include "main.h"

char *get_elf32_interp_path(FILE *file, Elf32_Phdr *p_hdrs32,
							Elf32_Half e_phnum)
{
	unsigned int i;
	char *interp_path = NULL;

	for (i = 0; i < e_phnum; i++)
	{
		if (p_hdrs32[i].p_type == PT_INTERP)
		{
			fseek(file, p_hdrs32[i].p_offset, SEEK_SET);
			interp_path = malloc(sizeof(char) * p_hdrs32[i].p_memsz);
			fread(interp_path, 1, p_hdrs32[i].p_memsz, file);
		}
	}
	return (interp_path);
}

char *get_elf64_interp_path(FILE *file, Elf64_Phdr *p_hdrs64,
							Elf64_Half e_phnum)
{
	unsigned int i;
	char *interp_path = NULL;

	for (i = 0; i < e_phnum; i++)
	{
		if (p_hdrs64[i].p_type == PT_INTERP)
		{
			fseek(file, p_hdrs64[i].p_offset, SEEK_SET);
			interp_path = malloc(sizeof(char) * p_hdrs64[i].p_memsz);
			fread(interp_path, 1, p_hdrs64[i].p_memsz, file);
		}
	}
	return (interp_path);
}
