#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


// Create a socket and initialize it to be able to accept 
// connections.
// It returns the virtual device associated to the socket that should be used 
// in the accept system call, to get the virtual device associated to 
// the connection
//

int
createServerSocket (int port)
{  
  int socket_fd = socket (AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0){
    printf("Unable to create socket\n");
    return -1;
  }

  struct sockaddr_in my_addr; 
  my_addr.sin_family = AF_INET; 
  my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  my_addr.sin_port = htons(port); 

  if (bind(socket_fd, (struct sockaddr*) &my_addr, sizeof(my_addr)) < 0){
      printf("Unable to bind\n"); 
      return -1;
  }
  
  if (listen(socket_fd, 3) == 0){
      printf("Listening ...\n"); 
      return socket_fd;
  } else {
      printf("Unable to listen\n"); 
      return -1;
  }
}


// Returns the file descriptor associated to the connection.
// accept system call will fill the socketAddr parameter
// with the address of the socket for the client which is requesting the
// connection, and the addrSize parameter with the size of that address.

int
acceptNewConnections (int socket_fd)
{
  struct sockaddr peer_addr;                                                                                                          
  socklen_t peer_addr_size = sizeof(struct sockaddr);  
  int acc = accept(socket_fd, &peer_addr, &peer_addr_size);
  if(acc > 0)                                                                                                                                       
    printf("Accepted\n");                                                                                                          
  else                                                                                                                                                
    printf("Not accepted\n");
  return acc;
}

// Returns the socket virtual device that the client should use to access 
// the socket, if the connection is successfully established 
// and -1 in case of error
//
// Connect system call requires the address of the 
// server socket to request the connection and the size of that address.
//

int
clientConnection (char *host_name, int port)
{

  struct sockaddr_in serv_addr;
  struct hostent * hent;
  int socket_fd;
  int ret;

  //creates the virtual device for accessing the socket
  socket_fd = socket (AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0)
    return socket_fd;

  memset((char *) &serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  hent = gethostbyname(host_name);
  if (hent == NULL) {
        close (socket_fd);
	return -1;

  }
  memcpy((char *)&serv_addr.sin_addr.s_addr, (char *) hent->h_addr, hent->h_length);
  serv_addr.sin_port = htons(port);
  serv_addr.sin_family = PF_INET; 

  ret = connect (socket_fd, (struct sockaddr *) &serv_addr, sizeof (serv_addr));
  if (ret < 0)
  { 
	  close (socket_fd);
	  return (ret);
  } 

  return socket_fd;

}


int deleteSocket (int socket_fd)
{
  close (socket_fd);
}

