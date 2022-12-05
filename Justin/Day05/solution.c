#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "simple_stack.h"

#define DEFAULT_BUFFER_SIZE 1024

bool GetNextLine(FILE **file_ptr, char **buffer){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    int idx = 0;
    bool isSuccess = false;
    (*buffer) = NULL;
    
    (*buffer) = calloc(0, DEFAULT_BUFFER_SIZE);
    if(NULL == (*buffer)){
        printf("[-] Could not allocate buffer\n");
        return false;
    }

    while(true){
        currentChar = fgetc((*file_ptr));
        if (stop == (char)currentChar || feof((*file_ptr)) ) {
            break;
        }
        (*buffer)[idx++] = (char)currentChar;
    }

    if (idx != 0){
        isSuccess = true;
    }

    return isSuccess;
}

void ProcessLinePart1(struct SIMPLE_STACK *stacks, char* buffer){
    int src, numItems, dst, item;
    sscanf(buffer, "move %d from %d to %d", &numItems, &src, &dst);

    for(int i=0; i < numItems; i++){
        item = SimpleStackPop(&stacks[src-1]);
        SimpleStackPush(&stacks[dst-1], item);
    }
}

void ProcessLinePart2(struct SIMPLE_STACK *stacks, char* buffer){
    int src, numItems, dst, item;
    struct SIMPLE_STACK tmp_stack = {0};
    sscanf(buffer, "move %d from %d to %d", &numItems, &src, &dst);

    for(int i=0; i < numItems; i++){
        item = SimpleStackPop(&stacks[src-1]);
        SimpleStackPush(&tmp_stack, item);
        
    }

    for(int i=0; i < numItems; i++){
        item = SimpleStackPop(&tmp_stack);
        SimpleStackPush(&stacks[dst-1], item);
    }

}

void PrintResults(struct SIMPLE_STACK *stacks){
    int item;

    for(int i=0; i < 9; i++){
        item = SimpleStackPop(&stacks[i]);
        printf("%c", (char)item);
    }

    printf("\n");
}

bool InitStacks(struct SIMPLE_STACK **stacks){
/*
    [Q] [J]                         [H]
    [G] [S] [Q]     [Z]             [P]
    [P] [F] [M]     [F]     [F]     [S]
    [R] [R] [P] [F] [V]     [D]     [L]
    [L] [W] [W] [D] [W] [S] [V]     [G]
    [C] [H] [H] [T] [D] [L] [M] [B] [B]
    [T] [Q] [B] [S] [L] [C] [B] [J] [N]
    [F] [N] [F] [V] [Q] [Z] [Z] [T] [Q]
    1   2   3   4   5   6   7   8   9 
*/

    /* Need to optimize later.... */
    (*stacks) = calloc(sizeof(struct SIMPLE_STACK), 9);
    if(NULL == (*stacks)){
        printf("[-] Could not allocate stacks!");
        return false;
    }

    // Init stack 1
    SimpleStackPush(&(*stacks)[0], (int)'F');
    SimpleStackPush(&(*stacks)[0], (int)'T');
    SimpleStackPush(&(*stacks)[0], (int)'C');
    SimpleStackPush(&(*stacks)[0], (int)'L');
    SimpleStackPush(&(*stacks)[0], (int)'R');
    SimpleStackPush(&(*stacks)[0], (int)'P');
    SimpleStackPush(&(*stacks)[0], (int)'G');
    SimpleStackPush(&(*stacks)[0], (int)'Q');

    // Init Stack 2
    SimpleStackPush(&(*stacks)[1], (int)'N');
    SimpleStackPush(&(*stacks)[1], (int)'Q');
    SimpleStackPush(&(*stacks)[1], (int)'H');
    SimpleStackPush(&(*stacks)[1], (int)'W');
    SimpleStackPush(&(*stacks)[1], (int)'R');
    SimpleStackPush(&(*stacks)[1], (int)'F');
    SimpleStackPush(&(*stacks)[1], (int)'S');
    SimpleStackPush(&(*stacks)[1], (int)'J');

    // Init Stack 3
    SimpleStackPush(&(*stacks)[2], (int)'F');
    SimpleStackPush(&(*stacks)[2], (int)'B');
    SimpleStackPush(&(*stacks)[2], (int)'H');
    SimpleStackPush(&(*stacks)[2], (int)'W');
    SimpleStackPush(&(*stacks)[2], (int)'P');
    SimpleStackPush(&(*stacks)[2], (int)'M');
    SimpleStackPush(&(*stacks)[2], (int)'Q');
    

    // Init Stack 4
    SimpleStackPush(&(*stacks)[3], (int)'V');
    SimpleStackPush(&(*stacks)[3], (int)'S');
    SimpleStackPush(&(*stacks)[3], (int)'T');
    SimpleStackPush(&(*stacks)[3], (int)'D');
    SimpleStackPush(&(*stacks)[3], (int)'F');

    // Init stack 5
    SimpleStackPush(&(*stacks)[4], (int)'Q');
    SimpleStackPush(&(*stacks)[4], (int)'L');
    SimpleStackPush(&(*stacks)[4], (int)'D');
    SimpleStackPush(&(*stacks)[4], (int)'W');
    SimpleStackPush(&(*stacks)[4], (int)'V');
    SimpleStackPush(&(*stacks)[4], (int)'F');
    SimpleStackPush(&(*stacks)[4], (int)'Z');

    // Init Stack 6
    SimpleStackPush(&(*stacks)[5], (int)'Z');
    SimpleStackPush(&(*stacks)[5], (int)'C');
    SimpleStackPush(&(*stacks)[5], (int)'L');
    SimpleStackPush(&(*stacks)[5], (int)'S');

    // Init stack 7
    SimpleStackPush(&(*stacks)[6], (int)'Z');
    SimpleStackPush(&(*stacks)[6], (int)'B');
    SimpleStackPush(&(*stacks)[6], (int)'M');
    SimpleStackPush(&(*stacks)[6], (int)'V');
    SimpleStackPush(&(*stacks)[6], (int)'D');
    SimpleStackPush(&(*stacks)[6], (int)'F');

    // Init stack 8
    SimpleStackPush(&(*stacks)[7], (int)'T');
    SimpleStackPush(&(*stacks)[7], (int)'J');
    SimpleStackPush(&(*stacks)[7], (int)'B');

    // Init stack 5
    SimpleStackPush(&(*stacks)[8], (int)'Q');
    SimpleStackPush(&(*stacks)[8], (int)'N');
    SimpleStackPush(&(*stacks)[8], (int)'B');
    SimpleStackPush(&(*stacks)[8], (int)'G');
    SimpleStackPush(&(*stacks)[8], (int)'L');
    SimpleStackPush(&(*stacks)[8], (int)'S');
    SimpleStackPush(&(*stacks)[8], (int)'P');
    SimpleStackPush(&(*stacks)[8], (int)'H');

    printf("[+] Stacks initialized\n");
    return true;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s <file_name>\n", argv[0]);
        return -1;
    }

    char *buffer;
    bool isSuccess = false;
    int total = 0;
    struct SIMPLE_STACK *stacks1, *stacks2;

    InitStacks(&stacks1);
    InitStacks(&stacks2);

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextLine(&fp, &buffer);

        if (!isSuccess){
            break;
        }

        ProcessLinePart1(stacks1, buffer);
        ProcessLinePart2(stacks2, buffer);
        free(buffer);
    }
    
    free(buffer);
    fclose(fp);

    printf("[+] part 1... ");
    PrintResults(stacks1);
    printf("[+] part 2... ");
    PrintResults(stacks1);
    
    return 0;
}
