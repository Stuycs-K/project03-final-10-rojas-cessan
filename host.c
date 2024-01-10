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
  //handshake
  printf("Waiting for connection...\n");
  int listen_socket= server_setup();//happens once
  //int client_socket = server_tcp_handshake(listen_socket);//happens a lot
  //printf("server connected\n");

  //multi???
  //username prompt
  char * username = malloc (BUFFER_SIZE);
  printf("Type your username here: ");
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);
  if (strchr(username, '\n')!=NULL){ //if token ends in newline
    *strchr(username, '\n')='\0'; //remove newline
  }
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
    for (i = 0; i < c; i++){
            FD_SET(clients[i], &read_fds);
    }
    i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);
    err(i, "select");
    //if standard in, use fgets
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1]=0;
        printf("Recieved from terminal: '%s'\n",buff);
    }
    else if(FD_ISSET(listen_socket, &read_fds)){
      // if socket
          //accept the connection
          socklen_t sock_size;
          struct sockaddr_storage client_address;
          sock_size = sizeof(client_address);
          int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          printf("Connected, waiting for data.\n");

          //read the whole buff
          read(client_socket,buff, sizeof(buff));
          //trim the string
          buff[strlen(buff)-1]=0; //clear newline
          if(buff[strlen(buff)-1]==13){
              //clear windows line ending
              buff[strlen(buff)-1]=0;
          }
        c++; //one more client
    }
    else{
      int z = 0;
      for (i = 0; i < c; i++) {
      if (FD_ISSET(clients[z], &read_fds)){
        int dc_check = recvmessage(clients[i]);
        if (dc_check < 0){
          exit(0);
        }
        else{
          int dc_check = sendmessage(clients[i], username);
          if (dc_check < 0){
            //kill(p, SIGKILL);
            exit(0);
          }

        }
      }


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
