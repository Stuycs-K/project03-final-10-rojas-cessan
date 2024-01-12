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
  int * clients = calloc (10, sizeof(int));// An array for max 10 clients
  fd_set read_fds;
  char buff[1025]="";
while(1){
    printf("start of while\n");
    int i = 0;
    //select params; must be reset when reused
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket,&read_fds);

    int max = listen_socket;
    for (int a = 0; clients[a]; a++){
            FD_SET(clients[a], &read_fds);
            max=clients[a];
    }

    //select
    printf("before select\n");
    printf("fds: %d\n", (listen_socket+max+1));
    i = select(max+1, &read_fds, NULL, NULL, NULL);
//listen_socket+max
    err(i, "select");
    printf("after select\n");

    //if standard in, use fgets
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      // printf("Type yo here: ");
      //  fflush(stdout);
        fgets(buff, sizeof(buff), stdin);
        //buff[strlen(buff)-1]=0;
        printf("sending buff to clients: %s\n", buff);
        for (int d = 0; clients[d]; d++){
            sendmessage(clients[d], username, buff);
        }
        //printf("Recieved from terminal: '%s'\n",buff);
    }
    else if(FD_ISSET(listen_socket, &read_fds)){
      printf("in socket listen\n");
      // if socket LISTEN
          //accept the connection
          socklen_t sock_size;
          struct sockaddr_storage client_address;
          sock_size = sizeof(client_address);
          printf("before accept listen\n");

          int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          c++;
          int last = 0;
           for (int a = 0; clients[a]; a++){
            //FD_SET(clients[a], &read_fds);
            last=a;
           }
           clients[last] = client_socket;

           printf("\nCLIENT ADDED\n");
           // close(client_socket);
           // FD_CLR(client_socket ,&read_fds);
           //client_socket = -1;
          // printf("end socket listen\n");
    }
    else{
    for (int n = 0; clients[n]; n++){
      printf("in client loop\n");
      if(FD_ISSET(clients[n], &read_fds)){
      // if socket CLIENTS
          printf("Connected, waiting for data.\n");

          //read the whole buff
          int r_check = recvmessage(clients[n]);
          err(r_check, "read listen");
          //trim the string
          buff[strlen(buff)-1]=0; //clear newline
          if(buff[strlen(buff)-1]==13){
              //clear windows line ending
              buff[strlen(buff)-1]=0;
          }
          //printing to server terminal
          printf("Recieved from client %d: %s", n, buff);
          // close(clients[n]);
          // FD_CLR(clients[n] ,&read_fds);
      }
    }
    }
    printf("while loop completed\n");





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
