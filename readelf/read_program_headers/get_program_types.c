#include "main.h"

static dict_t64 ph_types[] = {
	{PT_NULL, "NULL"},
	{PT_LOAD, "LOAD"},
	{PT_DYNAMIC, "DYNAMIC"},
	{PT_INTERP, "INTERP"},
	{PT_NOTE, "NOTE"},
	{PT_SHLIB, "SHLIB"},
	{PT_PHDR, "PHDR"},
	{PT_TLS, "TLS"},
	{PT_NUM, "NUM"},
	{PT_LOOS, "LOOS"},
	{PT_GNU_EH_FRAME, "GNU_EH_FRAME"},
	{PT_GNU_STACK, "GNU_STACK"},
	{PT_GNU_RELRO, "GNU_RELRO"},
	{PT_LOSUNW, "LOSUNW"},
	{PT_SUNWBSS, "SUNWBSS"},
	{PT_SUNWSTACK, "SUNWSTACK"},
	{PT_HISUNW, "HISUNW"},
	{PT_HIOS, "HIOS"},
	{PT_LOPROC, "LOPROC"},
	{PT_HIPROC, "HIPROC"}
};

/**
 * get_elf32_p_types - Get program types for 32-bit ELF files.
 * @p_hdrs32: Array of 32-bit program headers.
 * @e_phnum: Number of program headers.
 *
 * This function retrieves program types for 32-bit ELF files.
 *
 * Return: Pointer to an array of program types.
 */
char **get_elf32_p_types(Elf32_Phdr *p_hdrs32, Elf32_Half e_phnum)
{
	int i;
	unsigned int j;
	char **program_types = NULL;

	program_types = malloc(e_phnum * sizeof(char *));

	for (i = 0; i < e_phnum; i++)
	{
		program_types[i] = strdup("NULL");
		for (j = 0; j < sizeof(ph_types) / sizeof(ph_types[0]); j++)
		{
			if (p_hdrs32[i].p_type == ph_types[j].value)
			{
				free(program_types[i]);
				program_types[i] = strdup(ph_types[j].name);
				break;
			}
		}
		if ((strcmp(program_types[i], "NULL") == 0) &&
			((p_hdrs32[i].p_type & PT_LOOS) == PT_LOOS))
		{
			program_types[i] = realloc(program_types[i],
								   sizeof(char *) * (strlen("LOOS") + 8 + 1));
			sprintf(program_types[i], "LOOS+%x", p_hdrs32[i].p_type - PT_LOOS);
		}
	}

	return (program_types);
}

/**
 * get_elf64_p_types - Return array of ELF64 program types.
 * @p_hdrs64: Array of ELF64_Phdr structures.
 * @e_phnum: Number of ELF programs.
 *
 * Returns an array of ELF64 program types based on the provided information.
 *
 * Return: Pointer to an array of strings representing program types.
 */
char **get_elf64_p_types(Elf64_Phdr *p_hdrs64, Elf64_Half e_phnum)
{
	long int i;
	unsigned long int j;
	char **program_types = NULL;

	program_types = malloc(e_phnum * sizeof(char *));

	for (i = 0; i < e_phnum; i++)
	{
		program_types[i] = strdup("NULL");
		for (j = 0; j < sizeof(ph_types) / sizeof(ph_types[0]); j++)
		{
			if (p_hdrs64[i].p_type == ph_types[j].value)
			{
				free(program_types[i]);
				program_types[i] = strdup(ph_types[j].name);
				break;
			}
		}
		if ((strcmp(program_types[i], "NULL") == 0) &&
			((p_hdrs64[i].p_type & PT_LOOS) == PT_LOOS))
		{
			program_types[i] = realloc(program_types[i],
									sizeof(char *) * (strlen("LOOS") + 8 + 1));
			sprintf(program_types[i], "LOOS+%x", p_hdrs64[i].p_type - PT_LOOS);
		}
	}

	return (program_types);
}
