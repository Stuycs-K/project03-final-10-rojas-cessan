#include "networking.h"

static void sighandler( int signo ){
    if (signo==SIGINT){
        printf("QUITTING SERVER\n");
        //remove(3);
        exit(0);
    }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  int listen_socket= server_setup();//happens once
  int client_socket = server_tcp_handshake(listen_socket);//happens a lot
  printf("server handshake completed\n");
  //multi threading
  pid_t p;
  p = fork();
  if (p<0){
      printf("fork error");
      exit(1);
  }
  else if (p==0){//send
    while(1){
      int dc_check = sendmessage(client_socket);
      if ((dc_check < 0)||(getppid()==1)){
        exit(0);
      }
    }
    close(client_socket);
    close(listen_socket);
    exit(0);
  }
  else{//recv
    while(1){
      int dc_check = recvmessage(client_socket);
      if (dc_check < 0){
        exit(0);
      }
    }
    close(client_socket);
    close(listen_socket);
    exit(0);
  }

}
