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
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_socket,&read_fds);
        int i = select(server_socket+1, &read_fds, NULL, NULL, NULL);
  }
  //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(server_socket, &read_fds)) {
            //accept the connection
            socklen_t sock_size;
            struct sockaddr_storage client_address;
            sock_size = sizeof(client_address);
            int server_socket = accept(server_socket,(struct sockaddr *)&client_address, &sock_size);
            printf("Connected, waiting for data.\n");

            //read the whole buff
            read(server_socket,buff, sizeof(buff));
            //trim the string
            buff[strlen(buff)-1]=0; //clear newline
            if(buff[strlen(buff)-1]==13){
                //clear windows line ending
                buff[strlen(buff)-1]=0;
            }

            printf("\nRecieved from host '%s'\n", buff);
            close(server_socket);
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
