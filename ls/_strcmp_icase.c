#include "custom_functions.h"

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