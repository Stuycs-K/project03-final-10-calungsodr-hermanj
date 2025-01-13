#include "player.h"
#include "host.h"

//before merge
/*
int main() {
	//prompts the user for the answer
	
	//making private pipe
	int pid;
	char name[10];
	pid = getpid();
	snprintf(name, 10, "player%d", pid);
	if (mkfifo(name, 0666) < 0 ){
		printf("private pipe couldn't be created\n");
		err();
	}
	
	//connecting to WKP
	int from_host;
	from_host = open(WKP, O_RDONLY, 0666);
	if (from_host < 0) {
		printf("mario couldn't be opened\n");
		err();
	}
	
	//wrong code
	//int *playernum;
	//read(from_host, playernum, sizeof(int));
	
	
	char * answer;
	char useranswer[20];
	printf("Your answer: ");
	fgets(useranswer, sizeof(useranswer), stdin);
	
	//get rid of \n
	for (int i = 0; i < sizeof(useranswer); i++) {
		if (useranswer[i] == '\n') {
			useranswer[i] = '\0';
			i = sizeof(useranswer);
		}
	}
	printf("useranswer: %s\n", useranswer);
	printf("correct answer: %s\n", answer);
	
	if (strcmp(answer, useranswer) == 0) {
		printf("YOU HAVE THE RIGHT ANSWER\n");
	}
	else {
		printf("INCORRECT, TRY AGAIN NEXT TIME\n");
	}
	return 0;
*/
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

	mkfifo(player_pipe, 0666);
	
	write(send_pid, player_pipe, strlen(player_pipe)+1);

	printf("Player has joined the game!\n");

	int open_pp = open(player_pipe, O_RDONLY);
	if (open_pp < 0){
		perror("cant open player pipe");
	}

	// wait for questions!
	while (1){
		if(read(open_pp,buffer,300)>0){ //why does nothing get sent????
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
