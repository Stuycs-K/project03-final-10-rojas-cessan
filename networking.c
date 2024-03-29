#include "networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {
  int serverd;//store the socket descriptor here
  //create the socket
  serverd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverd == -1){
    printf("SD error %d: %s\n", errno, strerror(errno));
  }

  //getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  results = calloc(5,sizeof(struct addrinfo));
  int g_check = getaddrinfo(server_address, PORT, hints, &results);
  // hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  if (g_check != 0){
    printf("GAR error %d: %s\n", errno, strerror(errno));
  }

  //connect to the server
  int c_check = connect(serverd, results->ai_addr, results->ai_addrlen);
  if (c_check == -1){
    printf("CONCT error %d: %s\n", errno, strerror(errno));
  }
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int client_socket;
    //accept the client connection
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    if (client_socket == -1){
      printf("ACCEPT error %d: %s\n", errno, strerror(errno));
    }

    return client_socket;
}

/*Create and bind a socket.socket( domain, type, protocol )
* Place the socket in a listening state.
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server

  int g_check = getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL
  if (g_check != 0){
    printf("GAR error %d: %s\n", errno, strerror(errno));
  }
  //create the socket
  int clientd;//store the socket descriptor here
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  if (sd == -1){
    printf("SD error %d: %s\n", errno, strerror(errno));
  }
	clientd = sd;
  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");

  //bind the socket to address and port
  int b_check = bind(clientd, results->ai_addr, results->ai_addrlen);
   if (b_check == -1){
    printf("BIND error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  //set socket to listen state
  int l_check = listen(clientd, 10);
  if (l_check == -1){
    printf("LISTEN error %d: %s\n", errno, strerror(errno));
  }

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return clientd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}