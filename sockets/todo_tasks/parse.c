#include "socket.h"

#define NB_CHAR_CRLF 2

static todo_node_t *head;

static char *ok_mes = "HTTP/1.1 200 OK\r\n";
static char *length_required_mes = "HTTP/1.1 411 Length Required\r\n\r\n";
static char *unproc_entity_mes = "HTTP/1.1 422 Unprocessable Entity\r\n\r\n";
static char *created_mes = "HTTP/1.1 201 Created\r\n";
static char *not_found_mes = "HTTP/1.1 404 Not Found\r\n\r\n";
static char *methods_available[] = {"POST", "GET", NULL};
static char *paths_available[] = {"/todos", NULL};

/**
 * parse_get_request - parse request to get all todo items
 * @query: query of the get request
 * Return: Http response with json representation of todo list
*/
char *parse_get_request(const char *query)
{
	todo_node_t *found_node;
	char *json_repr;
	char *response = NULL;
	int id = 0, status;

	if (query == NULL)
	{
		json_repr = get_list_json_repr(head);
	}
	else
	{
		status = sscanf(query, "id=%i", &id);
		found_node = find_node_with_id(head, id);
		if ((status != 1) || (found_node == NULL))
			return (strdup(not_found_mes));
		json_repr = get_node_json_repr(found_node);
	}

	asprintf(&response,
			 "%sContent-Length: %lu\r\nContent-Type: application/json\r\n\r\n%s",
			 ok_mes, strlen(json_repr), json_repr);

	return (response);
}

/**
 * parse_post_request - parse request to create a todo item
 * @message: http message containing todo title and description
 * Return: http responsse containing json reprensation of todo node
 * if it succeeded
*/
char *parse_post_request(const char *message)
{
	const char *body;
	char title[256], description[1024];
	char *json_repr = NULL, *response = NULL;
	int status;
	todo_node_t *new_node;

	if (get_body_length(message) == -1)
		return (strdup(length_required_mes));
	body = strstr(message, "\r\n\r\n") + 2 * NB_CHAR_CRLF;
	status = sscanf(body, "title=%255[^& ]&description=%1023[^\r\n]",
					title, description);
	if (status != 2)
	{
		status = sscanf(body, "description=%1023[^& ]&title=%255[^\r\n]",
						description, title);
		if (status != 2)
			return (strdup(unproc_entity_mes));
	}
	new_node = create_node(title, description);
	insert_at_tail(&head, new_node);
	json_repr = get_node_json_repr(new_node);
	asprintf(&response,
			"%sContent-Length: %lu\r\nContent-Type: application/json\r\n\r\n%s\r\n",
			created_mes, strlen(json_repr), json_repr);
	free(json_repr);
	return (response);
}

/**
 * parse_start_line - Parse first line of HTTP message
 * @message: http message
 * @method: adress of method string to fill
 * @path: adress of path string to fill
 * @query: adress of query string to fill
 * @protocol: adress of protocol string to fill
 * Return: 1 if method handled and path recognized, 0 otherwise
*/
int parse_start_line(const char *message, char **method, char **path,
					 char **query, char **protocol)
{
	const char *end_start_line = strstr(message, "\r\n");
	size_t length = end_start_line - message;
	char *start_line = strndup(message, length);
	char *path_start, *query_start;
	int i, method_handled = 0, path_recognized = 0;

	*method = strdup(strsep(&start_line, " "));
	for (i = 0; methods_available[i] != NULL; i++)
	{
		if (strcmp(*method, methods_available[i]) == 0)
			method_handled = 1;
	}
	path_start = strsep(&start_line, " ");
	query_start = strchr(path_start, '?');
	if (query_start)
	{
		*query_start = '\0';
		query_start++;
		*query = strdup(query_start);
		printf("Query: %s\n", *query);
	}
	*path = strdup(path_start);
	printf("Path: %s\n", *path);
	for (i = 0; paths_available[i] != NULL; i++)
	{
		if (strcmp(*path, paths_available[i]) == 0)
			path_recognized = 1;
	}

	*protocol = strdup(strsep(&start_line, " "));

	free(start_line);
	return (method_handled & path_recognized);
}

/**
 * get_body_length - get body length by looking for Content-length header
 * @message: http message
* Return: length of body if it exists, -1 if header content-length is missing
*/
int	get_body_length(const char *message)
{
	int status, body_length = 0;
	const char *headers_start = strstr(message, "\r\n") + NB_CHAR_CRLF;

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
 * parse_http_message - parse http message
 * @message: message string
 * Return: http response
 */
char *parse_http_message(const char *message)
{
	char *method = NULL, *path = NULL, *query = NULL, *protocol = NULL;
	char *response = NULL;

	if (parse_start_line(message, &method, &path, &query, &protocol) == 0)
		response = strdup(not_found_mes);
	else if (strcmp(method, "POST") == 0)
	{
		response = parse_post_request(message);
	}
	else if (strcmp(method, "GET") == 0)
		response = parse_get_request(query);
	return (response);
}
