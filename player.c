#include "player.h"

// singhandler

/*

idk what to add in the beginning... how will it know which
player_pipe it is? ex. "player1" "player2"

// open to write into
int open_pp = open(player_pipe, O_WRONLY);
if(pp==-1) err();

char answer[500];
printf("answer here, or 'end game'");
fgets(answer,sizeof(answer),stdin);
// remove training new line

int pp_write = write(open_pp, answer, strlen(answer)+1)==-1){
    err();
    close(open_pp);
    exit(1);
}

// TALK ABOUT THIS TOMORROW

// if 'end game' typed, break
*/
void yay() {
	//prompts the user for the answer
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
}
// do we need this actually?
