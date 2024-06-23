#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "todo.h"

/**
 * enum error_e - enum of different errors
 * @SOCKET_ERROR: socket() failed
 * @BIND_ERROR: bind() failed
 * @LISTEN_ERROR: listen() failed
 * @ACCEPT_ERROR: accept() failed
 * @RECV_ERROR: recv() failed
 * @SEND_ERROR: send() failed
*/
typedef enum error_e
{
	SOCKET_ERROR,
	BIND_ERROR,
	LISTEN_ERROR,
	ACCEPT_ERROR,
	RECV_ERROR,
	SEND_ERROR
} error_t;
void print_err_and_exit(error_t error);

int start_server(void);
void handle_clients(const int serv_sock);
void handle_message(const int clnt_sock);
void parse_http_request(const char *request, const int clnt_sock);
#endif /* SOCKET_H */
