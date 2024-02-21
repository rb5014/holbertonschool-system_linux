#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "signals.h"


/**
 * print_hello - Prints hello when a signal is caught
 * @signum: Signal no
 */
void print_hello(int signum)
{
	(void)signum;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
 * set_print_hello - Set 'print_hello' as the handler for SIGINT
 */
void set_print_hello(void)
{
	struct sigaction act;

	act.sa_handler = &print_hello;
	sigaction(SIGINT, &act, NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	void (*handler)(int);

	/* Set 'print_hello()` as the handler for SIGINT */
	set_print_hello();

	handler = current_handler_sigaction();
	if (handler != &print_hello)
	{
		printf("Addresses differ\n");
		return (EXIT_FAILURE);
	}

	/* Test a second time to ensure the handler is put back */
	handler = current_handler_sigaction();
	if (handler != &print_hello)
	{
		printf("Addresses differ\n");
		return (EXIT_FAILURE);
	}
	printf("Correct\n");
	return (EXIT_SUCCESS);
}