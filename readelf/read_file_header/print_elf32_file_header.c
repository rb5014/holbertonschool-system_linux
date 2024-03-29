#include "read_file_header.h"

static dict_t32 elf32_machine[] = {
	{0x00, "No specific instruction set"},
	{0x01, "AT&T WE 32100"},
	{0x02, "Sparc"},
	{0x03, "Intel 80386"},
	{0x04, "Motorola 68000 (M68k)"},
	{0x05, "Motorola 88000 (M88k)"},
	{0x06, "Intel MCU"},
	{0x07, "Intel 80860"},
	{0x08, "MIPS"},
	{0x09, "IBM System/370"},
	{0x0A, "MIPS RS3000 Little-endian"},
	{0x0B, "Reserved for future use"},
	{0x0C, "Reserved for future use"},
	{0x0D, "Reserved for future use"},
	{0x0E, "Reserved for future use"},
	{0x0F, "Hewlett-Packard PA-RISC"},
	{0x13, "Intel 80960"},
	{0x14, "PowerPC"},
	{0x15, "PowerPC (64-bit)"},
	{0x16, "S390, including S390x"},
	{0x17, "IBM SPU/SPC"},
	{0x18, "Reserved for future use"},
	{0x19, "Reserved for future use"},
	{0x1A, "Reserved for future use"},
	{0x1B, "Reserved for future use"},
	{0x1C, "Reserved for future use"},
	{0x1D, "Reserved for future use"},
	{0x1E, "Reserved for future use"},
	{0x1F, "Reserved for future use"},
	{0x24, "NEC V800"},
	{0x25, "Fujitsu FR20"},
	{0x26, "TRW RH-32"},
	{0x27, "Motorola RCE"},
	{0x28, "Arm (up to Armv7/AArch32)"},
	{0x29, "Digital Alpha"},
	{0x2A, "SuperH"},
	{0x2B, "SPARC Version 9"},
	{0x2C, "Siemens TriCore embedded processor"},
	{0x2D, "Argonaut RISC Core"},
	{0x2E, "Hitachi H8/300"},
	{0x2F, "Hitachi H8/300H"},
	{0x30, "Hitachi H8S"},
	{0x31, "Hitachi H8/500"},
	{0x32, "IA-64"},
	{0x33, "Stanford MIPS-X"},
	{0x34, "Motorola ColdFire"},
	{0x35, "Motorola M68HC12"},
	{0x36, "Fujitsu MMA Multimedia Accelerator"},
	{0x37, "Siemens PCP"},
	{0x38, "Sony nCPU embedded RISC processor"},
	{0x39, "Denso NDR1 microprocessor"},
	{0x3A, "Motorola Star*Core processor"},
	{0x3B, "Toyota ME16 processor"},
	{0x3C, "STMicroelectronics ST100 processor"},
	{0x3D, "Advanced Logic Corp. TinyJ embedded processor family"},
	{0x3E, "Advanced Micro Devices X86-64"},
	{0x3F, "Sony DSP Processor"},
	{0x40, "Digital Equipment Corp. PDP-10"},
	{0x41, "Digital Equipment Corp. PDP-11"},
	{0x42, "Siemens FX66 microcontroller"},
	{0x43, "STMicroelectronics ST9+ 8/16 bit microcontroller"},
	{0x44, "STMicroelectronics ST7 8-bit microcontroller"},
	{0x45, "Motorola MC68HC16 Microcontroller"},
	{0x46, "Motorola MC68HC11 Microcontroller"},
	{0x47, "Motorola MC68HC08 Microcontroller"},
	{0x48, "Motorola MC68HC05 Microcontroller"},
	{0x49, "Silicon Graphics SVx"},
	{0x4A, "STMicroelectronics ST19 8-bit microcontroller"},
	{0x4B, "Digital VAX"},
	{0x4C, "Axis Communications 32-bit embedded processor"},
	{0x4D, "Infineon Technologies 32-bit embedded processor"},
	{0x4E, "Element 14 64-bit DSP Processor"},
	{0x4F, "LSI Logic 16-bit DSP Processor"},
	{0x8C, "TMS320C6000 Family"},
	{0xAF, "MCST Elbrus e2k"},
	{0xB7, "Arm 64-bits (Armv8/AArch64)"},
	{0xDC, "Zilog Z80"},
	{0xF3, "RISC-V"},
	{0xF7, "Berkeley Packet Filter"},
	{0x101, "WDC 65C816"}};

