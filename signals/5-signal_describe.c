#include "signals.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/**
 * main - Entry point: prints a description of a given signal
 * @argc: number of argument
 * @argv: array of arguments
 * Usage: ./describe <signum>
 * Where <signum> is the signal number to be described
 * If the number of arguments is not correct,
 * program must print Usage: %s <signum> (where %s is argv[0]),
 * followed by a new line, and exit with EXIT_FAILURE
 * Return: 0 if success, -1 if error
 */
int main(int argc, char *argv[])
{
	const char *name;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	name = sys_siglist[atoi(argv[1])];
	printf("%s: %s%s\n", argv[1], name != NULL ? name : "Unknown signal ",
		   name == NULL ? argv[1] : "");
	return (0);
}
