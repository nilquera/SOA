#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
int main(int argc, char *argv[]){
	char *hostname;
	int port;
	int connectionFD;

	hostname = argv[1];
	port = atoi(argv[2]);
	connectionFD = clientConnection(hostname, port);
	if (connectionFD < 0){
		perror ("Error establishing connection\n");
		exit (1);
    }
}