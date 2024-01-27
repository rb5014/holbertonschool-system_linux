#include "main.h"

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
	char **s_names, **s_types, **s_flags;

	/* system compiles in 32-bit, so even if elf class is 64 it doest matter */
	if ((elf_class == ELFCLASS32) || (sizeof(void *) == 4))
	{
		Elf32_Ehdr f_hdr32;
		Elf32_Shdr *s_hdrs32;

		get_elf32_s_hdrs_info(file, &f_hdr32);
		s_hdrs32 = get_all_elf32_s_hdrs(file, f_hdr32);
		s_names = get_elf32_s_names(file, f_hdr32, s_hdrs32);
		s_types = get_elf32_s_types(s_hdrs32, f_hdr32.e_shnum);
		s_flags = get_elf32_s_flags(s_hdrs32, f_hdr32.e_shnum);
		print_elf32_s_hdrs(f_hdr32, s_hdrs32, s_names, s_types, s_flags);
		free_array(&s_names, f_hdr32.e_shnum);
		free_array(&s_types, f_hdr32.e_shnum);
		free_array(&s_flags, f_hdr32.e_shnum);
		free(s_hdrs32);
	}
	else if ((elf_class == ELFCLASS64) && (sizeof(void *) == 8))
	{
		Elf64_Ehdr f_hdr64;
		Elf64_Shdr *s_hdrs64;

		get_elf64_s_hdrs_info(file, &f_hdr64);

		s_hdrs64 = get_all_elf64_s_hdrs(file, f_hdr64);
		s_names = get_elf64_s_names(file, f_hdr64, s_hdrs64);
		s_types = get_elf64_s_types(s_hdrs64, f_hdr64.e_shnum);
		s_flags = get_elf64_s_flags(s_hdrs64, f_hdr64.e_shnum);
		print_elf64_s_hdrs(f_hdr64, s_hdrs64, s_names, s_types, s_flags);
		free_array(&s_names, f_hdr64.e_shnum);
		free_array(&s_types, f_hdr64.e_shnum);
		free_array(&s_flags, f_hdr64.e_shnum);
		free(s_hdrs64);
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
		printf("Usage: ./1-hreadelf prog_path\n");
		argv[1] = "./tests/exe/solaris32";
	}


	file = fopen(argv[1], "rb");

	if (!file)
		return (-1);


	/* Read ident to check elf class: 32 or 64, and endianness : little or big */
	fread(&ident, 1, sizeof(ident), file);
	fseek(file, 0, SEEK_SET);
	elf_class = ident[EI_CLASS];

	choose_print_function(file, elf_class);

	/* finally close the file */
	fclose(file);
	return (0);
}
