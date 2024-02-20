#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * sig_handler - signal handler
 * @signo: signal number that was caught
*/
void print_hello(int signo)
{
	signo = signo;
	printf("Hello :)\n");
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
int set_print_hello(void)
{
	if (signal(SIGINT, print_hello) == SIG_ERR)
		return (-1);
	return (0);
}
