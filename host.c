#include "host.h"

//  REMINDER FOR LATER THAT WE NEED TO WRITE THE README

/*

GAME HOST (main) should:
1. Allow multiple players to join the game. (fork process) do we need server?
2. Print an introduction and instructions for the players.
3. Assign player numbers. First to join is player one, second is player 2, and so on...
4. Print out a list of topics (ex. history, science, math) for player 1 to choose from. 
5. After selection, the host will access the corresponding topic's Q&A file, read it as
intended to place the current question and answer into shared memory.
6. Allow the players to take turns to enter in answers (with semaphores) until somebody's
response matches the current stored answer. Add one point to that player, then move on
to the next question.
7. Keep asking questions until a user types "end game" or the Q&A file ends.

*/

//prints errno
int err(){
  printf("Error %d: %s\n", errno, strerror(errno));
  exit(1);
}

// required
union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};   

/*
Should make the shared memory segment (one integer), 
semaphore and file called story.txt (open the file with the truncate flag to erase any prior data.)
Set any values that are needed.
*/

#define KEY 5849392

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

  view();
}








int semaphore_main(){
    printf("Attempting to open resource...\n");
  int semd = semget(KEY, 1, 0); // get access
  if (semd==-1) err();

  struct sembuf sb;
  sb.sem_num = 0; // sets index of semaphore to work on as 0
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; // setting the operation to down (not available)
  semop(semd, &sb, 1); // perform 1 operation w semd and sembuf sb, lock semaphore?

  // open file or something ehre.... ask question perhaps......

    // Prompt the use for the next line to be added to the story.
    // Read the user input from stdin
    char question[1000];
    char buff[1000];
    question = ask_question(1, buff); // change later TAKE THE QUESTION
    printf("Here's your next question: %s ", question);
    char answer[1000];
    fgets(answer, 1000, stdin);
    // SEND THIS INPUT TO CHECK_ANSWER(CHAR* ANSWER)

    // ... and write the size to the shared memory . FIXXX
  *data = strlen(sentence)+1;
  shmdt(data);

  // Release the semaphore, and end the write program.
  sb.sem_op = 1; // do i need this??
  semop(semd, &sb, 1); //perform the operation

  close(file);

}


/* ---------------- SEMAPHORE END ----------------------- */

// handles flow of the game, forking(?)
int main(){
    // a bunch of stuff should go here (????) with forking and perhaps a server, we should figure that out
    return 0;
    printf("Player %d, here's your next question: "); 
    ask_question(1); // 1 is a placeholder
}

/* Called in main whenever the host should ask another question.
"q_num" refers to the question number to be asked. This function will go through the Q&A file
and ask the corresponding question. */
void ask_question(int q_num){
    char* question;
    // question should be found by searching through the file
    printf("%s\n", question);
}