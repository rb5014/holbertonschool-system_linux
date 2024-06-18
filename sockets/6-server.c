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
 * parse_http_request - print headers of http request
 * @request: request string
*/
void parse_http_request(const char *request)
{
	char *request_line_end = strstr(request, "\r\n");
	char *headers_start = request_line_end + 2;
	char *header_line = NULL;
	char *key, *value, *colon_pos;
	char *header_line_end;

	/* one header per line of the form key: value*/
	/* header_start equalr header_line_ end when two \r\n are adjacent */
	/* meaning it is the end of the headers part of the http request */
	while ((header_line_end = strstr(headers_start, "\r\n")) &&
		    headers_start != header_line_end)
	{
		size_t line_length = header_line_end - headers_start;

		header_line = realloc(header_line, line_length + 1);
		if (!header_line)
			return;
		strncpy(header_line, headers_start, line_length);
		header_line[line_length] = '\0';
		key = header_line;
		colon_pos = strchr(key, ':');
		if (colon_pos)
		{
			*colon_pos = '\0'; /* to put end to key string */
			value = colon_pos + 1;
			while (*value == ' ') /* Trim any potential white space*/
				value++;
			printf("Header: \"%s\" -> \"%s\"\n", key, value);
		}
		headers_start = header_line_end + 2; /* +2 to skip \r\n */
	}
	free(header_line);
}


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
	char *request = NULL;
	int bytes_received, total_bytes_received = 0;
	const char *ok_status = "HTTP/1.1 200 OK\r\n\r\n";

	while (1)
	{
		bytes_received = recv(clnt_sock, chunk, CHUNKSIZE - 1, 0);
		chunk[bytes_received] = '\0'; /* Null-terminate the received data */
		total_bytes_received += bytes_received;

		request = realloc(request, total_bytes_received + 1);
		strcat(request, chunk);
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
	printf("Raw request: \"%s\"\n", request);
	parse_http_request(request);
	free(request);
	request = NULL;
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
