#include "main.h"

static dict_t32 type[] = {
	{ET_NONE, "NONE (Unknown)"},
	{ET_REL, "REL (Relocatable file)"},
	{ET_EXEC, "EXEC (Executable file)"},
	{ET_DYN, "DYN (Shared object file)"},
	{ET_CORE, "CORE (Core file)"},
	{ET_LOOS, "LOOS (Reserved inclusive range. Operating system specific.)"},
	{ET_HIOS, "HIOS (Reserved inclusive range. Operating system specific.)"},
	{ET_LOPROC, "LOPROC (Reserved inclusive range. Processor specific.)"},
	{ET_HIPROC, "HIPROC (Reserved inclusive range. Processor specific.)"}
};

/**
 * get_elf32_type - Retrieves the ELF file type description
 * based on the ELF header
 * @header: ELF header structure
 *
 * Return: A pointer to the file type description string.
 */
const char *get_elf32_type(Elf32_Ehdr header)
{
	size_t i;

	for (i = 0; i < sizeof(type) / sizeof(type[0]); i++)
	{
		if (header.e_type == type[i].value)
			return (type[i].name);
	}
	return ("");
}

/**
 * get_elf64_type - Retrieves the ELF file type description
 * based on the ELF header
 * @header: ELF header structure
 *
 * Return: A pointer to the file type description string.
 */
const char *get_elf64_type(Elf64_Ehdr header)
{
	size_t i;

	for (i = 0; i < sizeof(type) / sizeof(type[0]); i++)
	{
		if (header.e_type == type[i].value)
			return (type[i].name);
	}
	return ("");
}
