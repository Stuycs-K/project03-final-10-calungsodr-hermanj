#include "host.h"

#define MAX_PLAYERS 5 // ten players max can play

//  REMINDER FOR LATER THAT WE NEED TO WRITE THE README

/*

GAME HOST (main) should:
1. Allow multiple players to join the game. (fork process) do we need server?
2. Print an introduction and instructions for the players.
3. Assign player numbers. First to join is player one, second is player 2, and so on...
4. Print out a list of topics (ex. history, science, math) for player 1 to choose from. 
5. After selection, the host will access the corresponding topic's Q&A file, read it as
intended to place the current question and answer into shared memory.
6. Each player gets a chance to answer a new question. If it's right. Add one point to that player, then move on
to the next question.
7. Keep asking questions until a user types "end game" or the Q&A file ends.

*/

int err(){
  printf("errno %d\n", errno);
  printf("%s\n",strerror(errno));
  exit(1);
}

static int histq_num = 0;
static int geoq_num = 0;
static int mathq_num = 0;

void delete_pipes(){
  for (int i = 0; i<MAX_PLAYERS; i++){
    char pipe_name[10];
    snprintf(pipe_name,10,"player%d",i+1); // players named "player1" "player2" and so on
    unlink(pipe_name);
  }
}

// for pipe, look for sigpipe
// SIGNAL HANDLING
static void sighandler(int signo){
    if (signo == SIGINT){
      printf("\nDisconnected, game over");
      delete_pipes();
      exit(0);
    }
    if (signo == SIGPIPE){
      printf("\nDisconnected pipe.\n");
    }
}

// handles flow of the game, forking(?)
int main(){

    int from_client = 0;
    // make WKP
    if (mkfifo(WKP, 0644)==-1) err();

    // open wkp.[blocks]
    from_client = open(WKP, O_RDONLY);
    if (from_client==-1) err();
    printf("server setup done: created WKP, waiting for client\n");

    // for signals
    signal(SIGPIPE, sighandler);
    signal(SIGINT, sighandler);

    // creates array of player pipes
    for (int i = 0; i<MAX_PLAYERS; i++){
      char pipe_name[10];
      snprintf(pipe_name,10,"player%d",i+1); // players named "player1" "player2" and so on
      int make = mkfifo(pipe_name, 0644);
      if (make == -1){
        perror("Cannot create player pipe.");
      }
    }

    printf("welcome, instructions here...\n");
    printf("Player %d, please choose a topic (History, Science, Math): ", 1); //1 is a place holder
    char topic[20];
    fgets(topic, sizeof(topic), stdin);

    //get rid of \n and lowercase all
    for (int i = 0; i < sizeof(topic); i++) {
      topic[i] = tolower(topic[i]);
      if (topic[i] == '\n') {
        topic[i] = '\0';
        i = sizeof(topic);
      }
    }

    char question[500]; //change to malloc......
    char answer[500];
    int curr_player = 1;
    // deal with point system, initialize everyone's point system to 0 here
    // make an array of points?

    while(1){
      // loop through the pipes to speak to a specific one
      find_question(topic, question, answer);

      // if it ran out of questions, say that and then break the loop to end the game
      if(strlen(question)==0){
        printf("No more questions! Game over."); // separate display points function
        break;
      }

      // asks the next player the question
      printf("Player %d, here's your question:\n%s\n", curr_player,question);

      // open player pipe to read from them
      char player_pipe[10];
      snprintf(player_pipe,10,"player%d",curr_player); // players named "player1" "player2" and so on

      int pp = open(player_pipe, O_RDONLY);
      if (pp == -1) err();

      // tells the player pipe which number it is
      // this is wrong, the player should tell it's pid, THEN the server will open a private pipe with that pid
      char* player_num;
      snprintf(player_num, 3, "%d", curr_player); 
      int w = write(player_pipe, player_num, strlen(player_num)+1);
      if (w==-1){
        break;
      }

      char player_answer[500];
      // ok so we have to make it so that the player pipe writing side will send in a stdin input
      if(read(pp,player_answer,sizeof(player_answer))>0){
        // remove trailing newline here i forgot how
        if (strcmp(player_answer,"end game")==0){
          printf("Player ended the game.\n");
          break; // point function
        }
        if (strcmp(player_answer,answer)==0){
          printf("Correct! Point added.");
          // add point........ look at array and just add not done yet
          // handle lowercase
        }
        else printf("Wrong! The right answer is: %s",answer);
      }
      close(pp);

      curr_player = (curr_player%MAX_PLAYERS)+1; // so it wraps
    }
    // deal with final scores... print from array.... function

    // close file remove semaphore game end???
    delete_pipes();
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

void find_question(char * topic, char* question, char* answer) {
	char topicbuff[20];
	snprintf(topicbuff, 20, "%s.txt", topic); //adds .txt to the topic
	//printf("%s\n", topicbuff);
	FILE * readfile;
	readfile = fopen(topicbuff, "r");
	if (readfile == NULL) {
		err();
	}

	char line[1000];
	if (strcmp(topic, "history") == 0) {
		for (int i = 0; i <= histq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
		histq_num++;
	}
	else if (strcmp(topic, "geography") == 0) {
		for (int i = 0; i <= geoq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
		geoq_num++;
	}
	else if (strcmp(topic, "math") == 0) {
		for (int i = 0; i <= mathq_num; i++) {
			fgets(line, sizeof(line), readfile);
		}
		mathq_num++;
	}
	char * linepointer = line;
	char* q = strsep(&linepointer, ":");
	printf("question: %s\n", question);
	char* a = strsep(&linepointer, "\n");

  // should also deal with if tehre's nothing left

  strncpy(question,q,strlen(q));
  strncpy(answer,a,strlen(a)); // to be used up in main

  // close file
}

