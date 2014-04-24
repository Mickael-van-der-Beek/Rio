#include <stdlib.h>
#include <string.h>

/* HOST_NAME_MAX will have to be changed into getconf HOST_NAME_MAX */
#define HOST_NAME_MAX 255

typedef struct {
	unsigned short port;
	unsigned char host[HOST_NAME_MAX];
} Server;

Server* new_Server (unsigned short *port, unsigned char *host) {
	/*Server* server = malloc(sizeof(Server));
	server->port = port;
	server->host = host;*/
	Server* server = {port, host};
	return server;
}
