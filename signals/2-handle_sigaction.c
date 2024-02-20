#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * sig_handler - signal handler
 * @signo: signal number that was caught
*/
void sig_handler(int signo)
{
	printf("Gotcha! [%i]\n", signo);
	fflush(stdout);
}

/**
 * handle_sigaction - Set the handler for the signal SIGINT
 * The program should print Gotcha! [<signum>] followed by a new line,
 * every time Control-C is pressed
 * (where <signum> must be replaced with the signal number that was caught)
 * signal(2) is not allowed
 * Return: 0 on success, -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;

	act.sa_handler = sig_handler;

	if (sigaction(SIGINT, &act, NULL))
		return (-1);
	return (0);
}
