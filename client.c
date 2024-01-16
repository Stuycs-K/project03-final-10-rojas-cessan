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

  //username
  char * username = malloc (BUFFER_SIZE);
  printf("Type your username here: ");
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);
  if (strchr(username, '\n')!=NULL){ //if token ends in newline
    *strchr(username, '\n')='\0'; //remove newline
  }

  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("CESSENGER has started...\nWaiting for connection...\n");

  int server_socket = client_tcp_handshake(IP);
  printf("Welcome to the chatroom! Start typing to send messages. Type '.d' to disconnect\n");

  //init
  fd_set read_fds;
  char buff[1025]="";

  while(1){
    //printf("while start\n");
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_socket,&read_fds);
        //printf("before sselect\n");
        int i = select(server_socket+1, &read_fds, NULL, NULL, NULL);
        err(i, "select");
        //printf("after sselect\n");

  //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
          //printf("STDIN\n");
            fgets(buff, sizeof(buff), stdin);
            //buff[strlen(buff)-1]=0;
           // printf("sending this buff: %s\n", buff);
            int dc_check =  sendmessage(server_socket, username, buff, 0);
            if (dc_check < 0){
              exit(0);
            }
        }

        // if socket
        if (FD_ISSET(server_socket, &read_fds)) {
          //printf("SS\n");
           // printf("Connected, waiting for data.\n");

            //read the whole buff
            char tempuser[BUFFER_SIZE];
            char tempbuff[BUFFER_SIZE];
            int dc_check = recvmessagestring(server_socket, tempuser, tempbuff);
            if (dc_check < 0){
              exit(0);
            }
            if (dc_check == SOCKETCLOSED){
              printf("Chat ended.");
              exit(0);
            }

        }
      }
}
