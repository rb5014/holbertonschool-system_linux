#include "main.h"

/**
 * print_elf32_p_hdrs - Print information from the program headers.
 * @f_hdr32: ELF header structure for 32-bit ELF files.
 * @p_hdrs32: Array of 32-bit program headers.
 * @types: Array of program types.
 * @flags: Array of program flags.
 * @interp_path: String containing the interpreter path.
 * @segment_s_names: Array of arrays of strings containing the name of sections
 * of each segment
 * This function prints various information from the program headers
 * for 32-bit ELF files.
 */
void print_elf32_p_hdrs(Elf32_Ehdr f_hdr32, Elf32_Phdr *p_hdrs32,
						char **types, char **flags, char *interp_path, char ***segment_s_names)
{
	unsigned int i, j;

	if (f_hdr32.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}
	printf("\nElf file type is %s\n", get_elf32_type(f_hdr32));
	printf("Entry point 0x%x\n", f_hdr32.e_entry);
	printf("There are %u program headers, starting at offset %u\n\n",
		   f_hdr32.e_phnum, f_hdr32.e_phoff);
	printf("Program Headers:\n");
	printf("  Type           Offset   VirtAddr   PhysAddr");
	printf("   FileSiz MemSiz  Flg Align\n");
	for (i = 0; i < f_hdr32.e_phnum; i++)
	{
		printf("  %-*s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %s %s%x\n",
			   14, types[i], p_hdrs32[i].p_offset, p_hdrs32[i].p_vaddr,
			   p_hdrs32[i].p_paddr, p_hdrs32[i].p_filesz, p_hdrs32[i].p_memsz,
			   flags[i], p_hdrs32[i].p_align ? "0x" : "", p_hdrs32[i].p_align);
		if (p_hdrs32[i].p_type == PT_INTERP)
		{
			printf("      ");
			printf("[Requesting program interpreter: %s]\n", interp_path);
		}
	}
	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	for (i = 0; i < f_hdr32.e_phnum; i++)
	{
		printf("   %02d     ", i);
		for (j = 0; segment_s_names[i][j] != NULL; j++)
		{
			printf("%s", segment_s_names[i][j]);
			printf("%s", strcmp(segment_s_names[i][j], "")  ? " " : "");
		}
		puts("");
	}
}

/**
 * print_elf64_p_hdrs - Print various information from ELF64 program headers.
 * @f_hdr64: ELF64_Ehdr structure containing ELF header information.
 * @p_hdrs64: Array of ELF64_Phdr structures.
 * @types: Array of ELF64 program types.
 * @flags: Array of ELF64 program flags.
 * @interp_path: String containing the interpreter path.
 * @segment_s_names: Array of arrays of strings containing the name of sections
 * of each segment
 * Prints various information from ELF64 program headers.
 */
void print_elf64_p_hdrs(Elf64_Ehdr f_hdr64, Elf64_Phdr *p_hdrs64,
						char **types, char **flags, char *interp_path, char ***segment_s_names)
{
	unsigned int i, j;

	if (f_hdr64.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}
	printf("\nElf file type is %s\n", get_elf64_type(f_hdr64));
	printf("Entry point 0x%lx\n", f_hdr64.e_entry);
	printf("There are %u program headers, starting at offset %lu\n\n",
		   f_hdr64.e_phnum, f_hdr64.e_phoff);
	printf("Program Headers:\n");
	printf("  Type           Offset   VirtAddr           PhysAddr");
	printf("           FileSiz  MemSiz   Flg Align\n");
	for (i = 0; i < f_hdr64.e_phnum; i++)
	{
		printf("  %-*s 0x%06lx 0x%016lx 0x%016lx 0x%06lx 0x%06lx %s %s%lx\n",
			   14, types[i], p_hdrs64[i].p_offset, p_hdrs64[i].p_vaddr,
			   p_hdrs64[i].p_paddr, p_hdrs64[i].p_filesz, p_hdrs64[i].p_memsz,
			   flags[i], p_hdrs64[i].p_align ? "0x" : "", p_hdrs64[i].p_align);
		if (p_hdrs64[i].p_type == PT_INTERP)
		{
			printf("      ");
			printf("[Requesting program interpreter: %s]\n", interp_path);
		}
	}
	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	for (i = 0; i < f_hdr64.e_phnum; i++)
	{
		printf("   %02d     ", i);
		for (j = 0; segment_s_names[i][j] != NULL; j++)
		{
			printf("%s", segment_s_names[i][j]);
			printf("%s", strcmp(segment_s_names[i][j], "")  ? " " : "");
		}
		puts("");
	}
}
