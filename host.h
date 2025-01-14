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

#ifndef HOST_H
#define HOST_H

int err();
#define WKP "mario"

int main();
char* ask_question(int file_des, char* question);
void find_question(char *topic, char *question, char *answer);
void delete_pipes();

#endif
