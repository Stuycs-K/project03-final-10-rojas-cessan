#include "networking.h"
#include "messaging.h"

static void sighandler( int signo ){
    if (signo==SIGINT){
        printf(BLU "QUITTING SERVER\n" RESET);
        exit(0);
    }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  printf(CYN "CESSENGER " BLU);
  printf("has started...\n");
  //start chat log
  int chat_log_file;
  chat_log_file = open("chat_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); //happens once bc trunc
  close(chat_log_file);
  //username prompt
  char * username = malloc (BUFFER_SIZE);
  printf("Type your username here: " RESET);
  fflush(stdout);
  fgets(username, BUFFER_SIZE, stdin);
  if (strchr(username, '\n')!=NULL){ //if token ends in newline
    *strchr(username, '\n')='\0'; //remove newline
  }

  //handshake
  printf(BLU "Waiting for connections..." RESET);
  printf("\n");
  int listen_socket= server_setup();
  //init stuff
  int c = 0;
  int * clients = calloc (10, sizeof(int));// An array for max 10 clients
  fd_set read_fds;
  char buff[1025]="";
while(1){
  //checking filedescriptable
      // printf("filedescriptable: ");
      // for(int z = 0; clients[z]; z++){
      //   printf("%d, ", clients[z]);
      // }
      // printf("\n");
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
    //printf("fds: %d\n", (listen_socket+max+1)); //checking fd table
    i = select(max+1, &read_fds, NULL, NULL, NULL);
//listen_socket+max
    err(i, "select");

    //if standard in, use fgets

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        //checking filedescriptable
            // printf("filedescriptable: ");
            // for(int z = 0; clients[z]; z++){
            //   printf("%d, ", clients[z]);
            // }
            // printf("\n");
        fgets(buff, sizeof(buff), stdin);
        int boolean = 0;
        for (int d = 0; clients[d]; d++){
          //printf("sending to client %d\n", d);
            int dc_check = sendmessage(clients[d], username, buff, boolean);
            if (dc_check < 0){
              printf(BLU "Chat ended.\n" RESET);
              exit(0);
            }
            boolean = -1;
        }

    }
    else if(FD_ISSET(listen_socket, &read_fds)){
     // printf("in socket listen\n");
      // if socket LISTEN
          //accept the connection
          socklen_t sock_size;
          struct sockaddr_storage client_address;
          sock_size = sizeof(client_address);
        //  printf("before accept listen\n");

          int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          c++;
          int last = 0;
          if (clients[0]==0){
            clients[0] = client_socket;
          }
          else{
            for (int a = 0; a < sizeof(clients); a++){
              if (clients[a] == 0){
                clients[a] = client_socket;
                break;
              }
           }

          }


       //    printf("\nCLIENT ADDED\n");
           // close(client_socket);
           // FD_CLR(client_socket ,&read_fds);
           //client_socket = -1;
          // printf("end socket listen\n");
    }
    else{
    for (int n = 0; clients[n]; n++){
    //  printf("in client loop\n");
      if(FD_ISSET(clients[n], &read_fds)){
      // if socket CLIENTS

          //read the whole buff
          char tempuser[BUFFER_SIZE];
          char tempbuff[BUFFER_SIZE];
          int dc_check = recvmessagestring(clients[n], tempuser, tempbuff);

          //err(dc_check, "read listen"); //for some reason i cant have this
          if (dc_check < 0){ //.d disconnect check
            //tell others that someon left the chat
            for (int j=0; clients[j]; j++){
              if (j!=n){
                //printf("It's working, sending %s's message\n", tempuser);
                sendmessage(clients[j], tempuser, DCCODE, -1);
              }
            }
            //remove from client list
            clients[n] = -1;
            //shift down higher clients
            for (int j=n; clients[j] && j<9; j++){ //10 IS ARBITRARY

                clients[j] = clients[j+1];
                clients[9]=0;
            //  }
            }

            //exit(0);
          }
          else if (dc_check == SOCKETCLOSED){//SIGINT disconnect check
            //tell others that someon left the chat
            for (int j=0; clients[j]; j++){
              if (j!=n){
                //printf("It's working, sending %s's message\n", tempuser);
                sendmessage(clients[j], tempuser, DCCODE, -1);
              }
            }
            //remove from client list
            clients[n] = -1;
            //shift down higher clients
            for (int j=n; clients[j] && j<9; j++){ //10 IS ARBITRARY

                clients[j] = clients[j+1];
                clients[9]=0;
            //  }
            }
            //exit(0);
            //printf("exit?\n");
          }
          else{//normal
            //send to everyone else
            for (int j=0; clients[j]; j++){
              if (j!=n){
                sendmessage(clients[j], tempuser, tempbuff, -1);
              }
            }
          }

      }
    }
    }



  }

}
