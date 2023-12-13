#include "_getline.h"

/**
 * _memmove - Safely moves overlapping memory regions.
 * @dest: The destination address.
 * @src: The source address.
 * @n: The number of bytes to move.
 */
void _memmove(char *dest, char *src, size_t n)
{
	size_t i;

	if (dest < src)
	{
		for (i = 0; i < n; i++)
		{
			dest[i] = src[i];
		}
	}
	else
	{
		for (i = n; i > 0; i--)
		{
			dest[i - 1] = src[i - 1];
		}
	}
}
