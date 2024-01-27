#include "main.h"

/**
 * print_elf32_s_hdrs - Print information from the section headers.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 * @s_hdrs32: Array of 32-bit section headers.
 * @names: Array of section names.
 * @types: Array of section types.
 * @flags: Array of section flags.
 *
 * This function prints various information from the section headers
 * for 32-bit ELF files.
 */
void print_elf32_s_hdrs(Elf32_Ehdr f_hdr32, Elf32_Shdr *s_hdrs32,
						char **names, char **types, char **flags)
{
	unsigned int i;

	printf("There are %u section headers, starting at offset 0x%x:\n\n",
		   f_hdr32.e_shnum, f_hdr32.e_shoff);
	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            Addr     Off    Size");
	printf("   ES Flg Lk Inf Al\n");
	for (i = 0; i < f_hdr32.e_shnum; i++)
	{
		printf("  [%*u] %-*s %-*s %08x %06x %06x %02x %*s %*u %*u %*u\n",
			   2, i, 17, names[i], 15, types[i], s_hdrs32[i].sh_addr,
			   s_hdrs32[i].sh_offset, s_hdrs32[i].sh_size, s_hdrs32[i].sh_entsize,
			   3, flags[i], 2, s_hdrs32[i].sh_link, 3, s_hdrs32[i].sh_info,
			   2, s_hdrs32[i].sh_addralign);
	}
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude),");
	printf(" x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific),");
	printf(" p (processor specific)\n");
}

/**
 * print_elf64_s_hdrs - Print various information from ELF64 section headers.
 * @f_hdr64: ELF64_Ehdr structure containing ELF header information.
 * @s_hdrs64: Array of ELF64_Shdr structures.
 * @names: Array of ELF64 section names.
 * @types: Array of ELF64 section types.
 * @flags: Array of ELF64 section flags.
 *
 * Prints various information from ELF64 section headers.
 */
void print_elf64_s_hdrs(Elf64_Ehdr f_hdr64, Elf64_Shdr *s_hdrs64,
						char **names, char **types, char **flags)
{
	unsigned int i;

	printf("There are %u section headers, starting at offset 0x%lx:\n\n",
		   f_hdr64.e_shnum, f_hdr64.e_shoff);
	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            Address");
	printf("          Off    Size");
	printf("   ES Flg Lk Inf Al\n");
	for (i = 0; i < f_hdr64.e_shnum; i++)
	{
		printf("  [%*u] %-*s %-*s %016lx %06lx %06lx %02lx %*s %*u %*u %*lu\n",
			   2, i, 17, names[i], 15, types[i], s_hdrs64[i].sh_addr,
			   s_hdrs64[i].sh_offset, s_hdrs64[i].sh_size, s_hdrs64[i].sh_entsize,
			   3, flags[i], 2, s_hdrs64[i].sh_link, 3, s_hdrs64[i].sh_info,
			   2, s_hdrs64[i].sh_addralign);
	}
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings),");
	printf(" l (large)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude),");
	printf(" x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific),");
	printf(" p (processor specific)\n");
}
