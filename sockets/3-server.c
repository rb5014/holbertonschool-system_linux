#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 12345
#define MAXPENDING 5
#define CHUNKSIZE 32

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
 *		Accept an entering connection
 *		Print the IP address of the connected client
 *		Wait for an incoming message from the connected client
 *		Print the received message
 *		Close the connection with the client
 *		Exit
 * Return: 1 on success, 0 otherwise
*/
int main(void)
{
	struct sockaddr_in serv_addr, clnt_addr;
	const int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	int clnt_sock;
	unsigned int clnt_len; /* Length of client address data structure */
	char chunk[CHUNKSIZE];

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
	clnt_len = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_len);
	if (clnt_sock < 0)
		exit_with_err_msg("accept() failed");
	printf("Client connected: %s\n", inet_ntoa(clnt_addr.sin_addr));
	memset(chunk, '\0', CHUNKSIZE);	/* clear the variable */
	printf("Message received: \"");
	while (recv(clnt_sock, chunk, CHUNKSIZE, 0))
	{
		printf("%s", chunk);
		memset(chunk, '\0', CHUNKSIZE);	/* clear the variable */
	}
	printf("\"\n");
	close(clnt_sock);

	return (1);
}
