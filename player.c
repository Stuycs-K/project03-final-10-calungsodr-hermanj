#include "player.h"

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
