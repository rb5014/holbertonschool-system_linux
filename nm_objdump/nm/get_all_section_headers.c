#include "hnm.h"

Elf32_Shdr *get_elf32_all_sct_hdrs(FILE *file, Elf32_Ehdr f_hdr)
{
	int i;
	Elf32_Shdr *s_hdrs = malloc(sizeof(Elf32_Shdr) * f_hdr.e_shnum);

	fseek(file, f_hdr.e_shoff, SEEK_SET);
	fread(s_hdrs, sizeof(Elf32_Shdr), f_hdr.e_shnum, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr.e_shnum; i++)
			convert_elf32_s_hdr_endianness(&s_hdrs[i]);
	}
	return (s_hdrs);
}

Elf64_Shdr *get_elf64_all_sct_hdrs(FILE *file, Elf64_Ehdr f_hdr)
{
	int i;
	Elf64_Shdr *s_hdrs = malloc(sizeof(Elf64_Shdr) * f_hdr.e_shnum);

	fseek(file, f_hdr.e_shoff, SEEK_SET);
	fread(s_hdrs, sizeof(Elf64_Shdr), f_hdr.e_shnum, file);

	if (f_hdr.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		for (i = 0; i < f_hdr.e_shnum; i++)
			convert_elf64_s_hdr_endianness(&s_hdrs[i]);
	}
	return (s_hdrs);
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
