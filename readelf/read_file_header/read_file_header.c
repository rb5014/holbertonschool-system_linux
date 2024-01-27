#include "read_file_header.h"

/**
 * convert_elf32_file_header_endianness - Convert endianness of fields
 *							  in a 32-bit ELF header.
 * @file_hdr32: Pointer to the 32-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf32_Half => uint16_t
 * Elf32_Word => uint32_t
 * Elf32_Addr => uint32_t
 * Elf32_Off => uint32_t
 */
void convert_elf32_file_header_endianness(Elf32_Ehdr *file_hdr32)
{
	file_hdr32->e_type = __builtin_bswap16(file_hdr32->e_type);
	file_hdr32->e_machine = __builtin_bswap16(file_hdr32->e_machine);
	file_hdr32->e_version = __builtin_bswap32(file_hdr32->e_version);
	file_hdr32->e_entry = __builtin_bswap32(file_hdr32->e_entry);
	file_hdr32->e_phoff = __builtin_bswap32(file_hdr32->e_phoff);
	file_hdr32->e_shoff = __builtin_bswap32(file_hdr32->e_shoff);
	file_hdr32->e_flags = __builtin_bswap32(file_hdr32->e_flags);
	file_hdr32->e_ehsize = __builtin_bswap16(file_hdr32->e_ehsize);
	file_hdr32->e_phentsize = __builtin_bswap16(file_hdr32->e_phentsize);
	file_hdr32->e_phnum = __builtin_bswap16(file_hdr32->e_phnum);
	file_hdr32->e_shentsize = __builtin_bswap16(file_hdr32->e_shentsize);
	file_hdr32->e_shnum = __builtin_bswap16(file_hdr32->e_shnum);
	file_hdr32->e_shstrndx = __builtin_bswap16(file_hdr32->e_shstrndx);

}
/**
 * convert_elf64_file_header_endianness - Convert endianness of fields
 *							  in a 64-bit ELF header.
 * @file_hdr64: Pointer to the 64-bit ELF header structure to be converted.
 *
 * This function swaps the endianness of various fields
 * in the given ELF header, ensuring proper interpretation
 * on systems with different endianness.
 * Elf64_Half => uint16_t
 * Elf64_Word => uint32_t
 * Elf64_Addr => uint64_t
 * Elf64_Off => uint64_t
 */
void convert_elf64_file_header_endianness(Elf64_Ehdr *file_hdr64)
{
	file_hdr64->e_type = __builtin_bswap16(file_hdr64->e_type);
	file_hdr64->e_machine = __builtin_bswap16(file_hdr64->e_machine);
	file_hdr64->e_version = __builtin_bswap32(file_hdr64->e_version);
	file_hdr64->e_entry = __builtin_bswap64(file_hdr64->e_entry);
	file_hdr64->e_phoff = __builtin_bswap64(file_hdr64->e_phoff);
	file_hdr64->e_shoff = __builtin_bswap64(file_hdr64->e_shoff);
	file_hdr64->e_flags = __builtin_bswap32(file_hdr64->e_flags);
	file_hdr64->e_ehsize = __builtin_bswap16(file_hdr64->e_ehsize);
	file_hdr64->e_phentsize = __builtin_bswap16(file_hdr64->e_phentsize);
	file_hdr64->e_phnum = __builtin_bswap16(file_hdr64->e_phnum);
	file_hdr64->e_shentsize = __builtin_bswap16(file_hdr64->e_shentsize);
	file_hdr64->e_shnum = __builtin_bswap16(file_hdr64->e_shnum);
	file_hdr64->e_shstrndx = __builtin_bswap16(file_hdr64->e_shstrndx);
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
		Elf32_Ehdr file_hdr32;

		fread(&file_hdr32, sizeof(file_hdr32), 1, file);
		if (endianness == ELFDATA2MSB)
			convert_elf32_file_header_endianness(&file_hdr32);
		print_elf32_file_header(file_hdr32);
	}
	else if ((elf_class == ELFCLASS64) && (sizeof(void *) == 8))
	{
		Elf64_Ehdr file_hdr64;

		fread(&file_hdr64, sizeof(file_hdr64), 1, file);
		if (endianness == ELFDATA2MSB)
			convert_elf64_file_header_endianness(&file_hdr64);
		print_elf64_file_header(file_hdr64);
	}
	else
		printf("Error class unkown\n");
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
