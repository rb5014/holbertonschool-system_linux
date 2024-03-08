#include "hnm.h"

/**
* get_elf32_sym_type - Get the type of a symbol in a 32-bit ELF file.
*
* This function takes the symbol information, the symbol itself, and an array
* of ELF section headers,
* and determines the type of the symbol. It returns a string representation of
* the symbol's type.
*
* @info: Information about the symbol.
* @sym: The symbol to analyze.
* @shdr: An array of ELF section headers.
* Return: A string representing the symbol's type.
*/
const char get_elf32_sym_type(uint8_t info, Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char type;

	if (ELF32_ST_TYPE(info) == STT_FILE)
		type = 'F';
	else if (ELF32_ST_BIND(info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF32_ST_BIND(info) == STB_WEAK && ELF32_ST_TYPE(info) == STT_OBJECT)
		type = (sym.st_shndx == SHN_UNDEF) ? 'v' : 'V';
	else if (ELF32_ST_BIND(info) == STB_WEAK)
		type = (sym.st_shndx == SHN_UNDEF) ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (sym.st_shndx == SHN_ABS)
		type = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		type = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
			shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
			shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		type = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
			shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		type = 'D';
	else
		type = 'T';

	if (ELF32_ST_BIND(info) == STB_LOCAL)
		type += 32;
	return (type);
}

/**
* get_elf64_sym_type - Get the type of a symbol in a 64-bit ELF file.
*
* This function takes the symbol information, the symbol itself, and an array
* of ELF section headers,
* and determines the type of the symbol. It returns a string representation of
* the symbol's type.
*
* @info: Information about the symbol.
* @sym: The symbol to analyze.
* @shdr: An array of ELF section headers.
* Return: A string representing the symbol's type.
*/
const char get_elf64_sym_type(uint8_t info, Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char type;

	if (ELF64_ST_TYPE(info) == STT_FILE)
		type = 'F';
	else if (ELF64_ST_BIND(info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF64_ST_BIND(info) == STB_WEAK && ELF64_ST_TYPE(info) == STT_OBJECT)
		type = (sym.st_shndx == SHN_UNDEF) ? 'v' : 'V';
	else if (ELF64_ST_BIND(info) == STB_WEAK)
		type = (sym.st_shndx == SHN_UNDEF) ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (sym.st_shndx == SHN_ABS)
		type = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		type = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
			shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
			shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		type = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
			shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		type = 'D';
	else
		type = 'T';

	if (ELF64_ST_BIND(info) == STB_LOCAL)
		type += 32;
	return (type);
}
