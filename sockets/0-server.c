#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#define PORT 12345
/**
 * main - Entry point
 * opens an IPv4/TCP socket, and listens to traffic on port 12345 (Any address)
 *		program must hang indefinitely
 *		(It’ll eventually be killed by a signal during correction)
 *		don’t have to accept entering connections
 * Return: 1 on success, 0 otherwise
*/
int main(void)
{
	struct sockaddr_in addrport;
	const int tcp_sock_id = socket(AF_INET, SOCK_STREAM, 0);
	int status = 0;

	addrport.sin_family = AF_INET;
	addrport.sin_port = htons(PORT);
	addrport.sin_addr.s_addr = htonl(INADDR_ANY);

	if (tcp_sock_id == -1)
	{
		printf("Error socket creation failed\n");
		return (0);
	}
	if (bind(tcp_sock_id, (struct sockaddr *) &addrport, sizeof(addrport)) == -1)
	{
		printf("Error binding socket %i on port %i\n", tcp_sock_id, PORT);
		return (0);
	}
	printf("Server listening on port 12345\n");
	while (1)
	{
		status = listen(tcp_sock_id, 0);
		if (status == -1)
		{
			printf("Error listening status\n");
			return (0);
		}
	}
	return (1);
}
