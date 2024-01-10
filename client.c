#include "networking.h"
#include "messaging.h"

static void sighandler( int signo ){
    if (signo==SIGINT){
        printf("QUITTING CLIENT\n");
        //remove(3);
        exit(0);
    }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("Waiting for connection...\n");

  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");

  //username
  char * username = malloc (BUFFER_SIZE);
  printf("Type your username here: ");
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);
  if (strchr(username, '\n')!=NULL){ //if token ends in newline
    *strchr(username, '\n')='\0'; //remove newline
  }

  pid_t p;
  p = fork();
  if (p<0){
      printf("fork error");
      exit(1);
  }
  else if (p==0){//recv
    while(1){
      int dc_check = recvmessage(server_socket);
      if (dc_check<0){
        err(dc_check, "recv");
        exit(0);
      }
    }
    close(server_socket);
    exit(0);
  }
  else{//recv
    while(1){
      int status;
      int w_check = waitpid(p, &status, WNOHANG);
      if (w_check != 0 ){
        printf("Quitting Sending Loop WNOHANG\n");
        kill(p, SIGKILL);
        exit(0);
      }

      int dc_check = sendmessage(server_socket, username);
      if (dc_check < 0){
        kill(p, SIGKILL);
        exit(0);
      }
    }
    //close(server_socket);
    exit(0);
  }
}
