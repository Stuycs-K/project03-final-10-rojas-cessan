#include "networking.h"

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
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");

  //username
  char username[BUFFER_SIZE];
  printf("Type your username here:");
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);

  pid_t p;
  p = fork();
  if (p<0){
      printf("fork error");
      exit(1);
  }
  else if (p==0){//send
    while(1){
      if (getppid()==1){
        printf("Quitting PID Loop\n");
        exit(0);
      }
      int dc_check = sendmessage(server_socket);
      if (dc_check < 0){
        printf("Quitting Sending Loop\n");
        exit(0);
      }
    }
    close(server_socket);
    printf("Quitting Child\n");
    exit(0);
  }
  else{//recv
    while(1){
      int dc_check = recvmessage(server_socket, "other");
      if (dc_check<0){
        exit(0);
      }
    }
    close(server_socket);
    exit(0);
  }
}
