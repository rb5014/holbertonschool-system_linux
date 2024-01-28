#include "main.h"

/**
 * convert_elf32_p_hdr_endianness - Convert endianness of fields.
 * @p_hdr32: Pointer to the 32-bit section header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf32_Word => uint32_t
 * Elf32_Addr => uint32_t
 * Elf32_Off => uint32_t
 */
void convert_elf32_p_hdr_endianness(Elf32_Phdr *p_hdr32)
{
	p_hdr32->p_type = __builtin_bswap32(p_hdr32->p_type);
	p_hdr32->p_offset = __builtin_bswap32(p_hdr32->p_offset);
	p_hdr32->p_vaddr = __builtin_bswap32(p_hdr32->p_vaddr);
	p_hdr32->p_paddr = __builtin_bswap32(p_hdr32->p_paddr);
	p_hdr32->p_filesz = __builtin_bswap32(p_hdr32->p_filesz);
	p_hdr32->p_memsz = __builtin_bswap32(p_hdr32->p_memsz);
	p_hdr32->p_flags = __builtin_bswap32(p_hdr32->p_flags);
	p_hdr32->p_align = __builtin_bswap32(p_hdr32->p_align);
}
/**
 * convert_elf64_p_hdr_endianness - Convert endianness of fields.
 * @p_hdr64: Pointer to the 64-bit section header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf64_Word => uint32_t
 * Elf64_XWord => uint64_t
 * Elf64_Addr => uint64_t
 * Elf64_Off => uint64_t
 */
void convert_elf64_p_hdr_endianness(Elf64_Phdr *p_hdr64)
{
	p_hdr64->p_type = __builtin_bswap32(p_hdr64->p_type);
	p_hdr64->p_flags = __builtin_bswap32(p_hdr64->p_flags);
	p_hdr64->p_offset = __builtin_bswap64(p_hdr64->p_offset);
	p_hdr64->p_vaddr = __builtin_bswap64(p_hdr64->p_vaddr);
	p_hdr64->p_paddr = __builtin_bswap64(p_hdr64->p_paddr);
	p_hdr64->p_filesz = __builtin_bswap64(p_hdr64->p_filesz);
	p_hdr64->p_memsz = __builtin_bswap64(p_hdr64->p_memsz);
	p_hdr64->p_align = __builtin_bswap64(p_hdr64->p_align);
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
