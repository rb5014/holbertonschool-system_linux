#include "hnm.h"

/**
 * get_elf32_sym_structs - Get symbol structs for 32-bit ELF files.
 * @file: Pointer to the ELF file.
 * @f_hdr: ELF header structure for 32-bit ELF files.
 * @symtab_hdr: ".symtab" section header.
 * @n_symbols: Number of symbols of the file
 *
 * Return: Pointer to an "array" of Elf32_Sym structs.
 */
Elf32_Sym *get_elf32_sym_structs(FILE *file, Elf32_Ehdr f_hdr,
								 Elf32_Shdr symtab_hdr, unsigned long n_symbols)
{
	unsigned long i;
	Elf32_Sym *symbols = malloc(sizeof(Elf32_Sym) * n_symbols);

	fseek(file, symtab_hdr.sh_offset, SEEK_SET);
	fread(symbols, sizeof(Elf32_Sym), n_symbols, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < n_symbols; i++)
		{
			symbols[i].st_name = __builtin_bswap32(symbols[i].st_name);
			symbols[i].st_value = __builtin_bswap32(symbols[i].st_value);
			symbols[i].st_size = __builtin_bswap32(symbols[i].st_size);
			symbols[i].st_shndx = __builtin_bswap16(symbols[i].st_shndx);
		}
	}

	return (symbols);
}


/**
 * get_elf64_sym_structs - Get symbol structs for 64-bit ELF files.
 * @file: Pointer to the ELF file.
 * @f_hdr: ELF header structure for 64-bit ELF files.
 * @symtab_hdr: ".symtab" section header.
 * @n_symbols: Number of symbols of the file
 *
 * Return: Pointer to an "array" of Elf64_Sym structs.
 */
Elf64_Sym *get_elf64_sym_structs(FILE *file, Elf64_Ehdr f_hdr,
								 Elf64_Shdr symtab_hdr, unsigned long n_symbols)
{
	unsigned long i;

	Elf64_Sym *symbols = malloc(sizeof(Elf64_Sym) * n_symbols);

	fseek(file, symtab_hdr.sh_offset, SEEK_SET);
	fread(symbols, sizeof(Elf64_Sym), n_symbols, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < n_symbols; i++)
		{
			symbols[i].st_name = __builtin_bswap32(symbols[i].st_name);
			symbols[i].st_value = __builtin_bswap64(symbols[i].st_value);
			symbols[i].st_size = __builtin_bswap64(symbols[i].st_size);
			symbols[i].st_shndx = __builtin_bswap16(symbols[i].st_shndx);
		}
	}

	return (symbols);
}
