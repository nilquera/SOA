#include <stdio.h>
#include <stdlib.h>

void doService(int fd){
	char buff[80];
	int ret = read(fd, buff, sizeof(buff));
	while (ret > 0){
		printf("%s", buff);
		ret = read(fd, buff, sizeof(buff));
	}

	if (ret < 0){
		perror ("Error reading from socket");
	}
	
}

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
		doService(connectionFD);
 	}
}