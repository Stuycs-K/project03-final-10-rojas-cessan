#include "networking.h"
#include "messaging.h"

static void sighandler( int signo ){
    if (signo==SIGINT){
        printf("QUITTING SERVER\n");
        exit(0);
    }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  //username prompt
  char * username = malloc (BUFFER_SIZE);
  printf("Type your username here: ");
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);
  if (strchr(username, '\n')!=NULL){ //if token ends in newline
    *strchr(username, '\n')='\0'; //remove newline
  }

  //handshake
  printf("Waiting for connection...\n");
  int listen_socket= server_setup();
  //init stuff
  int c = 0;
  int clients[10];// An array for max 10 clients
  fd_set read_fds;
  char buff[1025]="";
  while(1){
    int i = 0;
    //select params; must be reset when reused
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket,&read_fds);
    for (int a = 0; a < c; a++){
            FD_SET(clients[a], &read_fds);
    }

    //select
    i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);
    err(i, "select");

    //if standard in, use fgets
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1]=0;
        for (int d = 0; d < c; d++){
            sendmessage(clients[d], username);
        }
        printf("Recieved from terminal: '%s'\n",buff);
    }
    if(FD_ISSET(listen_socket, &read_fds)){
      // if socket LISTEN
          //accept the connection
          socklen_t sock_size;
          struct sockaddr_storage client_address;
          sock_size = sizeof(client_address);
          int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          c++; //one more client
          printf("Connected, waiting for data.\n");

          //read the whole buff
          read(client_socket,buff, sizeof(buff));
          //trim the string
          buff[strlen(buff)-1]=0; //clear newline
          if(buff[strlen(buff)-1]==13){
              //clear windows line ending
              buff[strlen(buff)-1]=0;
          }
          printf("\nRecieved from client '%s'\n",buff);
          close(client_socket);
    }
    for (int n = 0; n < c; n++){
      if(FD_ISSET(clients[n], &read_fds)){
      // if socket CLIENTS
          //accept the connection
          socklen_t sock_size;
          struct sockaddr_storage client_address;
          sock_size = sizeof(client_address);
          int client_socket = accept(clients[n],(struct sockaddr *)&client_address, &sock_size);
          c++; //one more client
          printf("Connected, waiting for data.\n");

          //read the whole buff
          read(client_socket,buff, sizeof(buff));
          //trim the string
          buff[strlen(buff)-1]=0; //clear newline
          if(buff[strlen(buff)-1]==13){
              //clear windows line ending
              buff[strlen(buff)-1]=0;
          }
          printf("\nRecieved from client '%s'\n",buff);
          close(client_socket);
      }
    }





  }

}




//   //multi threading
//   pid_t p;
//   p = fork();
//   if (p<0){
//       printf("fork error");
//       exit(1);
//   }
//   else if (p==0){//recv
//     while(1){
//       int dc_check = recvmessage(client_socket); //placeholder
//       if (dc_check < 0){
//         exit(0);
//       }
//     }
//     close(client_socket);
//     close(listen_socket);
//     exit(0);
//   }
//   else{//send
//     while(1){
//       int status;
//       int w_check = waitpid(p, &status, WNOHANG);
//       if (w_check != 0 ){
//         printf("Quitting Sending Loop WNOHANG\n");
//         kill(p, SIGKILL);
//         exit(0);
//       }
//       int dc_check = sendmessage(client_socket, username);
//       if (dc_check < 0){
//         kill(p, SIGKILL);
//         exit(0);
//       }
//     }
//     exit(0);
//   }
//
// }
