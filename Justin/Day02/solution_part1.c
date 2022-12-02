#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
    GAME_STATE_ROCK, 
    GAME_STATE_PAPER, 
    GAME_STATE_SCISSORS,
    GAME_STATE_UNKNOWN
} GAME_STATE;

typedef enum{
    GAME_OUTCOME_P1_WINNER,
    GAME_OUTCOME_TIE,
    GAME_OUTCOME_P2_WINNER
} GAME_OUTCOME;

bool GetNextPair(FILE **file_ptr, char *opponents_action, char *response){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    char *buffer = NULL;
    int idx = 0;
    bool isSuccess = false;
    (*opponents_action) = ' ';
    (*response) = ' ';
    
    buffer = calloc(0, sizeof(char)*2);
    if(NULL == buffer){
        printf("[-] Could not allocate buffer\n");
        return false;
    }

    while(true){
        currentChar = fgetc((*file_ptr));

        if (stop == (char)currentChar || feof((*file_ptr)) ) {
            /* exit condition */
            break;
        }
        if (currentChar == ' '){
            /* ignore */
            continue;
        }

        buffer[idx++] = (char)currentChar;
    }

    if (idx != 0){
        /* success */
        (*opponents_action) = buffer[0];
        (*response) = buffer[1];
        isSuccess = true;
    }

    free(buffer);
    return isSuccess;
}

GAME_STATE GetState(char action){
    if ('X' == action || 'A' == action) {
        return GAME_STATE_ROCK;
    }

    if ('Y' == action || 'B' == action) {
        return GAME_STATE_PAPER;
    }

    if ('Z' == action || 'C' == action) {
        return GAME_STATE_SCISSORS;
    }

    return GAME_STATE_UNKNOWN;
}

GAME_OUTCOME DetermineOutcome(GAME_STATE p1, GAME_STATE p2){
    if(p1 == p2){
        return GAME_OUTCOME_TIE;
    }
    else if( (p1 == GAME_STATE_ROCK && p2 == GAME_STATE_SCISSORS) ||
        (p1 == GAME_STATE_PAPER && p2 == GAME_STATE_ROCK) ||
        (p1 == GAME_STATE_SCISSORS && p2 == GAME_STATE_PAPER) ){
        return GAME_OUTCOME_P1_WINNER;
    }

    /* Default Answer */
    return GAME_OUTCOME_P2_WINNER;
}

int CalculateScore(char action, char response){
    GAME_STATE player1, player2;
    GAME_OUTCOME outcome;
    int points = 0;

    /* player2 is "yourself" */
    player1 = GetState(action);
    player2 = GetState(response);

    if(GAME_STATE_UNKNOWN == player1 || 
       GAME_STATE_UNKNOWN == player2){
        printf("[!] received unknown character!\n");
        return 0;
    }

    /* calculate points for choosing shape */
    points += player2 + 1;
    
    /* Calculate points for the outcome of the round */
    points += DetermineOutcome(player1, player2)*3;

    printf("[+] This round generated %d points...\n", points);
    return points;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: rock_paper_scissors <file_name>\n");
        return -1;
    }

    char oppenent_action, response;
    bool isSuccess = false;
    int total = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextPair(&fp, &oppenent_action, &response);

        if (!isSuccess){
            break;
        }

        /* Keep track of the score */
        total += CalculateScore(oppenent_action, response);
    }
    
    printf("[+] Answer: %d\n", total);
    
    return 0;
}
