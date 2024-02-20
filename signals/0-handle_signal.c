#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * sig_handler - signal handler
 * @signo: signal number that was caught tg
*/
void sig_handler(int signo)
{
	printf("Gotcha! [%i]\n", signo);
	fflush(stdout);
}

/**
 * handle_signal - Set the handler for the signal SIGINT
 * The program should print Gotcha! [<signum>] followed by a new line,
 * every time Control-C is pressed
 * (where <signum> must be replaced with the signal number that was caught)
 * sigaction(2) is not allowed
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (-1);
	return (0);
}
