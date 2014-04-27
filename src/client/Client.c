/* Used to get errno verbosity with strerror() */
#include <errno.h>

/* Used for strerror() */
#include <string.h>

/* Used for close() */
#include <unistd.h>

typedef struct {
	int socket;
	struct sockaddr_storage address;
} Client;

Client* new_Client (unsigned int socket, struct sockaddr_storage address);
Client* new_Client (unsigned int socket, struct sockaddr_storage address) {
	Client* client = malloc(sizeof(Client));
	client->address = address;
	client->socket = socket;
	return client;
}

void kill_Client (Client* client);
void kill_Client (Client* client) {
	close(client->socket);
	free(client);
	exit(0);
}

void respond_Client (Client* client);
void respond_Client (Client* client) {
	char input[] = "This is the response!";
	int len = strlen(input);

	if(send(client->socket, input, len, 0) == -1) {
		printf("[ERROR:respond_Client] Client-send() -> %s\n", strerror(errno));
	}

	kill_Client(client);
}
