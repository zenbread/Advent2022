#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 8192

bool GetNextLine(FILE **file_ptr, char **buffer, int* bufferSize){
    char stop = '\n';
    int currentChar = 1; /* What should the default value be? */
    int idx = 0;
    bool isSuccess = false;
    (*buffer) = NULL;
    (*bufferSize) = 0;
    
    (*buffer) = calloc(sizeof(char), DEFAULT_BUFFER_SIZE);
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
        (*bufferSize) = idx;
        isSuccess = true;
    }else{
        free( (*buffer) );
    }

    return isSuccess;
}

bool IsWindowValid(int charCounter[26]){

    for(int i = 0; i < 26; i++){
        if(charCounter[i] > 1){
            return false;
        }
    }

    return true;
}

int FindFirstMarker(char* buffer, int bufferSize, int windowSize){
    int ret = 0;
    int charCounter[26] = {0};

    for(int i = 0; i < windowSize; i++){
        charCounter[buffer[i]-'a'] += 1;
    }

    if(IsWindowValid(charCounter)){
        return windowSize;
    }

    for(int i = windowSize; i < (bufferSize-windowSize); i++){
        // Mark the next character as "seen"        
        charCounter[buffer[i]-'a'] += 1;

        // Unmark the previous character
        charCounter[buffer[i-windowSize]-'a'] -= 1;

        // Have we found the answer?
        if(IsWindowValid(charCounter)){
            ret =  i+1;
            break;
        }
    }
    return ret;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s <file_name>\n", argv[0]);
        return -1;
    }

    char *buffer;
    bool isSuccess = false;
    int p1Answer, p2Answer, bufferSize = 0;

    FILE* fp = fopen(argv[1], "r");
    if(NULL == fp){
        printf("[-] File with the name %s does not exist\n", argv[1]);
        return -1;
    }

    while(true){
        isSuccess = GetNextLine(&fp, &buffer, &bufferSize);

        if (!isSuccess){
            break;
        }

        p1Answer = FindFirstMarker(buffer, bufferSize, 4);
        p2Answer = FindFirstMarker(buffer, bufferSize, 14);
        free(buffer);
    }
    
    fclose(fp);

    printf("[+] Part1 Answer: %d\n", p1Answer);
    printf("[+] Part2 Answer: %d\n", p2Answer);
    return 0;
}