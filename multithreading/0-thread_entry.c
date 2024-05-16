#include "multithreading.h"

/**
 * thread_entry - entry point to a new thread.
 * @arg: holds the address of a string that must
 * be printed and followed by a new line.
 * Return: NULL
*/
void *thread_entry(void *arg)
{
	if (arg)
		printf("%s\n", (char *) arg);
	pthread_exit(NULL);
}
