#include "player.h"

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

	//prompts the user for the answer
	//connecting to WKP

	int from_host;

	// well known pipe sends the question
	from_host = open(WKP, O_WRONLY, 0666);
	if (from_host < 0) {
		printf("here line 93\n");
		err();
	}

	//making private pipe

	int pid = getpid();
	int * pidp = &pid;
	char name[10]; 
	snprintf(name, 10, "%d", pid);
	if (mkfifo(name, 0666) < 0 ){
		printf("here line 103\n");
		err();
	}

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

}

// do we need this actually?