#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef HOST_H
#define HOST_H

#define histq_num 0
#define geoq_num 0
#define mathq_num 0

int main();
void ask_question(int file_des);
char* find_question(char* topic);

#endif
