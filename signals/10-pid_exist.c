#include <signal.h>
/**
 * pid_exist - Tests if a process exist, given its pid
 * @pid: pid to test
 * Return: 1 if process with pid exists, 0 otherwise
*/
int pid_exist(pid_t pid)
{
	return (!(kill(pid, 0)));
}
