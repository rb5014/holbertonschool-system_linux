#include <ctype.h>
#include "custom_functions.h"
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
	&& tolower((unsigned char)*s1) == tolower((unsigned char)*s2))
	{
		s1++;
		s2++;
	}

	return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}