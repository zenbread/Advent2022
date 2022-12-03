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
    GAME_OUTCOME_P2_WINNER,
    GAME_OUTCOME_UNKNOWN
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
    switch(action){
        case 'A':
            return GAME_STATE_ROCK;
        case 'B':
            return GAME_STATE_PAPER;
        case 'C':
            return GAME_STATE_SCISSORS;
        default:
            return GAME_STATE_UNKNOWN;
    }
}

GAME_OUTCOME GetOutcome(char outcome){
    switch(outcome){
        case 'X':
            return GAME_OUTCOME_P1_WINNER;
        case 'Y':
            return GAME_OUTCOME_TIE;
        case 'Z':
            return GAME_OUTCOME_P2_WINNER;
        default:
            return GAME_OUTCOME_UNKNOWN;
    }
}

GAME_STATE DetermineResponse(GAME_STATE p1_action, GAME_OUTCOME outcome){
    GAME_STATE p2_action = GAME_STATE_UNKNOWN;

    switch(outcome){
        case GAME_OUTCOME_P1_WINNER:
            p2_action = (int)p1_action-1 < (int)GAME_STATE_ROCK ? GAME_STATE_SCISSORS : p1_action-1;
            break;
        case GAME_OUTCOME_P2_WINNER:
            p2_action = (int)(p1_action+1) > (int)GAME_STATE_SCISSORS ? GAME_STATE_ROCK : p1_action+1;
            break;
        case GAME_OUTCOME_TIE:
            p2_action = p1_action;
            break;
        default:
            break;
    }

    return p2_action;
}

int CalculateScore(char action, char outcome_char){
    GAME_STATE player1, player2;
    GAME_OUTCOME outcome;
    int points = 0;

    player1 = GetState(action);
    outcome = GetOutcome(outcome_char);

    if(GAME_STATE_UNKNOWN == player1 || 
       GAME_OUTCOME_UNKNOWN == outcome){
        printf("[!] received unknown character!\n");
        return 0;
    }

    player2 = DetermineResponse(player1, outcome);

    if(GAME_STATE_UNKNOWN == player2){
        printf("[!] received unknown character for player 2!\n");
        return 0;
    }

    /* calculate points for choosing shape */
    points += player2 + 1;
    
    /* Calculate points for the outcome of the round */
    points += outcome*3;

    printf("[+] This round generated %d points...\n", points);
    return points;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: rock_paper_scissors <file_name>\n");
        return -1;
    }

    char oppenent_action, outcome;
    bool isSuccess = false;
    int total = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextPair(&fp, &oppenent_action, &outcome);

        if (!isSuccess){
            break;
        }

        /* Keep track of the score */
        total += CalculateScore(oppenent_action, outcome);
    }
    
    fclose(fp);
    printf("[+] Answer: %d\n", total);
    
    return 0;
}
