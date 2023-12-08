#include "main.h"

/**
 * update_options - Update the Option (defined in "main.h") structure members
 * @prog_name: Name of the program
 * @arg: Argument containing the options code
 * @options: Option structure to be updated
*/
void update_options(char *prog_name, char *arg, Options *options)
{
	int i;

	for (i = 0; arg[i] != '\0'; i++)
	{
		switch (arg[i])
		{
			case '1':
				options->one_by_line = true;
				break;

			case 'a':
				options->all = true;
				break;

			case 'A':
				options->almost_all = true;
				break;

			case 'l':
				options->long_listing_format = true;
				break;

			default:
				fprintf(stderr, "%s: invalid option -- '%c'\n",
						prog_name, arg[i]);
				fprintf(stderr, "Try '%s --help' for more information.\n",
						prog_name);
				exit(EXIT_FAILURE);
		}
	}
}


/**
 * main - Entry point for the "hls" program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Description:
 *   This function serves as the entry point for the "hls" program.
 *   It lists the content of a specified directory in lexicographical order.
 *   If no directory is provided,
 *   it lists the content of the current directory.
 *
 * Usage:
 *   hls [directory_path]
 *
 * Return:
 *   0 on success.
 */
int main(int argc, char *argv[])
{
	/* FileArg structure defined in "main.h" */
	FileArg *reg_array = NULL;
	FileArg *dir_array = NULL;
	int nb_reg = 0;
	int nb_dir = 0;

	/* Options structure defined in "main.h" */
	Options options;

	options.one_by_line = false;
	options.all = false;
	options.almost_all = false;
	options.long_listing_format = false;

	parse_args(argc, argv, &options, &reg_array, &dir_array, &nb_reg, &nb_dir);

	if (nb_reg > 0)
		print_files(reg_array, nb_reg, options);

	if (nb_dir > 0)
		print_directories(dir_array, nb_dir, options);

	free_all(&reg_array, &dir_array, nb_reg, nb_dir);

	return (0);
}
