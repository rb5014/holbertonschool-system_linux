#include "main.h"

static dict_t64 sh_types[] = {
	{SHT_NULL, "NULL"},
	{SHT_PROGBITS, "PROGBITS"},
	{SHT_SYMTAB, "SYMTAB"},
	{SHT_STRTAB, "STRTAB"},
	{SHT_RELA, "RELA"},
	{SHT_HASH, "HASH"},
	{SHT_DYNAMIC, "DYNAMIC"},
	{SHT_NOTE, "NOTE"},
	{SHT_NOBITS, "NOBITS"},
	{SHT_REL, "REL"},
	{SHT_SHLIB, "SHLIB"},
	{SHT_DYNSYM, "DYNSYM"},
	{SHT_INIT_ARRAY, "INIT_ARRAY"},
	{SHT_FINI_ARRAY, "FINI_ARRAY"},
	{SHT_PREINIT_ARRAY, "PREINIT_ARRAY"},
	{SHT_GROUP, "GROUP"},
	{SHT_SYMTAB_SHNDX, "SYMTAB_SHNDX"},
	{SHT_NUM, "NUM"},
	{SHT_LOOS, "LOOS"},
	{SHT_GNU_ATTRIBUTES, "GNU_ATTRIBUTES"},
	{SHT_GNU_HASH, "GNU_HASH"},
	{SHT_GNU_LIBLIST, "GNU_LIBLIST"},
	{SHT_CHECKSUM, "CHECKSUM"},
	{SHT_LOSUNW, "LOSUNW"},
	{SHT_SUNW_move, "SUNW_move"},
	{SHT_SUNW_COMDAT, "SUNW_COMDAT"},
	{SHT_SUNW_syminfo, "VERDEF"},
	{SHT_GNU_verdef, "VERDEF"},
	{SHT_GNU_verneed, "VERNEED"},
	{SHT_GNU_versym, "VERSYM"},
	{0x6ffffff1, "LOOS+ffffff1"},
	{0x6ffffff3, "LOOS+ffffff3"},
	{SHT_HISUNW, "HISUNW"},
	{SHT_HIOS, "HIOS"},
	{SHT_LOPROC, "LOPROC"},
	{SHT_HIPROC, "HIPROC"},
	{SHT_LOUSER, "LOUSER"},
	{SHT_HIUSER, "HIUSER"}
};

/**
 * get_elf32_s_types - Get section types for 32-bit ELF files.
 * @s_hdrs32: Array of 32-bit section headers.
 * @e_shnum: Number of section headers.
 *
 * This function retrieves section types for 32-bit ELF files.
 *
 * Return: Pointer to an array of section types.
 */
char **get_elf32_s_types(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum)
{
	int i;
	unsigned int j;
	char **section_types = NULL;

	section_types = malloc(e_shnum * sizeof(char *));

	for (i = 0; i < e_shnum; i++)
	{
		section_types[i] = strdup("NULL");
		for (j = 0; j < sizeof(sh_types) / sizeof(sh_types[0]); j++)
		{
			if (s_hdrs32[i].sh_type == sh_types[j].value)
			{
				free(section_types[i]);
				section_types[i] = strdup(sh_types[j].name);
				break;
			}
		}
	}

	return (section_types);
}



/**
 * get_elf64_s_types - Return array of ELF64 section types.
 * @s_hdrs64: Array of ELF64_Shdr structures.
 * @e_shnum: Number of ELF sections.
 *
 * Returns an array of ELF64 section types based on the provided information.
 *
 * Return: Pointer to an array of strings representing section types.
 */
char **get_elf64_s_types(Elf64_Shdr *s_hdrs64, Elf64_Half e_shnum)
{
	long int i;
	unsigned long int j;
	char **section_types = NULL;

	section_types = malloc(e_shnum * sizeof(char *));

	for (i = 0; i < e_shnum; i++)
	{
		section_types[i] = strdup("NULL");
		for (j = 0; j < sizeof(sh_types) / sizeof(sh_types[0]); j++)
		{
			if (s_hdrs64[i].sh_type == sh_types[j].value)
			{
				free(section_types[i]);
				section_types[i] = strdup(sh_types[j].name);
				break;
			}
		}
	}

	return (section_types);
}
