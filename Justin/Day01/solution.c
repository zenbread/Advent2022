#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_ELVES 3
#define DEFAULT_BUFFER_SIZE 1024

bool GetNextValue(FILE **file_ptr, int *result){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    char *buffer = NULL;
    int idx = 0;
    bool isSuccess = false;
    (*result) = 0;
    
    buffer = calloc(0, DEFAULT_BUFFER_SIZE);
    if(NULL == buffer){
        printf("[-] Could not allocate buffer\n");
        return false;
    }

    while(true){
        currentChar = fgetc((*file_ptr));
        if (stop == (char)currentChar || feof((*file_ptr)) ) {
            break;
        }
        buffer[idx++] = (char)currentChar;
    }

    if (idx != 0){
        (*result) = atoi(buffer);
        isSuccess = true;
    }

    free(buffer);
    return isSuccess;
}

bool GetNextElfCount(FILE **file_ptr, int *total_calories){
    bool isSuccess = true;
    int result = 0;
    (*total_calories) = 0;

    if( feof((*file_ptr)) ){
        printf("[!] Reached EOF\n");
        return false;
    }

    while(isSuccess){
        /* Considered unsuccessful if value is empty */
        isSuccess = GetNextValue(file_ptr, &result);
        (*total_calories) += result;
    }

    printf("[+] This elf has %d calories!\n", (*total_calories));
    return true;
}

int CheckIfMaximum(int **list, int newEntry){
    int current = newEntry;
    int tmp = 0;

    for (int i = 0; i < NUMBER_OF_ELVES; i++){

        if (current > (*list)[i]){
            tmp = (*list)[i];
            (*list)[i] = current;
            current = tmp;
        }

    }
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: calorie_count <file_name>\n");
        return -1;
    }

    int *maximums = NULL;
    int current = 0;
    bool isSuccess = false;

    maximums = calloc(0, sizeof(int)*NUMBER_OF_ELVES);
    if(NULL == maximums){
        printf("[-] Could not allocate data!");
        return -1;
    }

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextElfCount(&fp, &current);

        if (!isSuccess){
            break;
        }

        CheckIfMaximum((int**)&maximums, current);
    }

    /* print the solution */
    int total = 0;
    for (int i = 0; i < NUMBER_OF_ELVES; i++){
        printf("elf %d has %d calories\n", i+1, maximums[i]);
        total += maximums[i];
    }
    printf("[+] Answer: the elves with the most calories have the following total amount: %d\n", total);
    
    return 0;
}
