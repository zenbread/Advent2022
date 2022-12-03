#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFULT_BUFFER_SIZE 2048

struct RUCKSACK{
    int compartmentSize;
    bool compartment1[52];
    bool compartment2[52];
};

bool GetLine(FILE **file_ptr, char **buffer, int *bufferSize){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    int idx = 0;
    (*buffer) = NULL;
    (*bufferSize) = 0;
    
    (*buffer) = calloc(sizeof(char), DEFULT_BUFFER_SIZE);
    if(NULL == (*buffer)){
        printf("[-] Could not allocate buffer\n");
        return false;
    }

    while(true){
        currentChar = fgetc((*file_ptr));

        if (stop == (char)currentChar || feof((*file_ptr)) ) {
            /* exit condition */
            break;
        }

        (*buffer)[idx++] = (char)currentChar;
    }

    (*bufferSize) = idx;

    return (idx != 0);
}

int ConverCharToOffset(char offset){

    if(offset >= 'a' && offset <= 'z'){
        return (int)(offset - 'a');
    } else if(offset >= 'A' && offset <= 'Z'){
        return (int)(offset - 'A') + 26;
    }

    return -1;
}

int CalculateScore(char* buffer, int  size){
    struct RUCKSACK sack = {0};
    bool foundSharedItem = false;
    int sackOffset = 0;

    sack.compartmentSize = (size)/2;

    /* Place the first half contents in rucksack 1 */
    for (int i = 0; i < sack.compartmentSize; i++){
        sackOffset = ConverCharToOffset(buffer[i]);
        sack.compartment1[sackOffset] = true;
    }

    /* Search for the shared item */
    for (int i = 0; i < sack.compartmentSize; i++){
        sackOffset = ConverCharToOffset(buffer[sack.compartmentSize + i]);

        if (sack.compartment1[sackOffset] == true){
            printf("[+] score: %d\n", sackOffset + 1);
            return sackOffset + 1;
        }
    }

    printf("[!] Could not find score\n");
    return 0;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s <file_name>\n", argv[0]);
        return -1;
    }

    char *buffer = NULL;
    int bufferSize = 0;
    int rucksack_size = 0;
    bool isSuccess = false;
    int total = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetLine(&fp, &buffer, &bufferSize);

        if (!isSuccess){
            break;
        }

        /* Keep track of the score */
        total += CalculateScore(buffer, bufferSize);
        free(buffer);
    }
    
    fclose(fp);
    printf("[+] Answer: %d\n", total);
    
    return 0;
}