static dict_t32 elf32_type[] = {
	{ET_NONE, "NONE (Unknown)"},
	{ET_REL, "REL (Relocatable file)"},
	{ET_EXEC, "EXEC (Executable file)"},
	{ET_DYN, "DYN (Shared object file)"},
	{ET_CORE, "CORE (Core file)"},
	{ET_LOOS, "LOOS (Reserved inclusive range. Operating system specific.)"},
	{ET_HIOS, "HIOS (Reserved inclusive range. Operating system specific.)"},
	{ET_LOPROC, "LOPROC (Reserved inclusive range. Processor specific.)"},
	{ET_HIPROC, "HIPROC (Reserved inclusive range. Processor specific.)"}};

static const char
*ABI_elf32_list[] = {"System V", "HP-UX", "NetBSD", "Linux", "GNU Hurd",
						   "", "Solaris", "AIX (Monterey)", "IRIX", "FreeBSD",
						   "Tru64", "Novell Modesto", "OpenBSD", "OpenVMS",
						   "NonStop Kernel", "AROS", "FenixOS", "Nuxi CloudABI",
						   "Stratus Technologies OpenVOS"};
/**
 * get_elf32_ABI - Retrieves the OS ABI description
 * based on the ELF header
 * @header: ELF header structure
 *
 * Return: A pointer to the OS ABI description string.
 */
const char *get_elf32_ABI(Elf32_Ehdr header)
{
	size_t len_list_ABI = sizeof(ABI_elf32_list) / sizeof(ABI_elf32_list[0]);

	if (header.e_ident[EI_OSABI] < len_list_ABI)
		return (ABI_elf32_list[header.e_ident[EI_OSABI]]);
	return (NULL);
}

/**
 * get_elf32_machine - Retrieves the machine type description
 * based on the ELF header
 * @header: ELF header structure
 *
 * Return: A pointer to the machine type description string.
 */
const char *get_elf32_machine(Elf32_Ehdr header)
{
	size_t i;

	for (i = 0; i < sizeof(elf32_machine) / sizeof(elf32_machine[0]); i++)
	{
		if (header.e_machine == elf32_machine[i].value)
			return (elf32_machine[i].name);
	}
	return (NULL);
}

/**
 * get_elf32_type - Retrieves the ELF file type description
 * based on the ELF header
 * @header: ELF header structure
 *
 * Return: A pointer to the file type description string.
 */
const char *get_elf32_type(Elf32_Ehdr header)
{
	size_t i;

	for (i = 0; i < sizeof(elf32_type) / sizeof(elf32_type[0]); i++)
	{
		if (header.e_type == elf32_type[i].value)
			return (elf32_type[i].name);
	}
	return ("");
}

/**
 * print_elf32_magic - Prints the ELF magic values from the ELF header
 * @header: ELF header structure
 */
void print_elf32_magic(Elf32_Ehdr header)
{
	int i;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i < 16; i++)
	{
		if (i > 0)
			printf(" ");
		printf("%02x", header.e_ident[i]);
	}
	printf(" \n");
}

/**
 * print_elf32_file_header - Prints various information from the ELF header
 * @header: ELF header structure
 */
void print_elf32_file_header(Elf32_Ehdr header)
{
	const char *ABI = get_elf32_ABI(header);
	const char *type = get_elf32_type(header);
	const char *machine = get_elf32_machine(header);

	print_elf32_magic(header);
	printf("  Class:                             ELF%i\n",
		   header.e_ident[EI_CLASS] == 1 ? 32 : 64);
	printf("  Data:                              2's complement, %s endian\n",
		   header.e_ident[EI_DATA] == 1 ? "little" : "big");
	printf("  Version:                           %d (current)\n",
		   header.e_ident[EI_VERSION]);

	if (ABI)
		printf("  OS/ABI:                            UNIX - %s\n", ABI);
	else
		printf("  OS/ABI:                            <unknown: %x>\n",
			   header.e_ident[EI_OSABI]);
	printf("  ABI Version:                       %d\n",
		   header.e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n", type);
	printf("  Machine:                           %s\n", machine);
	printf("  Version:                           0x%x\n", header.e_version);
	printf("  Entry point address:               0x%x\n", header.e_entry);
	printf("  Start of program headers:          %d (bytes into file)\n",
		   header.e_phoff);
	printf("  Start of section headers:          %u (bytes into file)\n",
		   header.e_shoff);
	printf("  Flags:                             0x%x\n", header.e_flags);
	printf("  Size of this header:               %u (bytes)\n", header.e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n",
		   header.e_phentsize);
	printf("  Number of program headers:         %u\n", header.e_phnum);
	printf("  Size of section headers:           %u (bytes)\n",
		   header.e_shentsize);
	printf("  Number of section headers:         %u\n", header.e_shnum);
	printf("  Section header string table index: %u\n", header.e_shstrndx);
}
