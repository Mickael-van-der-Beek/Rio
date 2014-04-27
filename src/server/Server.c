/* Used for socket(), bind() and listen() */
#include <sys/types.h>
#include <sys/socket.h>

/* Used to get errno verbosity with strerror() */
#include <errno.h>

/* Used for strerror() */
#include <string.h>

/* Used for printf() */
#include <stdio.h>

/* Used for free() */
#include <stdlib.h>

/* Used for addrinfo and sockaddr_in */
#include <netdb.h>

/* Client struct */
#include "../client/Client.c"

#define CLIENT_MAX 10
#define HOST_NAME_MAX 255
#define QUEUED_CONNECTION_MAX 10

typedef struct {
	int socket;
} Server;

Server* new_Server (char* port);
Server* new_Server (char* port) {
	int sock_fd;
	Server* server;
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof hints);
	/* Auto-assign me an IP address */
	hints.ai_flags = AI_PASSIVE;
	/* Use IPv4 or IPv6 */
	hints.ai_family = AF_UNSPEC;
	/* Use TCP not UDP */
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(NULL, port, &hints, &result);

	/* Create a socket */
	sock_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(sock_fd == -1) {
		printf("[ERROR:new_Server] Server-socket() -> %s\n", strerror(errno));
		exit(0);
	}

	/* Bind the socket to an address */
	if(bind(sock_fd, result->ai_addr, result->ai_addrlen) == -1) {
		printf("[ERROR:new_Server] Server-bind() -> %s\n", strerror(errno));
		exit(0);
	}

	freeaddrinfo(result);

	/* Make the socket listen on a port */
	if(listen(sock_fd, QUEUED_CONNECTION_MAX) == -1) {
		printf("[ERROR:new_Server] Server-listen() -> %s\n", strerror(errno));
		exit(0);
	}

	server = malloc(sizeof(Server));
	server->socket = sock_fd;

	return server;
}

void kill_Server (Server* server);
void kill_Server (Server* server) {
	close(server->socket);
	free(server);
	exit(0);
}

void accept_Connection (Server* server);
void accept_Connection (Server* server) {
	int pid;
	int clnt_fd;
	int clnt_count = 0;
	int sock_fd = server->socket;
	Client* client;
	struct sockaddr_storage clnt_addr;
	socklen_t addr_size = sizeof clnt_addr;

	while((clnt_fd = accept(sock_fd, (struct sockaddr *)&clnt_addr, &addr_size)) != -1) {
		clnt_count += 1;

		printf("Connection - %d!\n", clnt_count);

		if(clnt_count == CLIENT_MAX) {
			printf("[ERROR:accept_Connection] Server-CLIENT_MAX -> %s\n", strerror(errno));
			close(clnt_fd);
		}
		else {
			pid = fork();
			if(pid == -1) {
				printf("[ERROR:accept_Connection] Client-fork() -> %s\n", strerror(errno));
				close(clnt_fd);
				kill_Server(server);
			}
			else if(pid == 0) {
				client = new_Client(clnt_fd, clnt_addr);
				respond_Client(client);
			}

			close(clnt_fd);
		}

	}

	printf("[ERROR:accept_Connections] Server-accept() -> %s\n", strerror(errno));
	kill_Server(server);
}
