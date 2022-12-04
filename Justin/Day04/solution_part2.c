#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 1024

 bool ConvertToRange(int start, int finish, uint64_t** ret){

    (*ret) = calloc(sizeof(uint64_t), 2);
    if(NULL == (*ret) ){
        printf("[-] Could not allocate data");
        return false;
    }

    printf("Range: %d - %d\n", start, finish);

    for(int i = start-1; i <= finish-1; i++){
        if(i <64){
            (*ret)[0] |= (1ULL<<i);
        }
        else{
            (*ret)[1] |= (1ULL<<i);
        }
    }

    return true;
}

bool GetNextPair(FILE **file_ptr, uint64_t **section1, uint64_t **section2){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    char *buffer = NULL;
    int idx = 0;
    bool isSuccess = false;
    int start = -1, finish = -1;

    (*section1) = 0;
    (*section2) = 0;
    
    buffer = calloc(sizeof(char), DEFAULT_BUFFER_SIZE);
    if(NULL == buffer){
        printf("[-] Could not allocate buffer\n");
        return false;
    }

    while(true){
        currentChar = fgetc((*file_ptr));

        if (feof((*file_ptr)) ) {
            /* exit condition */
            break;
        }

        if (currentChar == ',' || stop == (char)currentChar){
            finish = atoi(buffer);

            /* assign to output*/
            if(0 == (*section1)){
                ConvertToRange(start, finish, section1);
            }else{
                ConvertToRange(start, finish, section2);
            }

            /* reset buffer */
            memset(buffer, 0, DEFAULT_BUFFER_SIZE);
            idx = 0;

            if(stop == (char)currentChar){
                isSuccess = true;
                goto end;
            }

            continue;
        }
        if(currentChar == '-'){
            start = atoi(buffer);

            /* reset buffer */
            memset(buffer, 0, DEFAULT_BUFFER_SIZE);
            idx = 0;
            continue;
        }

        buffer[idx++] = (char)currentChar;
    }

end:
    free(buffer);
    return isSuccess;
}

bool DoSectionsOverlap(uint64_t **section1, uint64_t **section2){
    bool isOverlapped = false;

    for(int i = 0; i < 128; i++){
        if(i < 64){
            isOverlapped = ((*section1)[0] & (1ULL << i)) && ((*section2)[0] & (1ULL << i));
        }else{
            isOverlapped = ((*section1)[1] & (1ULL << (i-64))) && ((*section2)[1] & (1ULL << (i-64)));
        }

        if (isOverlapped){
            printf("There's an overlap! %d\n\n", i);
            return true;
        }
    }

    printf("\n");
    return false;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: rock_paper_scissors <file_name>\n");
        return -1;
    }

    uint64_t *section1, *section2;
    bool isSuccess = false;
    int total = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextPair(&fp, &section1, &section2);

        if (!isSuccess){
            break;
        }

        /* Keep track of the score */
        total += DoSectionsOverlap(&section1, &section2);
    }
    
    fclose(fp);
    printf("[+] Answer: %d\n", total);
    
    return 0;
}
