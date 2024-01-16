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
#define DCCODE "9*72bdjso[[[8]]]....~"
//COLORS
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
//
#define BUFFER_SIZE 1024
#define SOCKETCLOSED 2
void err2(int i, char*message);
int sendmessage(int socket, char * username, char * input, int firstsend);
int recvmessage(int socket);
int recvmessagestring(int socket, char * tempuser, char * tempbuff);
struct package {char name[1024]; char MSG[1024];};
struct package * makepackage(struct package * package,char name[], char msg[]);
void printpackage(struct package * package);
#endif
