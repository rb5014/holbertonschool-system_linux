#include "socket.h"

#define PORT 8080
#define MAXPENDING 1
#define CHUNKSIZE 3000
#define NB_CHAR_CRLF 2

static todo_node_t *head;

static char *length_required_mes = "HTTP/1.1 411 Length Required\r\n\r\n";
static char *unproc_entity_mes = "HTTP/1.1 422 Unprocessable Entity\r\n\r\n";
static char *created_mes = "HTTP/1.1 201 Created\r\n";
static char *not_found_mes = "HTTP/1.1 404 Not Found\r\n\r\n";

	/**
	 * get_body_length - get body length by looking for Content-length header
	 * @headers_start: start of headers to check
	 * @clnt_sock: client socket to send message
	 *			   if content-length header is missing
	 * Return: length of body if it exists, -1 if header content-length is missing
	 */
	int
	get_body_length(const char *headers_start)
{
	int status, body_length = 0;

	while (strncmp(headers_start, "\r\n", 2) != 0)
	{
		char hdr_key[256], hdr_value[256];

		status = sscanf(headers_start, "%255[^: ]: %255[^\r\n]", hdr_key, hdr_value);
		if (status < 0)
			printf("Bad header line format\n");
		if (strcmp(hdr_key, "Content-Length") == 0)
		{
			body_length = atoi(hdr_value);
			return (body_length);
		}
		headers_start = strstr(headers_start, "\r\n") + NB_CHAR_CRLF;
	}

	/* header Content-length not found */
	return (-1);
}
/**
 * parse_http_request - print request path
 * and all body parameters key_value pairs
 * @request: request string
 * @clnt_sock: client socket to read messages from
 */
void parse_http_request(const char *request, const int clnt_sock)
{
	char method[16], path[256], *body, title[256], description[1024];
	int status, body_length = 0;
	char *headers_start, *headers_end;
	char json_repr[2000], response[3000];

	status = sscanf(request, "%15s %255s", method, path);
	if (status < 0)
		return;
	else if ((strcmp(method, "POST") != 0) || (strcmp(path, "/todos") != 0))
	{
		send(clnt_sock, not_found_mes, strlen(not_found_mes), 0);
		return;
	}
	printf("Method: %s\nPath:%s\n", method, path);
	headers_start = strstr(request, "\r\n") + NB_CHAR_CRLF; /* skip \r\n */
	headers_end = strstr(headers_start, "\r\n\r\n");

	body_length = get_body_length(headers_start);
	if (body_length == -1)
	{
		send(clnt_sock, length_required_mes, strlen(length_required_mes), 0);
		return;
	}
	body = strdup(headers_end + 2 * NB_CHAR_CRLF);
	printf("Body: %s\n", body);
	status = sscanf(body, "title=%255[^& ]&description=%1023[^\r\n]",
					title, description);
	if (status != 2)
	{
		send(clnt_sock, unproc_entity_mes, strlen(unproc_entity_mes), 0);
		return;
	}
	insert_at_head(&head, create_node(title, description));
	sprintf(json_repr, "{\"id\":%i,\"title\":\"%s\",\"description\":\"%s\"}",
			head->id, head->title, head->description);
	sprintf(response,
			"%sContent-Length: %lu\r\nContent-Type: application/json\r\n%s\r\n",
			created_mes, strlen(json_repr), json_repr);
	send(clnt_sock, response, strlen(response), 0);
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
	int bytes_received;

	bytes_received = recv(clnt_sock, chunk, CHUNKSIZE - 1, 0);
	chunk[bytes_received] = '\0'; /* Null-terminate the received data */

	if (bytes_received < 0)
	{
		close(clnt_sock);
		printf("Error receiving data failed");
		exit(EXIT_FAILURE);
	}
	printf("Raw request: \"%s\"\n", chunk);

	parse_http_request(chunk, clnt_sock);
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
 * start_server - create server, bind it and listen to clients then handle them
 * with handle_client function
 * Return: 0 if success, -1 otherwise
 */
int start_server(void)
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

/**
 * main - Entry point
 * Return: 0 if success, -1 otherwise
 */
int main(void)
{
	if (start_server() < 0)
		return (-1);
	return (0);
}
