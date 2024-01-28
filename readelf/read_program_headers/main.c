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
	char **p_types, **p_flags, *interp_path, ***segments_s_names;

	/* system compiles in 32-bit, so even if elf class is 64 it doest matter */
	if ((elf_class == ELFCLASS32) || (sizeof(void *) == 4))
	{
		Elf32_Ehdr f_hdr32;
		Elf32_Phdr *p_hdrs32;

		get_elf32_f_hdr(file, &f_hdr32);
		p_hdrs32 = get_all_elf32_p_hdrs(file, f_hdr32);
		p_types = get_elf32_p_types(p_hdrs32, f_hdr32.e_phnum);
		p_flags = get_elf32_p_flags(p_hdrs32, f_hdr32.e_phnum);
		interp_path = get_elf32_interp_path(file, p_hdrs32, f_hdr32.e_phnum);
		segments_s_names = get_elf32_segments_s_names(file, f_hdr32, p_hdrs32);
		print_elf32_p_hdrs(f_hdr32, p_hdrs32, p_types, p_flags, interp_path,
						   segments_s_names);
		free_array(&p_types, f_hdr32.e_phnum);
		free_array(&p_flags, f_hdr32.e_phnum);
		free(p_hdrs32);
	}
	else if ((elf_class == ELFCLASS64) && (sizeof(void *) == 8))
	{
		Elf64_Ehdr f_hdr64;
		Elf64_Phdr *p_hdrs64;

		get_elf64_f_hdr(file, &f_hdr64);
		p_hdrs64 = get_all_elf64_p_hdrs(file, f_hdr64);
		p_types = get_elf64_p_types(p_hdrs64, f_hdr64.e_phnum);
		p_flags = get_elf64_p_flags(p_hdrs64, f_hdr64.e_phnum);
		print_elf64_p_hdrs(f_hdr64, p_hdrs64, p_types, p_flags);

		free_array(&p_types, f_hdr64.e_phnum);
		free_array(&p_flags, f_hdr64.e_phnum);
		free(p_hdrs64);
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
		printf("Usage: ./2-hreadelf prog_path\n");
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
