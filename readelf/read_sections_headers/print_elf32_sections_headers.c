#include "read_sections_headers.h"
static dict_t sh_types[] = {
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
	{SHT_HIUSER, "HIUSER"}};

static dict_t sh_flags[] = {
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
	//{SHF_MASKOS, "MASKOS"},
	{SHF_MASKPROC, "o"},
	//{SHF_ORDERED, "ORDERED"},
	{SHF_EXCLUDE, "E"}
};
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

Elf32_Shdr *get_all_elf32_s_headers(FILE *file, int endianness,
									Elf32_Off e_shoff, Elf32_Half e_shentsize, Elf32_Half e_shnum)
{
	int i;
	Elf32_Shdr *s_hdrs32 = malloc(sizeof(Elf32_Shdr) * e_shnum);

	fseek(file, e_shoff, SEEK_SET);
	for (i = 0; i < e_shnum; i++)
	{
		fread(&s_hdrs32[i], 1, e_shentsize, file);
		if (endianness == ELFDATA2MSB)
			convert_elf32_s_hdr_endianness(&s_hdrs32[i]);
	}
	return (s_hdrs32);
}

void get_elf32_s_hdrs_info(FILE *file, int endianness, Elf32_Off *e_shoff,
						   Elf32_Half *e_shentsize, Elf32_Half *e_shnum,
						   Elf32_Half *e_shstrndx)
{
	Elf32_Ehdr file_hdr32;

	fread(&file_hdr32, 1, sizeof(file_hdr32), file);
	fseek(file, 0, SEEK_SET);
	if (endianness == ELFDATA2MSB)
	{
		file_hdr32.e_shoff = __builtin_bswap32(file_hdr32.e_shoff);
		file_hdr32.e_shentsize = __builtin_bswap16(file_hdr32.e_shentsize);
		file_hdr32.e_shnum = __builtin_bswap16(file_hdr32.e_shnum);
		file_hdr32.e_shstrndx = __builtin_bswap16(file_hdr32.e_shstrndx);
	}
	*e_shoff = file_hdr32.e_shoff;
	*e_shentsize = file_hdr32.e_shentsize;
	*e_shnum = file_hdr32.e_shnum;
	*e_shstrndx = file_hdr32.e_shstrndx;
}

char **get_elf32_s_names(FILE *file, int endianness, Elf32_Shdr *s_hdrs32, Elf32_Off e_shoff,
						 Elf32_Half e_shentsize, Elf32_Half e_shnum, Elf32_Half e_shstrndx)
{
	Elf32_Half i;
	Elf32_Shdr sh_strtab_header;
	char *sh_strtab;
	char **section_names;

	fseek(file, e_shoff + e_shentsize * e_shstrndx, SEEK_SET);
	fread(&sh_strtab_header, sizeof(Elf32_Shdr), 1, file);
	if (endianness == ELFDATA2MSB)
		convert_elf32_s_hdr_endianness(&sh_strtab_header);
	sh_strtab = malloc(sh_strtab_header.sh_size);

	fseek(file, sh_strtab_header.sh_offset, SEEK_SET);
	fread(sh_strtab, sh_strtab_header.sh_size, 1, file);
	section_names = malloc(e_shnum * sizeof(char *));

	for (i = 0; i < e_shnum; i++)
	{
		fseek(file, e_shoff + i * e_shentsize, SEEK_SET);

		section_names[i] = strdup(sh_strtab + s_hdrs32[i].sh_name);
	}

	free(sh_strtab);

	return (section_names);
}

char **get_elf32_s_types(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum)
{
	int i, j;
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

int binary(int **flags_vals_sep, int num)
{
	int i, count = 0;
	int cur_flag = 0;

	*flags_vals_sep = NULL;

	for (i = 1024; i > 0; i = i / 2)
	{
		if (num & i)
		{
			count++;
			*flags_vals_sep = realloc(*flags_vals_sep, sizeof(int) * (count));
			(*flags_vals_sep)[count - 1] = num & i;
			cur_flag = num & i;
		}
	}

	return (count);
}

char **get_elf32_s_flags(Elf32_Shdr *s_hdrs32, Elf32_Half e_shnum)
{
	int i, j, k, *flags_vals_sep, nb_flags = 0;
	char **section_flags;

	section_flags = malloc(e_shnum * sizeof(char *));
	for (i = 0; i < e_shnum; i++)
	{
		section_flags[i] = strdup("");
		if (s_hdrs32[i].sh_flags == 0)
			continue;
		nb_flags = binary(&flags_vals_sep, s_hdrs32[i].sh_flags);
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

/**
 * print_elf32_sections_headers - Prints various information
 * from the sections headers
 * @s_hdrs32: section header structure list
 */
void print_elf32_sections_headers(FILE *file, Elf32_Shdr *s_hdrs32, Elf32_Off e_shoff, Elf32_Half e_shentsize,
								  Elf32_Half e_shnum, Elf32_Half e_shstrndx, char **names, char **types, char **flags)
{
	unsigned int i;
	Elf32_Shdr str_tab;

	printf("There are %u section headers, starting at offset 0x%x:\n\n",
		   e_shnum, e_shoff);
	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            Addr     Off    Size");
	printf("   ES Flg Lk Inf Al\n");
	for (i = 0; i < e_shnum; i++)
	{
		printf("  [%*u] %-*s %-*s %08x %06x %06x %02x %*s %*u %*u %*u\n",
			   2, i, 17, names[i], 15, types[i], s_hdrs32[i].sh_addr,
			   s_hdrs32[i].sh_offset, s_hdrs32[i].sh_size, s_hdrs32[i].sh_entsize,
			   3, flags[i], 2, s_hdrs32[i].sh_link, 3, s_hdrs32[i].sh_info,
			   2, s_hdrs32[i].sh_addralign);
	}
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");
}
