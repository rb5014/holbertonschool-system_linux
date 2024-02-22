#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * sig_handler - signal handler
 * @signo: signal number that was caught
 * @info: pointer to a siginfo_t containing signal information
 * @ucontext: pointer to a ucontext_t structure, cast to void *
*/
void sig_handler(int signo, siginfo_t *info, void *ucontext)
{
	signo = signo;
	ucontext = ucontext;
	printf("SIGQUIT sent by %i\n", info->si_pid);
}

/**
 * trace_signal_sender - Set the handler for the signal SIGQUIT
 * The handler must print SIGQUIT sent by <pid> each time a SIGQUIT
 * (and only a SIGQUIT) is caught
 * Where <pid> must be replaced by the PID of the process that sent the signal
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	if (sigaction(SIGQUIT, &act, NULL))
		return (-1);
	return (0);
}
