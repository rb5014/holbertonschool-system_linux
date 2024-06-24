#include "socket.h"

/**
 * print_err_and_exit - print error message and exit program
 * @error: error encountered
*/
void print_err_and_exit(err_t error)
{
	char *func_name;

	switch (error)
	{
		case SOCKET_ERROR:
			func_name = "socket()";
			break;
		case BIND_ERROR:
			func_name = "bind()";
			break;
		case LISTEN_ERROR:
			func_name = "listen()";
			break;
		case ACCEPT_ERROR:
			func_name = "accept()";
			break;
		case RECV_ERROR:
			func_name = "recv()";
			break;
		case SEND_ERROR:
			func_name = "send()";
			break;
		default:
			break;
	}
	printf("\'%s\' failed\n", func_name);
	exit(EXIT_FAILURE);
}
