#include "signals.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point: sends the signal SIGINT to a process, given its PID
 * Where <pid> is the PID of the process to send a signal to
 * If the number of arguments is not correct,
 * program must print Usage: %s <pid>
 * (where %s is argv[0]), followed by a new line, and exit with EXIT_FAILURE
 * <pid> won’t be 0
 * @argc: number of argument
 * @argv: array of arguments
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (kill(atoi(argv[1]), SIGINT) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
