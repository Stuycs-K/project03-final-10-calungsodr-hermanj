#include "player.h"
#include "host.h"

// singhandler
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


// if 'end game' typed, break

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

	mkfifo(player_pipe, 0666);
	
	write(send_pid, player_pipe, strlen(player_pipe)+1);

	printf("Player has joined the game!\n");

	int open_pp = open(player_pipe, O_RDONLY);
	if (open_pp < 0){
		perror("cant open player pipe");
	}

	// wait for questions!
	while (1){
		memset(buffer, 0, sizeof(buffer)); // looked up, clear before start
		if(read(open_pp,buffer,300)>0){
			printf("Here's your question...%s\n", buffer);

			printf("Your answer: ");
			memset(buffer, 0, sizeof(buffer));
			fgets(buffer, sizeof(300), stdin);
			buffer[strcspn(buffer, "\n")] = '\0';


			// send user answer back to host
			// handle it, make it all lowercase
			int send_a = open(player_pipe, O_WRONLY);
			write(send_a,buffer,strlen(buffer)+1);
			close(send_a);
		}
	}
	unlink(player_pipe);
	remove(player_pipe);
	exit(0);
}

// add exiting signals
