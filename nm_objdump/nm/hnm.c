#include "hnm.h"

static char *file_path;

void process_elf32(FILE *file)
{
	int i;
	char *strtab;
	unsigned long n_symbols;
	Elf32_Ehdr f_hdr;
	Elf32_Shdr *s_hdrs, sym_hdrs[2]; /* Contains symtab and strtab headers*/
	Elf32_Sym *symbols; /* Array of Elf32_Sym structs*/

	f_hdr = get_elf32_f_hdr(file);
	s_hdrs = get_elf32_all_sct_hdrs(file, f_hdr);
	get_elf32_sym_hdrs(file, f_hdr, s_hdrs, sym_hdrs);

	if (sym_hdrs[0].sh_entsize == 0)
		fprintf(stderr, "hnm: %s: no symbols\n", file_path);
	else
	{
		n_symbols = sym_hdrs[0].sh_size / sym_hdrs[0].sh_entsize;
		symbols = get_elf32_sym_structs(file, f_hdr, sym_hdrs[0], n_symbols);
		strtab = get_elf32_strtab(file, sym_hdrs[1]);
		print_elf32_symbols_info(s_hdrs, symbols, strtab, n_symbols);
		free(symbols);
		free(strtab);
	}
	free(s_hdrs);
}

void process_elf64(FILE *file)
{
	int i;
	char *strtab;
	unsigned long n_symbols;
	Elf64_Ehdr f_hdr;
	Elf64_Shdr *s_hdrs, sym_hdrs[2]; /* Contains symtab and strtab headers*/
	Elf64_Sym *symbols; /* Array of Elf32_Sym structs*/

	f_hdr = get_elf64_f_hdr(file);
	s_hdrs = get_elf64_all_sct_hdrs(file, f_hdr);
	get_elf64_sym_hdrs(file, f_hdr, s_hdrs, sym_hdrs);

	if (sym_hdrs[0].sh_entsize == 0)
		fprintf(stderr, "hnm: %s: no symbols\n", file_path);
	else
	{
		n_symbols = sym_hdrs[0].sh_size / sym_hdrs[0].sh_entsize;
		symbols = get_elf64_sym_structs(file, f_hdr, sym_hdrs[0], n_symbols);
		strtab = get_elf64_strtab(file, sym_hdrs[1]);
		print_elf64_symbols_info(s_hdrs, symbols, strtab, n_symbols);
		free(symbols);
		free(strtab);
	}
	free(s_hdrs);
}


/**
 * choose_print_function - Determines ELF class and calls appropriate header
 *                         printing function.
 * @file: Pointer to the ELF file.
 * @elf_class: ELF class retrieved from the ELF file.
 *
 * This function reads the system's pointer size to distinguish between 32-bit
 * and 64-bit systems. Calls the appropriate ELF header printing function
 * based on the detected ELF class. If the system compiles in 32-bit, it uses
 * the 32-bit header printing function even if the ELF class is 64-bit. If the
 * system compiles in 64-bit and the ELF class is also 64-bit, it calls the
 * 64-bit header printing function. If the ELF class is unknown or not
 * supported, it prints an error message.
 */
void choose_print_function(FILE *file, int elf_class)
{
	/* system compiles in 32-bit, so even if elf class is 64 it doest matter */
	if ((elf_class == ELFCLASS32) || (sizeof(void *) == 4))
	{
		process_elf32(file);
	}
	else if ((elf_class == ELFCLASS64) && (sizeof(void *) == 8))
	{
		process_elf64(file);
	}
	else
		printf("Error class unkown\n");
}

/**
 * main - Entry point for the ELF header printing program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Serves as the entry point for a program that reads an ELF file, determines
 * its ELF class (32-bit or 64-bit), and prints relevant information from the
 * ELF header. Expects the path to the ELF file as a command-line argument. If
 * the correct number of arguments is not provided, a usage message is
 * displayed, and the program exits with an error code. Opens the specified ELF
 * file in binary mode, retrieves the ELF class, and calls the appropriate ELF
 * header printing function. Finally, closes the file,
 * and the program returns 0.
 *
 * Return: 0 on successful execution, -1 on errors.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	unsigned char ident[16];
	int elf_class;

	if (argc < 2)
	{
		printf("Usage: ./hnm prog_path\n");
		argv[1] = "./test/executables/vgpreload_memcheck-x86-linux.so";
	}

	file_path = argv[1];

	file = fopen(argv[1], "rb");
	/* Read ident to check elf class: 32 or 64, and endianness : little or big */
	fseek(file, 0, SEEK_SET);
	fread(&ident, 1, sizeof(ident), file);
	elf_class = ident[EI_CLASS];

	choose_print_function(file, elf_class);

	/* finally close the file */
	fclose(file);
	return (0);
}
