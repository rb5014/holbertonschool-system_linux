#include "signals.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * sig_handler - signal handler
 * @signo: signal number that was caught
*/
void sig_handler(int signo)
{
	printf("Caught %i\n", signo);
}

/**
 * main - Entry point: sets a handler for the signal SIGINT,
 * and exits right after the signal is received and handled
 * When a SIGINT is received, you must print Caught %d
 * (where %d must be replaced by the signal number), followed by a new line
 * After the first SIGINT is received, your program must:
 * Print Signal received, followed by a new line
 * Exit with EXIT_SUCCESS
 * You are not allowed to use the functions exit, sleep or _exit
 * You are not allowed to use any kind of loop (while, for, do/while)
 * Return: 0
 */
int main(void)
{
	struct sigaction act;

	act.sa_handler = sig_handler;

	if (sigaction(SIGINT, &act, NULL))
		return (-1);
	pause();

	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
