#include "read_sections_headers.h"
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

Elf64_Shdr *get_all_elf64_s_headers(FILE *file, int endianness,
			Elf64_Off e_shoff, Elf64_Half e_shentsize, Elf64_Half e_shnum)
{
	int i;
	Elf64_Shdr *s_hdrs64 = malloc(sizeof(Elf64_Shdr) * e_shnum);

	fseek(file, e_shoff, SEEK_SET);
	for (i = 0; i < e_shnum; i++)
	{
		fread(&s_hdrs64[i], e_shentsize, 1, file);
		fseek(file, e_shentsize, SEEK_CUR);
		if (endianness == ELFDATA2MSB)
			convert_elf64_s_hdr_endianness(&s_hdrs64[i]);
	}
	return (s_hdrs64);
}

void get_elf64_s_hdrs_info(FILE *file, int endianness, Elf64_Off *e_shoff,
						   Elf64_Half *e_shentsize, Elf64_Half *e_shnum,
						   Elf64_Half *e_shstrndx)
{
	Elf64_Ehdr file_hdr64;

	fread(&file_hdr64, sizeof(file_hdr64), 1, file);
	fseek(file, 0, SEEK_SET);
	if (endianness == ELFDATA2MSB)
	{
		file_hdr64.e_shoff = __builtin_bswap32(file_hdr64.e_shoff);
		file_hdr64.e_shentsize = __builtin_bswap16(file_hdr64.e_shentsize);
		file_hdr64.e_shnum = __builtin_bswap16(file_hdr64.e_shnum);
		file_hdr64.e_shstrndx = __builtin_bswap16(file_hdr64.e_shstrndx);
	}
	*e_shoff = file_hdr64.e_shoff;
	*e_shentsize = file_hdr64.e_shentsize;
	*e_shnum = file_hdr64.e_shnum;
	*e_shstrndx = file_hdr64.e_shstrndx;
}

/**
 * print_elf64_sections_headers - Prints various information
 * from the sections headers
 * @s_hdrs64: sections header structure list
 */
void print_elf64_sections_headers(Elf64_Shdr *s_hdrs64, Elf64_Off e_shoff,
								  Elf64_Half e_shnum, Elf64_Half e_shstrndx)
{

	e_shstrndx = e_shstrndx;
	s_hdrs64 = s_hdrs64;

	printf("There are %u section headers, starting at offset 0x%lx:\n",
	e_shnum, e_shoff);
	printf("Section Headers:\n");

}
