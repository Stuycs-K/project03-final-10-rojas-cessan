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
int sendmessage(int socket, char * username, char * input, int firstsend){
 // printf("SENDING MSGS\n");
  struct package * package = malloc ( sizeof(struct package));
  package = makepackage(package, username, input);

//disconnect
  if (strncmp(input, DISCONNECT, 2)==0){
    printf(BLU "You have left the chat." RESET);
    printf("\n");
    int s_check = send(socket, package, sizeof(struct package), 0);
    //err2(s_check, "Sending\n");
    free(package);
    return -1;
  }
  //send
  int s_check = send(socket, package, sizeof(struct package), 0);
  //check if disconnected socket
  if (s_check == 0){
    printf(BLU "A socket has closed." RESET);
    printf("\n");
    free(package);
    return SOCKETCLOSED;
  }
  //err2(s_check, "Sending\n");



  //chat chat_log
  if (firstsend == 0){
    int chat_log_file;
    chat_log_file = open("chat_log.txt", O_WRONLY | O_APPEND, 0644); //only adds
    char * str = malloc(BUFFER_SIZE);
    strcat(str, username);
    strcat(str, ": ");
    strcat(str, input);
    int w = write(chat_log_file, str, BUFFER_SIZE);
    close(chat_log_file);
    err2(w, "writing");
  }
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
    printf("%s%s has left the chat.%s\n", BLU, recieved->name, RESET);
    free(recieved);
    return -1;
  }
  if (strcmp(recieved->MSG, DCCODE)==0){
    //printf("It's wokring\n");
    printf("%s%s has left the chat.%s\n", BLU, recieved->name, RESET);
    free(recieved);
    return 0;
  }
  //print
  //printf(RED);
  printf( "%s%s:%s %s", RED, recieved->name, RESET, recieved->MSG);
  //printf(RESET);
  //err2(p_check, "printing\n");
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
    printf("%s%s has left the chat.%s\n", BLU, recieved->name, RESET);
    free(recieved);
    return -1;
  }
  if (strcmp(recieved->MSG, DCCODE)==0){
    //printf("It's wokring\n");
    printf("%s%s has left the chat.%s\n", BLU, recieved->name, RESET);
    free(recieved);
    return 0;
  }
  //print
  printf( "%s%s:%s %s", RED, recieved->name, RESET, recieved->MSG);
  //err2(p_check, "printing\n");
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
