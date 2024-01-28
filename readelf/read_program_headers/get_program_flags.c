#include "main.h"

/**
 * get_elf32_p_flags - Get program flags for 32-bit ELF files.
 * @p_hdrs32: Array of 32-bit program headers.
 * @e_phnum: Number of program headers.
 *
 * This function retrieves program flags for 32-bit ELF files.
 *
 * Return: Pointer to an array of program flags.
 */
char **get_elf32_p_flags(Elf32_Phdr *p_hdrs32, Elf32_Half e_phnum)
{
	unsigned int i;
	char **program_flags;

	program_flags = malloc(e_phnum * sizeof(char *));
	for (i = 0; i < e_phnum; i++)
	{
		program_flags[i] = strdup("   ");
		if (p_hdrs32[i].p_flags & PF_R)
			program_flags[i][0] = 'R';
		if (p_hdrs32[i].p_flags & PF_W)
			program_flags[i][1] = 'W';
		if (p_hdrs32[i].p_flags & PF_X)
			program_flags[i][2] = 'E';
	}
	return (program_flags);
}

/**
 * get_elf64_p_flags - Get program flags for 64-bit ELF files.
 * @p_hdrs64: Array of 32-bit program headers.
 * @e_phnum: Number of program headers.
 *
 * This function retrieves program flags for 64-bit ELF files.
 *
 * Return: Pointer to an array of program flags.
 */
char **get_elf64_p_flags(Elf64_Phdr *p_hdrs64, Elf64_Half e_phnum)
{
	unsigned long int i;
	char **program_flags;

	program_flags = malloc(e_phnum * sizeof(char *));
	for (i = 0; i < e_phnum; i++)
	{
		program_flags[i] = strdup("   ");
		if (p_hdrs64[i].p_flags & PF_R)
			program_flags[i][0] = 'R';
		if (p_hdrs64[i].p_flags & PF_W)
			program_flags[i][1] = 'W';
		if (p_hdrs64[i].p_flags & PF_X)
			program_flags[i][2] = 'E';
	}
	return (program_flags);
}

