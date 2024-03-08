#include "hnm.h"

Elf32_Ehdr get_elf32_f_hdr(FILE *file)
{
	Elf32_Ehdr f_hdr;

	fseek(file, 0, SEEK_SET);
	fread(&f_hdr, 1, sizeof(f_hdr), file);
	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf32_f_hdr_endianness(&f_hdr);

	return (f_hdr);
}

Elf64_Ehdr get_elf64_f_hdr(FILE *file)
{
	Elf64_Ehdr f_hdr;

	fseek(file, 0, SEEK_SET);
	fread(&f_hdr, 1, sizeof(f_hdr), file);
	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
		convert_elf64_f_hdr_endianness(&f_hdr);

	return (f_hdr);
}

/**
 * convert_elf32_f_hdr_endianness - Convert endianness of fields.
 * @file: Pointer to the ELF file.
 * @f_hdr32: Pointer to the ELF header structure for 32-bit ELF files.
 *
 * This function reads and updates the ELF header information
 * for 32-bit ELF files.
 */
void convert_elf32_f_hdr_endianness(Elf32_Ehdr *f_hdr32)
{
	f_hdr32->e_shoff = __builtin_bswap32(f_hdr32->e_shoff);
	f_hdr32->e_shentsize = __builtin_bswap16(f_hdr32->e_shentsize);
	f_hdr32->e_shnum = __builtin_bswap16(f_hdr32->e_shnum);
	f_hdr32->e_shstrndx = __builtin_bswap16(f_hdr32->e_shstrndx);
}

/**
 * convert_elf64_f_hdr_endianness - Convert endianness of fields.
 * @file: Pointer to ELF file.
 * @f_hdr64: Pointer to ELF64_Ehdr structure to store header information.
 *
 * Reads ELF64_Ehdr information from the file and updates f_hdr64.
 *
 */
void convert_elf64_f_hdr_endianness(Elf64_Ehdr *f_hdr64)
{
	f_hdr64->e_shoff = __builtin_bswap64(f_hdr64->e_shoff);
	f_hdr64->e_shentsize = __builtin_bswap16(f_hdr64->e_shentsize);
	f_hdr64->e_shnum = __builtin_bswap16(f_hdr64->e_shnum);
	f_hdr64->e_shstrndx = __builtin_bswap16(f_hdr64->e_shstrndx);
}
