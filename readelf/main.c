#include "main.h"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * Return: 0
 */
int main(int argc, char *argv[])
{
	/* Either Elf64_Ehdr or Elf32_Ehdr depending on architecture */
	ElfW(Ehdr) header;
	FILE *file;

	if (argc < 2)
		return (-1);

	file = fopen(argv[1], "rb");

	if (!file)
		return (-1);

	/* read the header */
	fread(&header, sizeof(header), 1, file);

	/* check so its really an elf file */
	if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0)
	{
		print_elf_header(header);
	}

	/* finally close the file */
	fclose(file);
	return (0);
}
