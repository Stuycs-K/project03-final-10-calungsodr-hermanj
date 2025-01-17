#include "player.h"
#include "host.h"

// singhandler
// for pipe, look for sigpipe
static void sighandler(int signo){
	if (signo == SIGINT || signo == SIGPIPE){
		printf("\nPlayer disconnected.\n");

		// unlink itself
		char player_pipe[100];
		int pid=getpid();
		sprintf(player_pipe,"player%d",pid);
		unlink(player_pipe);

		exit(0);
	}
}


// if 'end game' typed, break

int main() {
    signal(SIGPIPE, sighandler);
    signal(SIGINT, sighandler);

	//prompts the user for the answer
	//connecting to WKP
	char *player_pipe=malloc(100*sizeof(char));
	if(player_pipe==NULL) perror("malloc for player_pipe failed");
	char buffer[500];

	// send PID to WKP
	int send_pid = open(WKP, O_WRONLY);
	if (send_pid < 0) {
		perror("error opening wkp");
		exit(1);
	}

	//making private pipe
	int pid = getpid();
	sprintf(player_pipe, "player%d", pid);
	mkfifo(player_pipe, 0666); // err

	// send pipe name/pid to host
	sprintf(buffer, "%d", pid);
	write(send_pid, player_pipe, strlen(player_pipe)+1);

	printf("Player has joined the game! Waiting...\n");
		
	char end_buff[100];
	// wait for questions!
	while (1){
		//read(game_end, end_buff, sizeof(end_buff));
		int open_pp = open(player_pipe, O_RDONLY);
		if (open_pp < 0){
			perror("cant open player pipe");
			unlink(player_pipe);
			exit(1);
		}

		// read from pp
		read(open_pp, end_buff, sizeof(end_buff));
		if (strcmp(end_buff, "end") == 0) {
			close(open_pp);
			break;
		}
		//open private pipe to read question and answer

		printf("\n[TO END GAME, TYPE 'end'.]\n\nHere's your question...: %s\n", end_buff);
					
		char q_buff[300];
		char a_buff[300];
		char correct_a[300];

		memset(correct_a, 0, sizeof(correct_a));
		memset(q_buff, 0, sizeof(q_buff)); // clear before start
		memset(a_buff, 0, sizeof(a_buff));
		
		read(open_pp,q_buff,sizeof(q_buff)); //get question from host

		read(open_pp, correct_a, sizeof(correct_a)); //get correct answer from host
		close(open_pp);
		
		printf("Your answer: ");
		fgets(a_buff, sizeof(a_buff), stdin);
		a_buff[strcspn(a_buff, "\n")] = '\0';

		int send_a = open(player_pipe, O_WRONLY);
		write(send_a,a_buff,strlen(a_buff)+1);
		close(send_a);
		printf("waiting for turn\n");
	}
	
	printf("GAME OVER\n");
	unlink(player_pipe);
	remove(player_pipe);
	free(player_pipe);
	exit(0);
}

// add exiting signals
