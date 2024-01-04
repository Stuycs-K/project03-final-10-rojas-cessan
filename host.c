#include "networking.h"

static void sighandler( int signo ){
    if (signo==SIGINT){
        printf("QUITTING SERVER\n");
        //remove(3);
        exit(0);
    }
}

void server_logic(int client_socket){
// Listens for a string (use the buffer size),
  char recieved[BUFFER_SIZE];
  int r_check = read(client_socket, recieved, BUFFER_SIZE);
  if (r_check < 0){
    printf("BCR error %d: %s\n", errno, strerror(errno));
  }
  printf("recieved: %s", recieved);

  //Send
   char input[BUFFER_SIZE];
  printf("Type here:");
  fflush(stdout);
  fgets(input, BUFFER_SIZE, stdin);
  int w_check = send(client_socket, input, BUFFER_SIZE, 0);
  if (w_check < 0){
    printf("FSW error %d: %s\n", errno, strerror(errno));
  }
  //printf("wrote %s to client\n", changed);
  //close(client_socket);

}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  int listen_socket= server_setup();//happens once
  int client_socket;
  //listen_socket = server_setup();//happens once
    client_socket = server_tcp_handshake(listen_socket);//happens a lot
    printf("server handshake completed\n");
    while (1){
        server_logic(client_socket);
    }
    close(client_socket);
    close(listen_socket);
  
}
