#include "main.h"

/**
 * convert_elf32_endianness - Convert endianness of fields
 *							  in a 32-bit ELF header.
 * @header32: Pointer to the 32-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf32_Half => uint16_t
 * Elf32_Word => uint32_t
 * Elf32_Addr => uint32_t
 * Elf32_Off => uint32_t
 */
void convert_elf32_endianness(Elf32_Ehdr *header32)
{
	header32->e_type = __builtin_bswap16(header32->e_type);
	header32->e_machine = __builtin_bswap16(header32->e_machine);
	header32->e_version = __builtin_bswap32(header32->e_version);
	header32->e_entry = __builtin_bswap32(header32->e_entry);
	header32->e_phoff = __builtin_bswap32(header32->e_phoff);
	header32->e_shoff = __builtin_bswap32(header32->e_shoff);
	header32->e_flags = __builtin_bswap32(header32->e_flags);
	header32->e_ehsize = __builtin_bswap16(header32->e_ehsize);
	header32->e_phentsize = __builtin_bswap16(header32->e_phentsize);
	header32->e_phnum = __builtin_bswap16(header32->e_phnum);
	header32->e_shentsize = __builtin_bswap16(header32->e_shentsize);
	header32->e_shnum = __builtin_bswap16(header32->e_shnum);
	header32->e_shstrndx = __builtin_bswap16(header32->e_shstrndx);

}
/**
 * convert_elf64_endianness - Convert endianness of fields
 *							  in a 64-bit ELF header.
 * @header64: Pointer to the 64-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf64_Half => uint16_t
 * Elf64_Word => uint32_t
 * Elf64_Addr => uint64_t
 * Elf64_Off => uint64_t
 */
void convert_elf64_endianness(Elf64_Ehdr *header64)
{
	header64->e_type = __builtin_bswap16(header64->e_type);
	header64->e_machine = __builtin_bswap16(header64->e_machine);
	header64->e_version = __builtin_bswap32(header64->e_version);
	header64->e_entry = __builtin_bswap64(header64->e_entry);
	header64->e_phoff = __builtin_bswap64(header64->e_phoff);
	header64->e_shoff = __builtin_bswap64(header64->e_shoff);
	header64->e_flags = __builtin_bswap32(header64->e_flags);
	header64->e_ehsize = __builtin_bswap16(header64->e_ehsize);
	header64->e_phentsize = __builtin_bswap16(header64->e_phentsize);
	header64->e_phnum = __builtin_bswap16(header64->e_phnum);
	header64->e_shentsize = __builtin_bswap16(header64->e_shentsize);
	header64->e_shnum = __builtin_bswap16(header64->e_shnum);
	header64->e_shstrndx = __builtin_bswap16(header64->e_shstrndx);
}

/**
 * choose_print_function - Determines the ELF class and calls the appropriate
 *                        ELF header printing function.
 * @file: A pointer to the ELF file.
 * @elf_class: The ELF class retrieved from the ELF file.
 * @endianness: The ELF endianness retrieved from the ELF file.
 * This function reads the system's pointer size to distinguish between
 * 32-bit and 64-bit systems. It then calls the appropriate ELF header
 * printing function based on the detected ELF class. If the system compiles
 * in 32-bit, it uses the 32-bit header printing function even if the ELF class
 * is 64-bit.
 * If the system compiles in 64-bit and the ELF class is also 64-bit,
 * it calls the 64-bit header printing function. If the ELF class is unknown or
 * not supported, it prints an error message.
 */
void choose_print_function(FILE *file, int elf_class, int endianness)
{
	/* system compiles in 32-bit, so even if elf class is 64 it doest matter */
	if ((elf_class == ELFCLASS32) || (sizeof(void *) == 4))
	{
		Elf32_Ehdr header32;

		fread(&header32, sizeof(header32), 1, file);
		if (endianness == ELFDATA2MSB)
			convert_elf32_endianness(&header32);
		print_elf32_header(header32);
	}
	else if ((elf_class == ELFCLASS64) && (sizeof(void *) == 8))
	{
		Elf64_Ehdr header64;

		fread(&header64, sizeof(header64), 1, file);
		if (endianness == ELFDATA2MSB)
			convert_elf64_endianness(&header64);
		print_elf64_header(header64);
	}
	else
		printf("Error class unkown\n");
}

/**
 * get_elf_class - Retrieves the ELF class (32-bit or 64-bit) from an ELF file.
 * @file: A pointer to the ELF file.
 *
 * This function reads the ELF identifier from the given file and returns
 * the ELF class (32-bit or 64-bit). It seeks back to the beginning of the file
 * after reading the ELF identifier to ensure proper file handling.
 *
 * Return: The ELF class (ELFCLASS32 or ELFCLASS64).
 */
int get_elf_class(FILE *file)
{
	unsigned char ident[16];

	/* Read ident to check elf class: 32 or 64*/
	fread(&ident, sizeof(ident), 1, file);
	fseek(file, 0, SEEK_SET);
	return (ident[EI_CLASS]);
}

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
