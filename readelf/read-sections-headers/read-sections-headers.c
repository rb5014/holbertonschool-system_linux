#include "read-sections-headers.h"

/**
 * main - Entry point for the ELF header printing program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * This function serves as the entry point for a program that
 * reads an ELF file, determines its ELF class (32-bit or 64-bit),
 * and prints relevant information from the ELF header.
 * The program expects the path to the ELF file as a command-line
 * argument. If the correct number of arguments is not provided,
 * a usage message is displayed, and the program exits with an error code.
 * It then opens the specified ELF file in binary mode,
 * retrieves the ELF class, and calls the appropriate ELF header
 * printing function.
 * Finally, the file is closed, and the program returns 0.
 *
 * Return: 0 on successful execution, -1 on errors.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	unsigned char ident[16];
	int elf_class, endianness;

	if (argc < 2)
	{
		printf("Usage: ./0-hreadelf prog_path\n");
		return (-1);
	}


	file = fopen(argv[1], "rb");

	if (!file)
		return (-1);


	/* Read ident to check elf class: 32 or 64, and endianness : little or big */
	fread(&ident, sizeof(ident), 1, file);
	fseek(file, 0, SEEK_SET);
	elf_class = ident[EI_CLASS];
	endianness = ident[EI_DATA];

	choose_print_function(file, elf_class, endianness);

	/* finally close the file */
	fclose(file);
	return (0);
}
