#include "hnm.h"

/**
 * convert_elf32_f_hdr_endianness - Convert endianness of fields.
 * @file: Pointer to the ELF file.
 * @f_hdr32: Pointer to the ELF header structure for 32-bit ELF files.
 *
 * This function reads and updates the ELF header information
 * for 32-bit ELF files.
 */
void convert_elf32_f_hdr_endianness(FILE *file, Elf32_Ehdr *f_hdr32)
{
	if (f_hdr32->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		f_hdr32->e_shoff = __builtin_bswap32(f_hdr32->e_shoff);
		f_hdr32->e_shentsize = __builtin_bswap16(f_hdr32->e_shentsize);
		f_hdr32->e_shnum = __builtin_bswap16(f_hdr32->e_shnum);
		f_hdr32->e_shstrndx = __builtin_bswap16(f_hdr32->e_shstrndx);
	}
}

/**
 * convert_elf64_f_hdr_endianness - Convert endianness of fields.
 * @file: Pointer to ELF file.
 * @f_hdr64: Pointer to ELF64_Ehdr structure to store header information.
 *
 * Reads ELF64_Ehdr information from the file and updates f_hdr64.
 *
 */
void convert_elf64_f_hdr_endianness(FILE *file, Elf64_Ehdr *f_hdr64)
{
	if (f_hdr64->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		f_hdr64->e_shoff = __builtin_bswap64(f_hdr64->e_shoff);
		f_hdr64->e_shentsize = __builtin_bswap16(f_hdr64->e_shentsize);
		f_hdr64->e_shnum = __builtin_bswap16(f_hdr64->e_shnum);
		f_hdr64->e_shstrndx = __builtin_bswap16(f_hdr64->e_shstrndx);
	}
}


/**
 * convert_elf32_s_hdr_endianness - Convert endianness of fields.
 * @s_hdr32: Pointer to the 32-bit section header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf32_Word => uint32_t
 * Elf32_Addr => uint32_t
 * Elf32_Off => uint32_t
 */
void convert_elf32_s_hdr_endianness(Elf32_Shdr *s_hdr32)
{
	s_hdr32->sh_name = __builtin_bswap32(s_hdr32->sh_name);
	s_hdr32->sh_type = __builtin_bswap32(s_hdr32->sh_type);
	s_hdr32->sh_flags = __builtin_bswap32(s_hdr32->sh_flags);
	s_hdr32->sh_addr = __builtin_bswap32(s_hdr32->sh_addr);
	s_hdr32->sh_offset = __builtin_bswap32(s_hdr32->sh_offset);
	s_hdr32->sh_size = __builtin_bswap32(s_hdr32->sh_size);
	s_hdr32->sh_link = __builtin_bswap32(s_hdr32->sh_link);
	s_hdr32->sh_info = __builtin_bswap32(s_hdr32->sh_info);
	s_hdr32->sh_addralign = __builtin_bswap32(s_hdr32->sh_addralign);
	s_hdr32->sh_entsize = __builtin_bswap32(s_hdr32->sh_entsize);
}
/**
 * convert_elf64_s_hdr_endianness - Convert endianness of fields.
 * @s_hdr64: Pointer to the 64-bit section header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf64_Word => uint32_t
 * Elf64_XWord => uint64_t
 * Elf64_Addr => uint64_t
 * Elf64_Off => uint64_t
 */
void convert_elf64_s_hdr_endianness(Elf64_Shdr *s_hdr64)
{
	s_hdr64->sh_name = __builtin_bswap32(s_hdr64->sh_name);
	s_hdr64->sh_type = __builtin_bswap32(s_hdr64->sh_type);
	s_hdr64->sh_flags = __builtin_bswap64(s_hdr64->sh_flags);
	s_hdr64->sh_addr = __builtin_bswap64(s_hdr64->sh_addr);
	s_hdr64->sh_offset = __builtin_bswap64(s_hdr64->sh_offset);
	s_hdr64->sh_size = __builtin_bswap64(s_hdr64->sh_size);
	s_hdr64->sh_link = __builtin_bswap32(s_hdr64->sh_link);
	s_hdr64->sh_info = __builtin_bswap32(s_hdr64->sh_info);
	s_hdr64->sh_addralign = __builtin_bswap64(s_hdr64->sh_addralign);
	s_hdr64->sh_entsize = __builtin_bswap64(s_hdr64->sh_entsize);
}
