/* Project's Custom structs */
#include "./server/Server.c"

/* Configuration values */
#define PORT "8080"

int main (void) {

	Server* server = new_Server(PORT);
	accept_Connection(server);

	return 0;
}
