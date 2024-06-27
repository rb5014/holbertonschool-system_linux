
#include "syscalls.h"

/**
 * trace_syscalls - trace syscalls of child process
 * @child_pid: child process pid
*/
void trace_syscalls(int child_pid)
{
	int status, syscall_number, print_next_syscall;
	struct user_regs_struct user_registers;

	/* Parent process */
	wait(&status);
	/* Wait for the child to stop on its first instruction */
	ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
	/* Main tracing loop */
	for (print_next_syscall = 0; !WIFEXITED(status); print_next_syscall ^= 1)
	{
		wait(&status);
		/* Get the registers of the child process */
		ptrace(PTRACE_GETREGS, child_pid, 0, &user_registers);
		/* Print the system call number every other time */
		if (print_next_syscall)
		{
			/* Get the system call number */
			syscall_number = user_registers.orig_rax;
			printf("%d\n", syscall_number);
		}

		/* Continue the execution of the child process */
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
	}
}

/**
* main - Entry point
* @argc: The number of arguments
* @argv: The arguments
*
* Return: 0 on success, otherwise 1
*/
int main(int argc, char **argv)
{
	pid_t child_pid;

	/* Disable buffering on stdout */
	setvbuf(stdout, NULL, _IONBF, 0);

	if (argc < 2)
		exit(EXIT_FAILURE);
	/* Create a child process */
	child_pid = fork();

	if (child_pid < 0)
		exit(EXIT_FAILURE);
	else if (child_pid == 0)
	{
		/* Child process */
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		argv[argc] = NULL;
		execvp(argv[1], argv + 1);
	}
	else
		trace_syscalls(child_pid);
	return (0);
}
