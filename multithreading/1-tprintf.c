#include "multithreading.h"

/**
 * tprintf - uses the printf family to print out a given formatted string
 * @format: formatted string to print
 * Return: number of chars printed
*/
int tprintf(char const *format, ...)
{
	pthread_t id = pthread_self();
	va_list args;
	int result;

	printf("[%li] ", id);
	va_start(args, format);
	result = vprintf(format, args);
	va_end(args);
	return (result);
}
