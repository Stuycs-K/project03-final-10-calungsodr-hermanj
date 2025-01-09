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

close

// if 'end game' typed, break
*/