#include "socket.h"

#define PORT 8080
#define MAXPENDING 1
#define CHUNKSIZE 3000


/**
 * handle_message - handle message from client socket
 * @clnt_sock: client socket to read messages from
 * Print full message
 * Send back response to client after getting full message
 * Print the breakdown of the headers
 */
void handle_message(const int clnt_sock)
{
	char chunk[CHUNKSIZE];
	int bytes_received;
	char *response;

	bytes_received = recv(clnt_sock, chunk, CHUNKSIZE - 1, 0);
	chunk[bytes_received] = '\0'; /* Null-terminate the received data */

	if (bytes_received < 0)
	{
		close(clnt_sock);
		printf("Error receiving data failed");
		exit(EXIT_FAILURE);
	}
	printf("Raw request: \"%s\"\n", chunk);

	response = parse_http_message(chunk);

	send(clnt_sock, response, strlen(response), 0);
}

/**
 * handle_clients - handles connection to a client and its potiential requests
 * @serv_sock: server socket to connect to client
 * When connected, start handling potential message from client
 * When message was handled, close the connection
 */
void handle_clients(const int serv_sock)
{
	struct sockaddr_in clnt_addr;
	unsigned int clnt_len = sizeof(clnt_addr);
	int clnt_sock;

	while (1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_len);

		if (clnt_sock < 0)
		{
			printf("Error connection failed");
			exit(EXIT_FAILURE);
		}

		printf("Client connected: %s\n", inet_ntoa(clnt_addr.sin_addr));

		handle_message(clnt_sock);

		close(clnt_sock);
		fflush(stdout);
	}
}


/**
 * main - Entry point
 * create server, bind it and listen to clients then handle them
 * with handle_client function
 * Return: 0 if success, exit with EXIT_FAILURE otherwise
 */
int main(void)
{
	struct sockaddr_in serv_addr;
	const int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (serv_sock < 0)
		print_err_and_exit(SOCKET_ERROR);
	if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		print_err_and_exit(BIND_ERROR);
	if (listen(serv_sock, MAXPENDING) < 0)
		print_err_and_exit(LISTEN_ERROR);

	printf("Server listening on port %i\n", PORT);

	handle_clients(serv_sock);

	close(serv_sock);

	return (0);
}
