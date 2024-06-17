#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define MAXPENDING 5
#define CHUNKSIZE 32

/**
 * print_breakdown - print the breakdown of the first line of http request
 * @chunk: chunk of data containing 1st line
*/
void print_breakdown(char *chunk)
{
	char *token = " ";
	const char *delim = " ";

	token = strsep(&chunk, delim);
	printf("Method: %s\n", token);
	token = strsep(&chunk, delim);
	printf("Path: %s\n", token);
	token = strsep(&chunk, delim);
	printf("Version: %s\n", token);
}
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
 */

int main(void)
{
	struct sockaddr_in serv_addr, clnt_addr;
	const int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	int clnt_sock, i;
	unsigned int clnt_len; /* Length of client address data structure */
	char chunk[CHUNKSIZE], *first_line = NULL;
	ssize_t bytes_received;
	const char *ok_status = "HTTP/1.1 200 OK\r\n\r\n";

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (serv_sock < 0)
		exit_with_err_msg("Error socket creation failed\n");
	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		printf("Error binding socket\n");
	if (listen(serv_sock, MAXPENDING) < 0)
		exit_with_err_msg("Error listening status\n");
	printf("Server listening on port %i\n", PORT);
	clnt_len = sizeof(clnt_addr);
	while (1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_len);
		if (clnt_sock < 0)
			exit_with_err_msg("accept() failed");
		printf("Client connected: %s\n", inet_ntoa(clnt_addr.sin_addr));
		printf("Raw request: \"");
		while (1)
		{
			bytes_received = recv(clnt_sock, chunk, CHUNKSIZE - 1, 0);
			if (!first_line)
			{
				first_line = realloc(first_line, bytes_received);
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
			}
			chunk[bytes_received] = '\0'; /* Null-terminate the received data */
			printf("%s", chunk);
			if (bytes_received < (CHUNKSIZE - 1))
			{
				send(clnt_sock, ok_status, strlen(ok_status), 0);
				break;
			}
		}
		printf("\"\n");
		print_breakdown(first_line);
		close(clnt_sock);
		free(first_line);
		first_line = NULL;
	}
	
	close(serv_sock);

	return (1);
}
