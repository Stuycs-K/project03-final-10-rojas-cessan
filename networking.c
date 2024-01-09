#include "networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {
  //printf("RUNNING CLIENT\n");

  int serverd;//store the socket descriptor here
  //create the socket
  serverd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverd == -1){
    printf("SD error %d: %s\n", errno, strerror(errno));
  }
  //printf("created socket\n");
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
  //printf("gotaddrinfo on %s \n", server_address);

  // //this code should get around the address in use error
  // int yes = 1;
  // int sockOpt =  setsockopt(serverd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  // err(sockOpt,"sockopt  error");
  // //bind
  // int b_check = bind(serverd, results->ai_addr, results->ai_addrlen);
  // if (b_check == -1){
  //   printf("BIND error %d: %s\n", errno, strerror(errno));
  // }

  //connect to the server
  int c_check = connect(serverd, results->ai_addr, results->ai_addrlen);
  if (c_check == -1){
    printf("CONCT error %d: %s\n", errno, strerror(errno));
  }
  printf("connected to server\n");
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    //printf("RUNNING SERVER HANDSHAKE\n");
    int client_socket;
    //accept the client connection
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    //printf("pre accept\n");
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    if (client_socket == -1){
      printf("ACCEPT error %d: %s\n", errno, strerror(errno));
    }
    printf("accepted the client connection\n");

    return client_socket;
}

/*Create and bind a socket.socket( domain, type, protocol )
* Place the socket in a listening state.
*/
int server_setup() {
  //printf("RUNNING SERVER SETUP\n");
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  // results = calloc(1,sizeof(struct addrinfo));
  // results->ai_family = AF_INET;
  // results->ai_socktype = SOCK_STREAM; //TCP socket
  // results->ai_flags = AI_PASSIVE; //only needed on server

  int g_check = getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL
  // hints->ai_family = AF_INET;
  // hints->ai_socktype = SOCK_STREAM; //TCP socket
  // hints->ai_flags = AI_PASSIVE; //only needed on server
  if (g_check != 0){
    printf("GAR error %d: %s\n", errno, strerror(errno));
  }
  //printf("getaddrinfo\n");
  //create the socket
  int clientd;//store the socket descriptor here
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  if (sd == -1){
    printf("SD error %d: %s\n", errno, strerror(errno));
  }
	//printf("created socket: %d\n", sd);
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
  //printf("set socket to listen state\n");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  //printf("free structs\n");
  return clientd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}

//PACKAGES
//struct package {char name[BUFFER_SIZE]; char MSG[BUFFER_SIZE];};
struct package * makepackage(struct package * package, char name[], char msg[]){
  strcpy(package->name, name);
  strcpy(package->MSG, msg);
  return package;
}

void printpackage(struct package * package){
  printf("%s: %s\n", package->name, package->MSG);
}


//sending messages
int sendmessage(int socket, char * username){
  //printf("usr: %s\n", username);
  //prompt
  char * input = malloc(BUFFER_SIZE);
  //printf("Type here:");
  //fflush(stdout);
  fgets(input, BUFFER_SIZE, stdin);
  // if (strchr(input, '\n')!=NULL){ //if token ends in newline
  //   *strchr(input, '\n')='\0'; //remove newline
  // }
  
  struct package * package = malloc ( sizeof(struct package));
  package = makepackage(package, username, input);
  //printf("usr: %s\n", package->name);
  //printpackage(package);
  if (strncmp(input, DISCONNECT, 2)==0){
    printf("You have left the chat.\n");
    int s_check = send(socket, package, sizeof(struct package), 0);
    err(s_check, "Sending\n");
    return -1;
  }
  //send
  int s_check = send(socket, package, sizeof(struct package), 0);
  err(s_check, "Sending\n");
  //printf("You: %s", input);
  return 0;
}

int recvmessage(int socket, char * othername){
  struct package * recieved = malloc ( sizeof(struct package));
  //recieved = makepackage(NULL, NULL);// = calloc( sizeof(struct package));
  int r_check = recv(socket, recieved, sizeof(struct package), 0);
  err(r_check, "Recving\n");
  //disconnect
  if (strncmp(recieved->MSG, DISCONNECT, 2)==0){
    printf("%s has left the chat.\n", recieved->name);
    return -1;
  }
  //print
  //printpackage(recieved);
  //int p_check = printf("%s: %s", recieved->name, recieved->MSG);
   printf("othername: %s\n", recieved->name);
   printf("message: %s\n", recieved->MSG);
  //err(p_check, "printing\n");
  return 0;
}
