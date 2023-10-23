#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define NMAX 100
#define MAX_CLIENTS 10

int server_running;

typedef struct  {
	int client_num;
	int n ;
} Question;
typedef struct  {
	int numbers[NMAX];
	int count;
	int client_num;
} Response;
#endif