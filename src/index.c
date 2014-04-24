/* Standard libraries */
#include <stdio.h>
#include <string.h>

/* Poisonsed GCC methods for security reasons */
/* Sadly breaks stdlib and unistd */
/* #include "../poison/gcc-poison.h" */

/* Project's Custom classes */
#include "./server/Server.c"

/* Configuration value */
#define HOST "127.0.0.1"
#define PORT 80

int main (void) {
	unsigned short port = PORT;
	unsigned char host[255] = HOST; 
	Server* server = new_Server(port, host); 

	printf("Hello World\n");
	printf("%d", server->port);
	printf("%s", server->host);
	return 0;
}
