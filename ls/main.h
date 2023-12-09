#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/* Define the boolean type*/
typedef int bool;
#define true 1
#define false 0

/*** STRUCTURES ***/
/**
 * struct FileArg - Structure holding the argument name and numerous
 * informations stored in strut stat member
 * @name: Name of the argument
 * @st: Structure filled with argument info generated with lstat function
 * @elements: In the case of a directory,
 *  we can get also all his files in the struct
 * @nb_elem: Number of elements in directory
*/
typedef struct FileArg
{
	char *name;
	struct stat st;
	struct FileArg *elements;
	int nb_elem;
} FileArg;

/**
 * struct Options - Structure holding the options of the program
 * @one_by_line: List one file per line
 * @all: Do not ignore entries starting with .
 * @almost_all: Same as all but do not list implied . and ..
 * @long_listing_format: Use a long listing format
*/
typedef struct Options
{
	bool one_by_line; /* 1 */
	bool all; /* a */
	bool almost_all; /* A */
	bool long_listing_format; /* l */
} Options;
/******************/
void update_options(char *prog_name, char *arg, Options *options);

/*** TOOLS ***/
void *_memcpy(void *dest, const void *src, size_t n);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
/*************/

/*** PARSE ***/
void parse_args(int argc, char *argv[],
				Options *options,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir,
				bool *mult_dirs);

void parse_path(char *prog_name, char *path,
				FileArg **reg_array,
				FileArg **dir_array,
				int *nb_reg,
				int *nb_dir,
				Options *options,
				bool *invalid_file_found);
/*************/

/*** STORE ***/
FileArg *update_array(FileArg file, FileArg **file_array, int nb_elem);
void store_struct(FileArg **array, FileArg *file, int *nb);
void store_dir_struct(char *prog_name, char *path, FileArg **dir_array,
			   FileArg *dir_file, int *nb, Options *options);
/*************/

/*** READ ***/
void read_directory(char *prog_name, char *path,
			FileArg *dir_arg, Options *options);
void read_entries(char *prog_name, DIR *dir, char *dir_path,
				  FileArg *dir_arg, Options *options);
DIR *init_dir(char *prog_name, char *path, char *dir_name);
/************/

/*** PRINT ***/
void print_files(FileArg *reg_array, int nb_reg, Options options);
void print_directories(FileArg *dir_array, int nb_dir,
					   int nb_reg, Options options, bool mult_dirs);
void print_no_opt(FileArg *file_array, int nb);
void print_one_by_line(FileArg *file_array, int nb);
void print_long_listing_format(FileArg *file_array, int nb);
void print_permissions(mode_t st_mode);
void print_time(char *time);
void print_owner(uid_t st_uid);
void print_group(uid_t st_gid);
/*************/


/*** FREE  ***/
void free_files(FileArg **array, int nb);
void free_dirs(FileArg **dir_array, int nb_dir);
void free_all(FileArg **reg_array, FileArg **dir_array,
			  int nb_reg, int nb_dir);
/*************/

#endif /* MAIN_H */
