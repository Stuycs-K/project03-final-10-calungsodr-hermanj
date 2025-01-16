#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <ctype.h>
#include <signal.h>

#ifndef HOST_H
#define HOST_H

int err();
#define MAX_QUESTION 5;
#define WKP "mario"

int main();
struct player_struct create_player(char* player_num);
void remove_player(int ind);
void print_points();
void find_question(char * topic, char* question, char* answer);
void delete_pipes();
static void sighandler(int signo);

#endif
