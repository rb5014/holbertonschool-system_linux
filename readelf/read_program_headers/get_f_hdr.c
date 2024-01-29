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
		convert_elf32_file_header_endianness(f_hdr32);
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
		convert_elf64_file_header_endianness(f_hdr64);
}

/**
 * convert_elf32_file_header_endianness - Convert endianness of fields
 *							  in a 32-bit ELF header.
 * @file_hdr32: Pointer to the 32-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf32_Half => uint16_t
 * Elf32_Word => uint32_t
 * Elf32_Addr => uint32_t
 * Elf32_Off => uint32_t
 */
void convert_elf32_file_header_endianness(Elf32_Ehdr *file_hdr32)
{
	file_hdr32->e_type = __builtin_bswap16(file_hdr32->e_type);
	file_hdr32->e_machine = __builtin_bswap16(file_hdr32->e_machine);
	file_hdr32->e_version = __builtin_bswap32(file_hdr32->e_version);
	file_hdr32->e_entry = __builtin_bswap32(file_hdr32->e_entry);
	file_hdr32->e_phoff = __builtin_bswap32(file_hdr32->e_phoff);
	file_hdr32->e_shoff = __builtin_bswap32(file_hdr32->e_shoff);
	file_hdr32->e_flags = __builtin_bswap32(file_hdr32->e_flags);
	file_hdr32->e_ehsize = __builtin_bswap16(file_hdr32->e_ehsize);
	file_hdr32->e_phentsize = __builtin_bswap16(file_hdr32->e_phentsize);
	file_hdr32->e_phnum = __builtin_bswap16(file_hdr32->e_phnum);
	file_hdr32->e_shentsize = __builtin_bswap16(file_hdr32->e_shentsize);
	file_hdr32->e_shnum = __builtin_bswap16(file_hdr32->e_shnum);
	file_hdr32->e_shstrndx = __builtin_bswap16(file_hdr32->e_shstrndx);

}
/**
 * convert_elf64_file_header_endianness - Convert endianness of fields
 *							  in a 64-bit ELF header.
 * @file_hdr64: Pointer to the 64-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf64_Half => uint16_t
 * Elf64_Word => uint32_t
 * Elf64_Addr => uint64_t
 * Elf64_Off => uint64_t
 */
void convert_elf64_file_header_endianness(Elf64_Ehdr *file_hdr64)
{
	file_hdr64->e_type = __builtin_bswap16(file_hdr64->e_type);
	file_hdr64->e_machine = __builtin_bswap16(file_hdr64->e_machine);
	file_hdr64->e_version = __builtin_bswap32(file_hdr64->e_version);
	file_hdr64->e_entry = __builtin_bswap64(file_hdr64->e_entry);
	file_hdr64->e_phoff = __builtin_bswap64(file_hdr64->e_phoff);
	file_hdr64->e_shoff = __builtin_bswap64(file_hdr64->e_shoff);
	file_hdr64->e_flags = __builtin_bswap32(file_hdr64->e_flags);
	file_hdr64->e_ehsize = __builtin_bswap16(file_hdr64->e_ehsize);
	file_hdr64->e_phentsize = __builtin_bswap16(file_hdr64->e_phentsize);
	file_hdr64->e_phnum = __builtin_bswap16(file_hdr64->e_phnum);
	file_hdr64->e_shentsize = __builtin_bswap16(file_hdr64->e_shentsize);
	file_hdr64->e_shnum = __builtin_bswap16(file_hdr64->e_shnum);
	file_hdr64->e_shstrndx = __builtin_bswap16(file_hdr64->e_shstrndx);
}
