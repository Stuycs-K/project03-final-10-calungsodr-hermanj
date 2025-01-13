#include "host.h"

#define MAX_PLAYERS 3

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
/*
1/11 update to implement

1. player sends the host its PID (which will be the pipe name)
2. host adds each PID to an array that stores the pipe names
3. the host loops through this array of pipes to know which pipe to send a question to
*/


int err(){
  printf("errno %d\n", errno);
  printf("%s\n",strerror(errno));
  exit(1);
}

static int histq_num = 0;
static int geoq_num = 0;
static int mathq_num = 0;

struct player_struct {
  int pid;
  char pipe_name[20];
  int score;
};

struct player_struct players[MAX_PLAYERS]; //array of players!!!
int num_players = 0;

// is this correct????????
struct player_struct create_player(char* player_num){
// use heap memory, so calloc or malloc
  struct player_struct p;
  snprintf(p.pipe_name,20,"%s",player_num); // use player index for pipe name
  p.score = 0;
  return p;
}

void delete_pipes(){
  remove(WKP);
  for (int i = 0; i<num_players; i++){
	  printf("pipename: %s\n", players[i].pipe_name);
    remove(players[i].pipe_name);
  }
}

// for pipe, look for sigpipe
// SIGNAL HANDLING
static void sighandler(int signo){
    if (signo == SIGINT){
      printf("\nDisconnected, game over\n");
      delete_pipes();
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
    if (mkfifo(WKP, 0644)==-1) {
      perror("error in making WKP");
    }

    printf("Server setup finished, waiting for %d players to join! (Tip: type './player' in a different terminal window.)\n\n", MAX_PLAYERS);

    // open wkp.[blocks]
    int from_client = open(WKP, O_RDONLY);
    if (from_client==-1) err();

    char pid[20];
    // for every player ! need the max to begin
    while (num_players<MAX_PLAYERS){
      // if there's something to read!
      //int player_pid = atoi(pid); // convert pid to integer, looked this up
      if (read(from_client,pid,sizeof(pid))>0){
        players[num_players] = create_player(pid);

        if(mkfifo(players[num_players].pipe_name, 0644)==-1){
          perror("cannot create player pipe");
        }
        printf("Player %d joined!\n", num_players+1);
        num_players++;
      }
    }

    close(from_client);
    unlink(WKP);

    printf("welcome, instructions here...\n");
    printf("Please choose a topic (History, Geography, Math): "); //1 is a place holder

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

    char question[500];
    char answer[500];
    int curr_player = 0;
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


      // send question to player through pipe!
      int send_q = open(players[curr_player].pipe_name,O_WRONLY);
      if (send_q == -1){
        perror("cannot open player pipe");
        break;
      }
      write(send_q,question,strlen(question+1));
      close(send_q);

      // no wait for answer...
      int get_a = open(players[curr_player].pipe_name,O_RDONLY);
        if (get_a == -1){
        perror("cannot open player pipe");
        break;
      }

      char player_answer[500];
      // ok so we have to make it so that the player pipe writing side will send in a stdin input
      if(read(get_a,player_answer,sizeof(player_answer))>0){
        // remove trailing newline here i forgot how
        if (strcmp(player_answer,"end game")==0){
          printf("Player ended the game.\n");
          break; // point function
        }
        if (strcmp(player_answer,answer)==0){
          printf("Correct! Point added.");
          players[curr_player].score+=1;
          // handle lowercase, maybe in the part that actually gets it
        }
        else printf("Wrong! The right answer is: %s",answer);
      }
      close(get_a);

      curr_player = (curr_player+1)%num_players; // so it wraps
    }

    // deal with final scores... print from array.... function
    for (int i = 0; i<num_players; i++){
      printf("Player %d: %d points\n", i+1, players[i].score);
    }

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
  strncpy(question,q,strlen(q));
	char* a = strsep(&linepointer, "\n");
  strncpy(question,a,strlen(a));
	printf("question: %s\n", line);

  // should also deal with if tehre's nothing left

  fclose(readfile);

  // close file
}

