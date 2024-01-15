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
int sendmessage(int socket, char * username, char * input){
 // printf("SENDING MSGS\n");
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
  //check if disconnected
  if (s_check == 0){
    printf("socket closed.\n");
    return SOCKETCLOSED;
  }
  err2(s_check, "Sending\n");
  free(package);
  return 0;
}

int recvmessage(int socket){
 // printf("RECVING MSGS\n");
  struct package * recieved = malloc ( sizeof(struct package));
  int r_check = recv(socket, recieved, sizeof(struct package), 0);
  if (r_check == 0){
    printf("socket closed.\n");
    return SOCKETCLOSED;
  }
  err2(r_check, "Recving\n");

  //disconnect
  if (strncmp(recieved->MSG, DISCONNECT, 2)==0){
    // printf("Real dc\n");
    //printf("%s has left the chat.\n", recieved->name);
    return -1;
  }
  if (strcmp(recieved->MSG, DCCODE)==0){
    printf("It's wokring\n");
    printf("%s has left the chat.\n", recieved->name);
    return 0;
  }
  //print
  //printf("Normie\n");
  int p_check = printf("%s: %s", recieved->name, recieved->MSG);
  err2(p_check, "printing\n");
  free(recieved);
  return 0;
}

int recvmessagestring(int socket, char * tempuser, char * tempbuff){
 // printf("RECVING MSGS\n");
  struct package * recieved = malloc ( sizeof(struct package));
  int r_check = recv(socket, recieved, sizeof(struct package), 0);
  if (r_check == 0){
    printf("socket closed.\n");
    return SOCKETCLOSED;
  }
  err2(r_check, "Recving\n");

  //disconnect
  if (strncmp(recieved->MSG, DISCONNECT, 2)==0){
    printf("%s has left the chat.\n", recieved->name);
    return -1;
  }
  if (strcmp(recieved->MSG, DCCODE)==0){
    //printf("It's wokring\n");
    printf("%s has left the chat.\n", recieved->name);
    return 0;
  }
  //print
  int p_check = printf("%s: %s", recieved->name, recieved->MSG);
  err2(p_check, "printing\n");
  strcpy(tempuser, recieved->name);
  strcpy(tempbuff, recieved->MSG);
  free(recieved);
  return 0;
}

void err2(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
