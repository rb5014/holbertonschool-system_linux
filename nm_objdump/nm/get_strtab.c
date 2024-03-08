#include "hnm.h"

char *get_elf32_strtab(FILE *file, Elf32_Shdr strtab_hdr)
{
	char *strtab = malloc(strtab_hdr.sh_size);

	fseek(file, strtab_hdr.sh_offset, SEEK_SET);
	fread(strtab, strtab_hdr.sh_size, 1, file);

	return (strtab);
}

char *get_elf64_strtab(FILE *file, Elf64_Shdr strtab_hdr)
{
	char *strtab = malloc(strtab_hdr.sh_size);

	fseek(file, strtab_hdr.sh_offset, SEEK_SET);
	fread(strtab, strtab_hdr.sh_size, 1, file);

	return (strtab);
}
