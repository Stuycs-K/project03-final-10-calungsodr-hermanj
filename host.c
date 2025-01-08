#include "host.h"

//  REMINDER FOR LATER THAT WE NEED TO WRITE THE README

/*

GAME HOST (main) should:
1. Allow multiple players to join the game. (fork process) do we need server?
2. Print an introduction and instructions for the players.
3. Assign player numbers. First to join is player one, second is player 2, and so on...
4. Print out a list of topics (ex. history, science, math) for player 1 to choose from. 
5. After selection, the host will access the corresponding topic's Q&A file, read it as
intended to place the current question and answer into shared memory.
6. Allow the players to take turns to enter in answers (with semaphores) until somebody's
response matches the current stored answer. Add one point to that player, then move on
to the next question.
7. Keep asking questions until a user types "end game" or the Q&A file ends.

*/

// handles flow of the game, forking(?)
int main(){
    // a bunch of stuff should go here (????) with forking and perhaps a server, we should figure that out
    printf("Player %d, here's your next question: ", 1);
    ask_question(1); // 1 is a placeholder
	find_question("history");
	return 0;
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

char* find_question(char * topic) {
	int readfile;
	char topicbuff[20];
	snprintf(topicbuff, 20, "%s.txt", topic); //adds .txt to the topic
	printf("%s\n", topicbuff);
	readfile = open(topicbuff, , O_RDONLY, 0);
	if (readfile == -1) {
		err();
	}
	return topic;
}

