#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define PORT 8080
#define MAXPENDING 5
#define CHUNKSIZE 3000

/**
 * print_breakdown - print the breakdown of the first line of http request
 * @line: chunk of data containing 1st line
*/
void print_breakdown(char *line)
{
	char *token = " ";
	const char *delim = " ";

	token = strsep(&line, delim);
	printf("Method: %s\n", token);
	token = strsep(&line, delim);
	printf("Path: %s\n", token);
	token = strsep(&line, delim);
	printf("Version: %s\n", token);
}

/**
 * get_first_line_http - get first line of http request
 * @bytes_received: bytes received from call to recv
 * @chunk: chunk of data from to recv
 * Return: The first line
*/
char *get_first_line_http(const int bytes_received, const char *chunk)
{
	char *first_line = NULL;
	int i;

	first_line = malloc(bytes_received);
	for (i = 0; i < bytes_received; i++)
	{
		if (chunk[i] != '\r')
			first_line[i] = chunk[i];
		else
		{
			first_line[i] = '\0';
			break;
		}
	}
	return (first_line);
}

/**
 * handle_message - handle message from client socket
 * @clnt_sock: client socket to read messages from
 * Print full message
 * Send back response to client after getting full message
 * Print the breakdown of the first line
*/
void handle_message(const int clnt_sock)
{
	char chunk[CHUNKSIZE];
	int bytes_received;
	char *first_line;
	const char *ok_status = "HTTP/1.1 200 OK\r\n\r\n";

	printf("Raw request: \"");
	while (1)
	{
		bytes_received = recv(clnt_sock, chunk, CHUNKSIZE - 1, 0);
		if (!first_line)
		{
			first_line = get_first_line_http(bytes_received, chunk);
		}
		chunk[bytes_received] = '\0'; /* Null-terminate the received data */
		printf("%s", chunk);
		if (bytes_received < 0)
		{
			close(clnt_sock);
			printf("Error receiving data failed");
			exit(EXIT_FAILURE);
		}
		if (bytes_received < (CHUNKSIZE - 1))
		{
			send(clnt_sock, ok_status, strlen(ok_status), 0);
			break;
		}
	}
	printf("\"\n");
	print_breakdown(first_line);
	free(first_line);
	first_line = NULL;
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
		clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_len);

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
 * Opens an IPv4/TCP socket, listens on port 8080.
 *
 * The function performs the following steps:
 * 1. Accepts incoming connection.
 * 2. Prints connected client's IP address.
 * 3. Waits for an incoming message from the client.
 * 4. Prints the full received HTTP request.
 * 5. Prints the break-down of the first line of the HTTP request.
 * 6. Sends an HTTP 200 OK response to the client.
 * 7. Closes the client connection.
 * 8. Waits for the next connection.
 *
 * The client sends a valid HTTP/1.1 request.
 * Reference: RFC for HTTP/1.1 (Sections 4, 5, 6, and 10).
 *
 * The Makefile must define the rule `todo_api_0` which compiles and links
 * the sources to form an executable with the same name.
 * Return: 1 if success, exit on failure
 */

int main(void)
{
	struct sockaddr_in serv_addr;
	const int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (serv_sock < 0)
	{
		printf("Error socket creation failed\n");
		exit(EXIT_FAILURE);
	}
	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Error binding socket\n");
		exit(EXIT_FAILURE);
	}
	if (listen(serv_sock, MAXPENDING) < 0)
	{
		printf("Error listening status\n");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %i\n", PORT);

	handle_clients(serv_sock);

	close(serv_sock);

	return (1);
}
