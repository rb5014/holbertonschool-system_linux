#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 12345
#define MAXPENDING 5
/**
 * exit_with_err_msg - exits program with error message passed as parameter
 * @err_msg: error message to print before exit
*/
void exit_with_err_msg(const char *err_msg)
{
	printf("%s\n", err_msg);
	exit(-1);
}

/**
 * main - Entry point
 * opens an IPv4/TCP socket, and listens to traffic on port 12345 (Any address)
 *		program must hang indefinitely
 *		(It’ll eventually be killed by a signal during correction)
 *		must accept an entering connection,
 *		print the IP address of the connected client,
 *		and close the connection right after
 * Return: 1 on success, 0 otherwise
*/
int main(void)
{
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	const int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	int clnt_sock;
	unsigned int clnt_len; /* Length of client address data structure */

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (serv_sock < 0)
		exit_with_err_msg("Error socket creation failed\n");

	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		exit_with_err_msg("Error binding socket\n");

	if (listen(serv_sock, 0) < 0)
		exit_with_err_msg("Error listening status\n");
	printf("Server listening on port 12345\n");

	while (1)
	{
		/* Set the size of the in-out parameter */
		clnt_len = sizeof(clnt_addr);
		/* Wait for a client to connect */
		clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_len);
		if (clnt_sock < 0)
			exit_with_err_msg("accept() failed");
		/* clnt_sock is connected to a client! */
		printf("Client connected: %s\n", inet_ntoa(clnt_addr.sin_addr));
		break;
	}
	return (1);
}
