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

#define KEY 5849392
static int histq_num;
static int geoq_num;
static int mathq_num;
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

/* ---------------- SEMAPHORE END ----------------------- */

// handles flow of the game, forking(?)
int main(){
    // create shared memory .,.. ?? initialize

    // should create player pipes here as well..?

    // access!
    create_semaphore();

    printf("welcome, instructions here...\n");
    printf("Player 1, please choose a topic (History, Science, Math): ");
    char topic[20];
    fgets(topic, sizeof(topic), stdin); // do we have to do that thing where we add '\0' to the end somehow. or remove new line i forgot what it was

	//get rid of \n and lowercase all
	for (int i = 0; i < sizeof(topic); i++) {
		topic[i] = tolower(topic[i]);
		if (topic[i] == '\n') {
			topic[i] = '\0';
			i = sizeof(topic);
		}
	}
	
    // get file_name by adding .txt to the end of chosen topic
	find_question(topic);

    // open file... use the method that joy is writing??
    // if file doesnt work, remove the semaphore and stop...

    // fork a server for every player... have to figure out what to do with that

    while(1){
      lock_semaphore();
      // use ask_question method to print the question....
      // if it ran out of questions, say that and then break the loop to end the game

      unlock_semaphore();
    }
    // close file remove semaphore game end???
	printf("Player %d, here's your next question: ", 1);
	char buff[1000];
	ask_question(1, buff); // 1 is a placeholder
	return 0;
}

/* Called in main whenever the host should ask another question.
"q_num" refers to the question number to be asked. This function will go through the Q&A file
and ask the corresponding question. */
//copy the code for check_answer(char* answer)s
char* ask_question(int file_des, char* question){ //change later
    // question should be found by searching through the file with q_num as the number question
	printf("%s\n", question);
	return question;
}

void find_question(char * topic) {
	char topicbuff[20];
	snprintf(topicbuff, 20, "%s.txt", topic); //adds .txt to the topic
	//printf("%s\n", topicbuff);
	FILE * readfile;
	readfile = fopen(topicbuff, "r");
	if (readfile == NULL) {
		err();
	}
	char line[1000];
	char* question;
	char* answer;
	if (strcmp(topic, "history") == 0) {
		for (int i = 0; i <= histq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
	}
	else if (strcmp(topic, "geography") == 0) {
		for (int i = 0; i <= geoq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
	}
	else if (strcmp(topic, "math") == 0) {
		for (int i = 0; i <= mathq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
	}
	char * linepointer = line;
	question = strsep(&linepointer, ":");
	printf("question: %s\n", question);
	answer = strsep(&linepointer, "\n");
	printf("answer: %s\n", answer);
}

