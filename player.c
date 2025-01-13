#include "player.h"

// for pipe, look for sigpipe
// for pipe, look for sigpipe
static void sighandler(int signo){
    if (signo == SIGINT){
        printf("\nDisconnected.\n");
        exit(0);
    }
    if (signo == SIGPIPE){
        printf("\nDisconnected.\n");
        exit(0);
    }
}

// singhandler

/*

idk what to add in the beginning... how will it know which
player_pipe it is? ex. "player1" "player2"

// if 'end game' typed, break
*/

/*
	player pipes should be WKPs. name them "player1", "player2", etc...ACCESSX_MAX_TABLESIZE

*/

int main() {

    signal(SIGPIPE, sighandler);
    signal(SIGINT, sighandler);

	//prompts the user for the answer
	//connecting to WKP
	char player_pipe[500];
	char buffer[300];

	// send PID to WKP
	int send_pid = open(WKP, O_WRONLY, 0666);
	if (send_pid < 0) {
		perror("error opening wkp");
	}

	//making private pipe
	int pid = getpid();
	sprintf(player_pipe, "player%d", pid); // do we still need this
	sprintf(buffer, "%d", pid);

	write(send_pid, buffer, strlen(buffer)+1);

	printf("Player has joined the game!\n");

	mkfifo(player_pipe, 0666);

	int open_pp = open(player_pipe, O_RDONLY);
	if (open_pp < 0){
		perror("cant open player pipe");
	}

	// wait for questions!
	while (1){
		if(read(open_pp,buffer,300)>0){
			printf("Here's your question...%s\n", buffer);

			printf("Your answer: ");
			fgets(buffer, sizeof(300), stdin);

			// senf user answer back to host
			// handle it, make it all lowercase
			int send_a = open(WKP, O_WRONLY);
			write(send_a,buffer,strlen(buffer)+1);
			close(send_a);
		}
	}
	unlink(player_pipe);
}

// add exiting signals