#include "main.h"

/**
 * get_elf32_f_hdr - Read ELF header information for 32-bit ELF files.
 * @file: Pointer to the ELF file.
 * @f_hdr32: Pointer to the ELF header structure for 32-bit ELF files.
 *
 * This function reads and updates the ELF header information
 * for 32-bit ELF files.
 */
void get_elf32_f_hdr(FILE *file, Elf32_Ehdr *f_hdr32)
{

	fread(&(*f_hdr32), 1, sizeof(*f_hdr32), file);
	fseek(file, 0, SEEK_SET);
	if (f_hdr32->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		f_hdr32->e_phoff = __builtin_bswap32(f_hdr32->e_phoff);
		f_hdr32->e_phentsize = __builtin_bswap16(f_hdr32->e_phentsize);
		f_hdr32->e_phnum = __builtin_bswap16(f_hdr32->e_phnum);
	}
}

/**
 * get_elf64_f_hdr - Read ELF64_Ehdr information from file.
 * @file: Pointer to ELF file.
 * @f_hdr64: Pointer to ELF64_Ehdr structure to store header information.
 *
 * Reads ELF64_Ehdr information from the file and updates f_hdr64.
 *
 */
void get_elf64_f_hdr(FILE *file, Elf64_Ehdr *f_hdr64)
{

	fread(&(*f_hdr64), 1, sizeof(*f_hdr64), file);
	fseek(file, 0, SEEK_SET);
	if (f_hdr64->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		f_hdr64->e_phoff = __builtin_bswap64(f_hdr64->e_phoff);
		f_hdr64->e_phentsize = __builtin_bswap16(f_hdr64->e_phentsize);
		f_hdr64->e_phnum = __builtin_bswap16(f_hdr64->e_phnum);
	}
}
