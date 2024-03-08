#include "hnm.h"

void print_elf32_symbols_info(Elf32_Shdr *s_hdrs, Elf32_Sym *symbols,
							  const char strtab[], unsigned long n_symbols)
{
	unsigned long i;
	char type;

	for (i = 0; i < n_symbols; i++)
	{
		type = get_elf32_sym_type(symbols[i].st_info, symbols[i], s_hdrs);
		if (symbols[i].st_name && type != 'f' && type != 'F')
		{
			if ((symbols[i].st_shndx != SHN_UNDEF) && (type != 'w'))
				printf("%08x", symbols[i].st_value);
			else
				printf("        ");
			printf(" %c", type);
			printf(" %s", strtab + symbols[i].st_name);
			printf("\n");
		}

	}
}

void print_elf64_symbols_info(Elf64_Shdr *s_hdrs, Elf64_Sym *symbols,
							  const char strtab[], unsigned long n_symbols)
{
	unsigned long i;
	char type;

	for (i = 0; i < n_symbols; i++)
	{
		type = get_elf64_sym_type(symbols[i].st_info, symbols[i], s_hdrs);
		if (symbols[i].st_name && type != 'f' && type != 'F')
		{
			if ((symbols[i].st_shndx != SHN_UNDEF) && (type != 'w'))
				printf("%016lx", symbols[i].st_value);
			else
				printf("                ");
			printf(" %c", type);
			printf(" %s", strtab + symbols[i].st_name);
			printf("\n");
		}

	}
}
