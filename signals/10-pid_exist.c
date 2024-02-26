#include <signal.h>
/**
 * pid_exist - Tests if a process exist, given its pid
 * @pid: pid to test
 * Return: 1 if process with pid exists, 0 otherwise
*/
int pid_exist(pid_t pid)
{
	/* kill ruturns 0 if pid exists, -1 if not, so we return the NOT of kill */
	return (!(kill(pid, 0)));
}
