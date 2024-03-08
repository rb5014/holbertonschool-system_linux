#include "hnm.h"

Elf32_Ehdr get_elf32_f_hdr(FILE *file)
{
	Elf32_Ehdr f_hdr;

	fseek(file, 0, SEEK_SET);
	fread(&f_hdr, 1, sizeof(f_hdr), file);
	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf32_f_hdr_endianness(file, &f_hdr);

	return (f_hdr);
}

Elf64_Ehdr get_elf64_f_hdr(FILE *file)
{
	Elf64_Ehdr f_hdr;

	fseek(file, 0, SEEK_SET);
	fread(&f_hdr, 1, sizeof(f_hdr), file);
	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf64_f_hdr_endianness(file, &f_hdr);

	return (f_hdr);
}
