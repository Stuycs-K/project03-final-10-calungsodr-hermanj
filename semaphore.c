#include "semaphore.h"

#define KEY 5849392
// !!!!!
// UNCOMMENT WHEN DONEEEEEEE!!!!!
// !!!!!
// required, might have issues w mac i forgot yea it does
/*union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};   */

/* ---------- SEMAPHORE FOR ACCESS TO ANSWER ------------- */
void create_semaphore(){
    // create semaphore (blocks write access when it's not the right turn)
    int semd = semget(KEY, 1, IPC_CREAT | 0600);
    if (semd==-1) err();

    // initialize semaphore value to 1, making it availible
    union semun us;
    us.val = 1; // make us = 1 availible
    semctl(semd, 0, SETVAL, us); // set the value to us... currently 1, meaning available!!
}

// Remove the shared memory and the semaphore
void remove_semaphore(){
  printf("Removed shared memory and semaphore.\n");
  // remove semaphore
  int semd = semget(KEY, 1, 0);
  if (semd==-1) err();

  semctl(semd, IPC_RMID, 0);
// wasn't defined yet
  //view();
}

void lock_semaphore(){
  int semd = semget(KEY, 1, 0); // get access
  if (semd==-1) err();

  struct sembuf sb;
  sb.sem_num = 0; // sets index of semaphore to work on as 0
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; // setting the operation to down (not available)
  semop(semd, &sb, 1); // perform 1 operation w semd and sembuf sb, lock semaphore?
}

void unlock_semaphore(){
  int semd = semget(KEY, 1, 0); // get access
  if (semd==-1) err();

  struct sembuf sb;
  sb.sem_num = 0; // sets index of semaphore to work on as 0
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = 1; // setting the operation to up (available)
  semop(semd, &sb, 1); // perform 1 operation w semd and sembuf sb, lock semaphore?
}
