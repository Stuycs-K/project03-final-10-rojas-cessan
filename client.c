#include "networking.h"

void clientLogic(int server_socket){
// Prompts the user for a string.
  char input[BUFFER_SIZE];
  printf("This is a prompt:\n");
  fgets(input, BUFFER_SIZE, stdin);
  // Send the user input to the client
    int w_check = write(server_socket, input, BUFFER_SIZE);
    if (w_check < 0){
      printf("FSW error %d: %s\n", errno, strerror(errno));
    }
    printf("writing to client %s\n", input);
  // Read the modified string from the server
    char recieved[BUFFER_SIZE];
    int r_check = read(server_socket, recieved, BUFFER_SIZE);
    if (r_check < 0){
      printf("BCR error %d: %s\n", errno, strerror(errno));
      exit(1);
    }
  // prints the modified string
    printf("recieved message: %s\n", recieved);

}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");

  while(1){
    clientLogic(server_socket);
  }
}
