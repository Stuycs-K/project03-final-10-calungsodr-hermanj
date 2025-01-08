#include "host.h"
#include "semaphore.h"

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

// for pipe, look for sigpipe
// SIGNAL HANDLING
static void sighandler(int signo){
    if (signo == SIGINT){
      printf("\nDisconnected, game over");
      exit(0);
    }
    if (signo == SIGPIPE){
      printf("\nDisconnected pipe.\n");
    }
}

//prints errno
int err(){
  printf("Error %d: %s\n", errno, strerror(errno));
  exit(1);
}

// handles flow of the game, forking(?)
int main(){

    // for signals
    signal(SIGPIPE, sighandler);
    signal(SIGINT, sighandler);

    // get access!
    create_semaphore();

    // should create player pipes here as well..? not sure
    // array of pipes

    printf("welcome, instructions here...\n");
    printf("Player 1, please choose a topic (History, Geography, Math): ");
    char topic[20];
    fgets(topic, sizeof(topic), stdin); // do we have to do that thing where we add '\0' to the end somehow. or remove new line i forgot what it was

	// get rid of \n
	for (int i = 0; i < sizeof(topic); i++) {
		if (topic[i] == '\n') {
			topic[i] = '\0';
			i = sizeof(topic);
		}
	}
	
  // get file_name by adding .txt to the end of chosen topic

    // open file... use the method that joy is writing??
    // if file doesnt work, remove the semaphore and stop...

    // fork a server for every player... have to figure out what to do with that

    while(1){
      // loop through the pipes to speak to a specific one
      lock_semaphore();
      find_question(topic);
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
	fgets(line, sizeof(line), readfile);
	char * linepointer = line;
	question = strsep(&linepointer, ":");
	printf("question: %s\n", question);
	answer = strsep(&linepointer, "\n");
	printf("answer: %s\n", answer);
}

