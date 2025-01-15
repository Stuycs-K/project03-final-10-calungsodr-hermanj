
#include "host.h"

#define MAX_PLAYERS 3
#define MAX_QUESTION 5;

//  REMINDER FOR LATER THAT WE NEED TO WRITE THE README

/*

GAME HOST (main) should:
1. Allow multiple players to join the game. (fork process) do we need server?
2. Print an introduction and instructions for the players.
3. Assign player numbers. First to join is player one, second is player 2, and so on...
5. After selection, the host will access the corresponding topic's Q&A file, read it as
intended to place the current question and answer into shared memory.
6. Each player gets a chance to answer a new question. If it's right. Add one point to that player, then move on
to the next question.
7. Keep asking questions until a user types "end game" or the Q&A file ends.

1/11 update to implement
1. player sends the host its PID (which will be the pipe name)
2. host adds each PID to an array that stores the pipe names
3. the host loops through this array of pipes to know which pipe to send a question to

CURRENT PROBLEMS: 
- exiting the host doesnt make the player exit
- lowercase for answers (not case sensitive, also add in instructions)
*/

struct player_struct {
  int pid;
  char pipe_name[20];
  int score;
};

struct player_struct players[MAX_PLAYERS]; // array of players!!!
int num_players = 0;
static int histq_num = 0;
static int geoq_num = 0;
static int mathq_num = 0;

struct player_struct create_player(char* player_num){
// use heap memory, so calloc or malloc
  struct player_struct p;
  snprintf(p.pipe_name,20,"%s",player_num); // use player index for pipe name
  p.score = 0;
  return p;
}

void print_points(){
  printf("FINAL POINT COUNT:\n");
    for (int i = 0; i<MAX_PLAYERS; i++){
	    printf("Player %d: %d\n", i+1, players[i].score);
    // possible add-on -- tell who the winner is
  }
}

void delete_pipes(){
  for (int i = 0; i<num_players; i++){
	int pp = open(players[i].pipe_name, O_WRONLY);
	char end[100] = "end";
	write(pp, end, sizeof(end));
	unlink(players[i].pipe_name);
  }
  unlink(WKP);
}

// for pipe, look for sigpipe
// SIGNAL HANDLING
static void sighandler(int signo){
  if (signo == SIGINT){
    printf("\nDisconnected game. Players will be disconnected automatically.\n");
	delete_pipes();
	printf("pipes deleted successfully\n");
	remove(WKP);
	printf("wkp removed successfully\n");
	for (int i = 0; i<MAX_PLAYERS; i++){
	  printf("players currently being disconnected\n");
	  if (players[i].pid>0){
		kill(players[i].pid,SIGINT);
	  }
	}
    exit(0);
  }
  if (signo == SIGPIPE){
    printf("\nDisconnected pipe.\n");
		delete_pipes();
		exit(0);
  }
}

