#include "custom_functions.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/**
 * _tolower - Convert a character to lowercase.
 * @c: The character to be converted.
 *
 * Return: The lowercase equivalent of the character if it is an uppercase
 *         letter; otherwise, the original character.
 */
char _tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	else
	{
		return (c);
	}
}

/**
 * _strcmp_icase - Case-insensitive string comparison.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 if strings are equal, positive if the first non-matching character
 * in s1 is greater than that of s2, negative otherwise.
 */
int _strcmp_icase(const char *s1, const char *s2)
{
	while (*s1 != '\0'
	&& _tolower((unsigned char)*s1) == _tolower((unsigned char)*s2))
	{
		s1++;
		s2++;
	}

	return (_tolower((unsigned char)*s1) - _tolower((unsigned char)*s2));
}

/**
 * _strcmp- string comparison.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 if strings are equal, positive if the first non-matching character
 * in s1 is greater than that of s2, negative otherwise.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return ((unsigned char) *s1 - (unsigned char) *s2);
}
/**
 * compare_names - Compare two strings alphabetically.
 * @a: First string.
 * @b: Second string.
 *
 * Return: 0 if strings are equal, positive if the first non-matching character
 * in a is greater than that of b, negative otherwise.
 */
int compare_names(const void *a, const void *b)
{
	return (_strcmp_icase(*(const char **)a, *(const char **)b));
}

/**
 * compare_types - Compare two strings alphabetically.
 * @a: First string.
 * @b: Second string.
 *
 * Return: 1 if first element is directory and second element is file,
 * otherwise returns 0
 */
int compare_types(const void *a, const void *b)
{
	const char *A = *(const char **)a;
	const char *B = *(const char **)b;
	struct stat stA;
	struct stat stB;

	if (lstat(A, &stA) && lstat(B, &stB))
	{
		if (S_ISDIR(stA.st_mode) && S_ISREG(stB.st_mode))
		{
			return (1);
		}
	}
	return (0);
}

