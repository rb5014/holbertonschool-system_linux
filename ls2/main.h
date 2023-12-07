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

/* Define the boolean type*/
typedef int bool;
#define true 1
#define false 0


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

#endif /* MAIN_H */
