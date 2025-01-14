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
		char buffer[500];

	// send PID to WKP
	int send_pid = open(WKP, O_WRONLY);
	if (send_pid < 0) {
		perror("error opening wkp");
	}

	//making private pipe
	int pid = getpid();
	sprintf(player_pipe, "player%d", pid); 
	sprintf(buffer, "%d", pid);

	mkfifo(player_pipe, 0666); // err
	
	write(send_pid, player_pipe, strlen(player_pipe)+1);

	printf("Player has joined the game!\n");


	// wait for questions!
	while (1){
			//open private pipe to read question and answer
			int open_pp = open(player_pipe, O_RDONLY);
			if (open_pp < 0){
				perror("cant open player pipe");
			}
			
			char q_buff[300];
			char a_buff[300];
			char correct_a[300];
			memset(correct_a, 0, sizeof(correct_a));
			memset(q_buff, 0, sizeof(q_buff)); // looked up, clear before start
			memset(a_buff, 0, sizeof(a_buff));
			read(open_pp,q_buff,sizeof(q_buff)); //get question from host
			//printf("sample question: %s\n", q_buff);
			read(open_pp, correct_a, sizeof(correct_a)); //get correct answer from host
			close(open_pp);
			//printf("sample answer: %s\n", correct_a);
			printf("Here's your question...%s\n", q_buff);

			printf("Your answer: ");
			fgets(a_buff, sizeof(300), stdin);
			a_buff[strcspn(a_buff, "\n")] = '\0';

			// checks if its correct or not
			/*if (strcmp(a_buff, correct_a) == 0) {
					printf("Correct! Point added.\n");
			}
			else {
					printf("Wrong! The right answer is: %s\n",correct_a);
			}*/
			//open private pipe to send answer
			int send_a = open(player_pipe, O_WRONLY);
			write(send_a,a_buff,strlen(a_buff)+1);
			close(send_a);
			printf("waiting for turn\n");
	}
	unlink(player_pipe);
	remove(player_pipe);
	exit(0);
}

// add exiting signals
