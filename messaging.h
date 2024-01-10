#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include <time.h>

#ifndef MESSAGING_H
#define MESSAGING_H
#define DISCONNECT ".d"
#define BUFFER_SIZE 1024
void err2(int i, char*message);
int sendmessage(int socket, char * username);
int recvmessage(int socket);
struct package {char name[1024]; char MSG[1024];};
struct package * makepackage(struct package * package,char name[], char msg[]);
void printpackage(struct package * package);
#endif
