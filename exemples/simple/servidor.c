#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int port;
	int socketFD;
	int connectionFD;

	port = atoi(argv[1]);
 	socketFD = createServerSocket(port);

 	while (1){
		connectionFD = acceptNewConnections (socketFD);
		if (connectionFD < 0){
			perror ("Error establishing connection \n");
			deleteSocket(socketFD);
			exit (1);
		}
 	}
}