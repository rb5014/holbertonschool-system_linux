#include "main.h"

static dict_t64 sh_flags[] = {
	{SHF_WRITE, "W"},
	{SHF_ALLOC, "A"},
	{SHF_EXECINSTR, "X"},
	{SHF_MERGE, "M"},
	{SHF_STRINGS, "S"},
	{SHF_INFO_LINK, "I"},
	{SHF_LINK_ORDER, "L"},
	{SHF_OS_NONCONFORMING, "O"},
	{SHF_GROUP, "G"},
	{SHF_TLS, "T"},
	{2147483648, "E"},
	{SHF_MASKPROC, "o"},
};

/**
 * binary_32 - Convert a decimal number to binary for 32-bit ELF files.
 * @flags_vals_sep: Pointer to the array storing separated flag values.
 * @num: Decimal number to be converted.
 *
 * This function converts a decimal number to binary and returns
 * the count of set bits in the binary representation.
 *
 * Return: Count of set bits in the binary representation.
 */
unsigned int binary_32(unsigned int **flags_vals_sep, unsigned int num)
{
	unsigned int i, count = 0;

	*flags_vals_sep = NULL;

	for (i = 1024; i > 0; i = i / 2)
	{
		if (num & i)
		{
			count++;
			*flags_vals_sep = realloc(*flags_vals_sep, sizeof(int) * (count));
			(*flags_vals_sep)[count - 1] = num & i;
		}
	}

	return (count);
}

/**
 * get_elf32_s_flags - Get section flags for 32-bit ELF files.
 * @s_hdrs32: Array of 32-bit section headers.
 * @e_shnum: Number of section headers.
 *
 * This function retrieves section flags for 32-bit ELF files.
 *
 * Return: Pointer to an array of section flags.
 */
char **get_elf32_s_flags(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum)
{
	unsigned int i, k, *flags_vals_sep, nb_flags = 0;
	int j;
	char **section_flags;

	section_flags = malloc(e_shnum * sizeof(char *));
	for (i = 0; i < e_shnum; i++)
	{
		section_flags[i] = strdup("");
		if (s_hdrs32[i].sh_flags == 0)
			continue;
		nb_flags = binary_32(&flags_vals_sep, s_hdrs32[i].sh_flags);
		for (j = nb_flags - 1; j >= 0; j--)
		{
			for (k = 0; k < sizeof(sh_flags) / sizeof(sh_flags[0]); k++)
			{
				if (flags_vals_sep[j] == sh_flags[k].value)
				{
					section_flags[i] = realloc(section_flags[i],
										 strlen(section_flags[i]) + 2);
					strcat(section_flags[i], strdup(sh_flags[k].name));
				}
			}
		}
		if (nb_flags != 0)
			free(flags_vals_sep);
	}
	return (section_flags);
}


/**
 * binary_64 - Extract binary values from a 64-bit number.
 * @flags_vals_sep: Pointer to store extracted binary values.
 * @num: 64-bit number to extract binary values from.
 *
 * Extracts binary values from the given 64-bit number and returns the count.
 *
 * Return: Count of extracted binary values.
 */
Elf64_Xword binary_64(Elf64_Xword **flags_vals_sep, Elf64_Xword num)
{
	Elf64_Xword i;
	int count = 0;

	*flags_vals_sep = NULL;

	for (i = 2147483648; i > 0; i = i / 2)
	{
		if (num & i)
		{
			count++;
			*flags_vals_sep = realloc(*flags_vals_sep, sizeof(long int) * (count));
			(*flags_vals_sep)[count - 1] = num & i;
		}
	}

	return (count);
}

/**
 * get_elf64_s_flags - Return array of ELF64 section flags.
 * @s_hdrs64: Array of ELF64_Shdr structures.
 * @e_shnum: Number of ELF sections.
 *
 * Returns an array of ELF64 section flags based on the provided information.
 *
 * Return: Pointer to an array of strings representing section flags.
 */
char **get_elf64_s_flags(Elf64_Shdr *s_hdrs64, Elf32_Half e_shnum)
{
	unsigned long int i, k, nb_flags = 0;
	long int j;
	Elf64_Xword *flags_vals_sep;
	char **section_flags;

	section_flags = malloc(e_shnum * sizeof(char *));
	for (i = 0; i < e_shnum; i++)
	{
		section_flags[i] = strdup("");
		if (s_hdrs64[i].sh_flags == 0)
			continue;
		nb_flags = binary_64(&flags_vals_sep, s_hdrs64[i].sh_flags);
		for (j = nb_flags - 1; j >= 0; j--)
		{
			for (k = 0; k < sizeof(sh_flags) / sizeof(sh_flags[0]); k++)
			{
				if (flags_vals_sep[j] == sh_flags[k].value)
				{

					section_flags[i] = realloc(section_flags[i],
										 strlen(section_flags[i]) + 2);
					strcat(section_flags[i], strdup(sh_flags[k].name));
				}
			}
		}
		if (nb_flags > 0)
			free(flags_vals_sep);
	}
	return (section_flags);
}
