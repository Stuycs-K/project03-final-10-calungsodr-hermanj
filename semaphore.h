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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

void create_semaphore();
void remove_semaphore();
void lock_semaphore();
void unlock_semaphore();

#endif