// handles flow of the game, forking(?)
int main(){
  // for signals
  signal(SIGPIPE, sighandler);
  signal(SIGINT, sighandler);

  // make WKP
  if (mkfifo(WKP, 0644)<0) {
	perror("error in making WKP");
  }

  printf("Server setup finished, waiting for %d players to join! (Tip: type './player' in a different terminal window.)\n\n", MAX_PLAYERS);

  // open wkp.[blocks]
  int from_client = open(WKP, O_RDONLY);
  if (from_client==-1) perror("can't open WKP 1");

  char player_pipe[20];
  // for every player ! need the max to begin
  while (num_players<MAX_PLAYERS){
  // if there's something to read!
	if (read(from_client,player_pipe,sizeof(player_pipe))>0){
	  players[num_players] = create_player(player_pipe);

	  mkfifo(players[num_players].pipe_name, 0644);
	  printf("Player %d joined!\n", num_players+1);
	  num_players++;
	}
  }

  close(from_client);

  printf("welcome, instructions here...\n");
  printf("to end the game, write \"end\" in the player window\n");
  printf("Please choose a topic (History, Geography, Math): ");

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

  /*
  if (strcmp(topic, "history") != 0 || strcmp(topic, "geography") != 0 || strcmp(topic, "math")) {
	printf("You get ONE more try\nPlease choose a topic (History, Geography, Math): ");
	memset(topic, 0, sizeof(topic));
	fgets(topic, sizeof(topic), stdin);

	//get rid of \n and lowercase all
	for (int i = 0; i < sizeof(topic); i++) {
	  topic[i] = tolower(topic[i]);
	  if (topic[i] == '\n') {
		topic[i] = '\0';
		i = sizeof(topic);
	  }
	}
  }
   */
  int curr_player = 0;
  // deal with point system, initialize everyone's point system to 0 here
  // make an array of points?

  while(1){
	// loop through the pipes to speak to a specific one
	char question[500];
	char answer[500];
	memset(question, 0, sizeof(question));
	memset(answer, 0, sizeof(answer));
	find_question(topic, question, answer);
	//printf("this is the answer from the while loop: %s\n", answer);
	if(strlen(question)==0){
	  printf("No more questions! Game over.\n"); // separate display points function
	  delete_pipes();
	  break;
	}

	// send question and answer to player through pipe!
	int send_q = open(players[curr_player].pipe_name,O_WRONLY);
	if (send_q < 0){
	  delete_pipes();
	  perror("cannot open player pipe");
	  break;
	}
	write(send_q, "go", sizeof("go"));
	printf("question: %s\n", question);
	write(send_q,question,strlen(question)+1);
	close(send_q);

	// now wait for answer...
	int get_a = open(players[curr_player].pipe_name,O_RDONLY);
	if (get_a < 0){
	  delete_pipes();
	  perror("cannot open player pipe");
	  break;
	}

	char player_answer[500];
	// ok so we have to make it so that the player pipe writing side will send in a stdin input
	if(read(get_a, player_answer, sizeof(player_answer))>0){
	  player_answer[strcspn(player_answer, "\n")] = '\0'; // removes trailing newline

	  if (strcmp(player_answer,"end")==0){
		printf("Player ended the game.\n");
		break;
	  }
	  else if (strcmp(player_answer,answer)==0){
		printf("Correct! Point added.\n");
		players[curr_player].score+=1;
	  }
	  else {
		printf("Wrong! The right answer is: %s\n",answer);
	  }
	}
	close(get_a);
	// unlink(players[curr_player].pipe_name);

	curr_player = (curr_player+1)%num_players; // so it wraps
  }
  print_points();
  delete_pipes();
  return 0;
}

/* Called in main whenever the host should ask another question.
"q_num" refers to the question number to be asked. This function will go through the Q&A file
and ask the corresponding question. */

void find_question(char *topic, char *question, char *answer) {
    char topicbuff[20];
    snprintf(topicbuff, sizeof(topicbuff), "%s.txt", topic);

    FILE *readfile = fopen(topicbuff, "r");
    if (readfile == NULL) {
        perror("cannot open question file");
        return;
    }

    char line[1000];
    int *q_num = NULL;

    // q_num points to the correct # question
    if (strcmp(topic, "history") == 0) q_num = &histq_num;
    else if (strcmp(topic, "geography") == 0) q_num = &geoq_num;
    else if (strcmp(topic, "math") == 0) q_num = &mathq_num;
    else {
        fclose(readfile);
        return;
    }

    // is the current line on the right number?
    int curr_line = 0;
    while(fgets(line, sizeof(line), readfile)){
      if(curr_line==*q_num){
        char * linepointer = line;
	      char* q = strsep(&linepointer, ":");
	      char* a = strsep(&linepointer, "\n");
        strncpy(question,q,strlen(q));
        strncpy(answer,a,strlen(a));

        // increment to get to the next q the next time this is called
        (*q_num)++;

        fclose(readfile);
        return;
      }
      curr_line++;
    }
    fclose(readfile);
}
