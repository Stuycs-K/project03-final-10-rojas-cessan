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
  printf("Waiting for connection...\n");

  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");

  //init
  fd_set read_fds;
  char buff[1025]="";

  while(1){
    //printf("while start\n");
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_socket,&read_fds);
        printf("before sselect\n");
        int i = select(server_socket+1, &read_fds, NULL, NULL, NULL);
        err(i, "select");
        printf("after sselect\n");

  //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
          printf("STDIN\n");
            fgets(buff, sizeof(buff), stdin);
            //buff[strlen(buff)-1]=0;
           // printf("sending this buff: %s\n", buff);
            int dc_check =  sendmessage(server_socket, username, buff);
            if (dc_check < 0){
              printf("You left the chat.\n");
              exit(0);
            }
            //printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(server_socket, &read_fds)) {
          printf("SS\n");
           // printf("Connected, waiting for data.\n");

            //read the whole buff
            int dc_check = recvmessage(server_socket);
            if (dc_check < 0){
              printf("You left the chat.\n");
              exit(0);
            }

           // printf("\nRecieved from host '%s'\n", buff);
            //close(server_socket);
        }
      }
}

  // pid_t p;
  // p = fork();
  // if (p<0){
  //     printf("fork error");
  //     exit(1);
  // }
  // else if (p==0){//recv
  //   while(1){
  //     int dc_check = recvmessage(server_socket);
  //     if (dc_check<0){
  //       err(dc_check, "recv");
  //       exit(0);
  //     }
  //   }
  //   close(server_socket);
  //   exit(0);
  // }
  // else{//recv
  //   while(1){
  //     int status;
  //     int w_check = waitpid(p, &status, WNOHANG);
  //     if (w_check != 0 ){
  //       printf("Quitting Sending Loop WNOHANG\n");
  //       kill(p, SIGKILL);
  //       exit(0);
  //     }

  //     int dc_check = sendmessage(server_socket, username);
  //     if (dc_check < 0){
  //       kill(p, SIGKILL);
  //       exit(0);
  //     }
  //   }
  //   //close(server_socket);
  //   exit(0);
  // }
