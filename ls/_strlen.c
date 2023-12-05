#include "custom_functions.h"

/**
 * _strlen - Calculate the length of a string.
 * @str: Input string.
 *
 * Return: Length of the string.
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (*str != '\0')
	{
		str++;
		length++;
	}
	return (length);
}
