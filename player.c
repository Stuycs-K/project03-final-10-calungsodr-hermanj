#include "player.h"
#include "host.h"

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
}
// do we need this actually?
