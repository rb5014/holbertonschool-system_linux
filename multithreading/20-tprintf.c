#include "multithreading.h"

static pthread_mutex_t mutex;

/**
 * begin - initialize mutex before main function
*/
void __attribute__((constructor)) begin(void)
{
	pthread_mutex_init(&mutex, NULL);
}

/**
 * end - destroy mutex after main function
*/
void __attribute__((destructor)) end(void)
{
	pthread_mutex_destroy(&mutex);
}

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

	pthread_mutex_lock(&mutex);
	printf("[%li] ", id);
	va_start(args, format);
	result = vprintf(format, args);
	va_end(args);
	pthread_mutex_unlock(&mutex);
	return (result);
}
