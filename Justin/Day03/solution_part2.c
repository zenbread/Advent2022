#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFULT_BUFFER_SIZE 2048

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

int UpdateTracker(int tracker[52], char* buffer, int bufferSize){
    int sackOffset = 0;
    bool alreadyUpdated[52] = {0};

    for (int i = 0; i < bufferSize; i++){
        sackOffset = ConverCharToOffset(buffer[i]);

        if(!alreadyUpdated[sackOffset]){
            alreadyUpdated[sackOffset] = true;
            tracker[sackOffset] += 1;

            if (tracker[sackOffset] == 3){
                return sackOffset + 1;
            }
        }
        
    }

    return -1;
}

int FindCommonType(char* buffer1, int  size1, 
                   char* buffer2, int  size2, 
                   char* buffer3, int  size3){
    int ret = 0;
    int tracker[52] = {0};

    UpdateTracker(tracker, buffer1, size1);
    UpdateTracker(tracker, buffer2, size2);
    ret = UpdateTracker(tracker, buffer3, size3);

    printf("[+] group score: %d\n", ret);
    return ret;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s <file_name>\n", argv[0]);
        return -1;
    }

    char *buffer1, *buffer2, *buffer3;
    int bufferSize1, bufferSize2, bufferSize3;
    int rucksack_size = 0;
    bool isSuccess = false;
    int total = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetLine(&fp, &buffer1, &bufferSize1);
        isSuccess |= GetLine(&fp, &buffer2, &bufferSize2);
        isSuccess |= GetLine(&fp, &buffer3, &bufferSize3);

        if (!isSuccess){
            break;
        }

        /* Keep track of the score */
        total += FindCommonType(buffer1, bufferSize1,
                                buffer2, bufferSize2,
                                buffer3, bufferSize3);
        free(buffer1);
        free(buffer2);
        free(buffer3);
    }
    
    fclose(fp);
    printf("[+] Answer: %d\n", total);
    
    return 0;
}