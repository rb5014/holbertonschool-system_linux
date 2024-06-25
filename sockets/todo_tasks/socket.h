#ifndef SOCKET_H
#define SOCKET_H

#define _GNU_SOURCE
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
 * enum err_e - enum of different errors
 * @SOCKET_ERROR: socket() failed
 * @BIND_ERROR: bind() failed
 * @LISTEN_ERROR: listen() failed
 * @ACCEPT_ERROR: accept() failed
 * @RECV_ERROR: recv() failed
 * @SEND_ERROR: send() failed
*/
typedef enum err_e
{
	SOCKET_ERROR,
	BIND_ERROR,
	LISTEN_ERROR,
	ACCEPT_ERROR,
	RECV_ERROR,
	SEND_ERROR
} err_t;

/* error_handling.c */
void print_err_and_exit(err_t error);

/* parse.c */
const char *parse_delete_request(const char *query);
const char *parse_get_request(const char *query);
const char *parse_post_request(const char *message);
const char *parse_start_line(const char *message, char **method, char **path,
					 char **query, char **protocol);
int	get_body_length(const char *headers_start);

/* main.c */
void handle_message(const int clnt_sock);
void handle_clients(const int serv_sock);

#endif /* SOCKET_H */
