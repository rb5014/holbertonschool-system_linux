#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

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
 * connects to a listening server
 * Usage: 2-client <host> <port>
 * Where port is an unsigned short
 * If the number of command-line arguments is not sufficient,
 *  program must display: Usage: %s <host> <port>
 * (where %s must be replaced by the name of the program),
 *  followed by a new line and exit with EXIT_FAILURE
 * Can assume that <port> will be a positive integer
 * Once client established a connection with the server,
 *  it must print a message, and exit successfully
 * In order to test server, can use the program 2-server
 * @argc: nb of args
 * @argv: array of args
 * Return: 1 on success, 0 otherwise
*/
int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr;
	int clnt_sock;
	struct hostent *host;
	char *ptr;
	char *host_name, *port_name;
	unsigned short int port;
	unsigned int addr;

	if (argc < 3)
	{
		printf("Usage: %s <host> <port>", argv[0]);
		exit(EXIT_FAILURE);
	}
	host_name = argv[1];
	port_name = argv[2];
	port = htons((unsigned short)strtoul(argv[2], &ptr, 10));
	host = gethostbyname(argv[1]);
	if (host == NULL)
		exit_with_err_msg("Error: Unable to resolve localhost\n");
	addr = htonl(strtoul(host->h_addr_list[0], &ptr, 10));

	clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clnt_sock < 0)
		exit_with_err_msg("Client socket creation failed\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = addr;
	serv_addr.sin_port = port;

	if (connect(clnt_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		exit_with_err_msg("Error connecting socket\n");
	else
		printf("Connected to %s:%s\n", host_name, port_name);
	return (1);
}
