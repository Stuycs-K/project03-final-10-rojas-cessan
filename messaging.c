#include "messaging.h"

//PACKAGES
//struct package {char name[BUFFER_SIZE]; char MSG[BUFFER_SIZE];};
struct package * makepackage(struct package * package, char name[], char msg[]){
  strcpy(package->name, name);
  strcpy(package->MSG, msg);
  return package;
}

void printpackage(struct package * package){
  printf("%s: %s\n", package->name, package->MSG);
}


//sending messages
int sendmessage(int socket, char * username){

  //prompt
  char * input = malloc(BUFFER_SIZE);
  //fflush(stdout);
  fgets(input, BUFFER_SIZE, stdin);
  // if (strchr(input, '\n')!=NULL){ //if token ends in newline
  //   *strchr(input, '\n')='\0'; //remove newline
  // }
  
  struct package * package = malloc ( sizeof(struct package));
  package = makepackage(package, username, input);

//disconnect
  if (strncmp(input, DISCONNECT, 2)==0){
    printf("You have left the chat.\n");
    int s_check = send(socket, package, sizeof(struct package), 0);
    err2(s_check, "Sending\n");
    return -1;
  }

  //send
  int s_check = send(socket, package, sizeof(struct package), 0);
  err2(s_check, "Sending\n");
  return 0;
}

int recvmessage(int socket, char * othername){
  struct package * recieved = malloc ( sizeof(struct package));
  int r_check = recv(socket, recieved, sizeof(struct package), 0);
  err2(r_check, "Recving\n");

  //disconnect
  if (strncmp(recieved->MSG, DISCONNECT, 2)==0){
    printf("%s has left the chat.\n", recieved->name);
    return -1;
  }
  //print
  int p_check = printf("%s: %s", recieved->name, recieved->MSG);
  err2(p_check, "printing\n");
  return 0;
}

void err2(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}