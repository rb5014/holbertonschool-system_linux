#include "signals.h"
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
/**
 * handle_signal - Set the handler for the signal SIGINT
 * The program should print Gotcha! [<signum>] followed by a new line,
 * every time Control-C is pressed
 * (where <signum> must be replaced with the signal number that was caught)
 * sigaction(2) is not allowed
 * Return: 0 on success, -1 on error
 */

void sig_handler(int signo)
{
	printf("Gotcha! [%i]\n", signo);
}

int handle_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (-1);
	return (0);
}
