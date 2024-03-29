#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * current_handler_signal - Retrieves the current handler of the signal SIGINT
 * Not allowed to use sigaction(2)
 * The handler must be unchanged after calling function
 * Return: pointer to the current handler of SIGINT,
 * or NULL on failure
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, NULL);

	signal(SIGINT, handler);

	return (handler != SIG_ERR ? handler : NULL);
}
