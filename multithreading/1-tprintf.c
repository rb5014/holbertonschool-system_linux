#include "multithreading.h"

/**
 * tprintf - uses the printf family to print out a given formatted string
 * @format: formatted string to print
 * Return: NULL
*/
int tprintf(char const *format, ...)
{
	pthread_t id = pthread_self();
	va_list args;

	printf("[%li] ", id);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	pthread_exit(NULL);
}
