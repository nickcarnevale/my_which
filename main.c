#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int file_exists(char* path){
    return access(path, X_OK) == 0;
}

int main(int argc, char** argv) { // also known as: char* argv[] 
    char* path = getenv("PATH"); 
    char* pathCopy = strdup(path); 
    char* dirList[20]; 
    char* files[20]; 
    short numFiles = 0; 
    short numDir = 0; 
    short fileExistsCounter = 0;
    bool aFlag = false; 
    
    //split PATH into a list of Directories, stored in dirList 
    if(path != NULL){ 
        char* dir = strtok(path, ":"); 
        while(dir != NULL && numDir < 20){ 
            dirList[numDir] = dir; 
            numDir++; 
            dir = strtok(NULL, ":"); 
        }
    }

    //Get -a Flag and fileNames
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(strcmp(argv[i],"-a") == 0){
                aFlag = true;
            }else{
                printf("Invalid Option.");
                return 2;
            }
        }
        else{
            files[numFiles] = argv[i];
            numFiles++;
        }
    }
    
    //loop through eacch file and check if its exists and is executable
    for(int i = 0; i < numFiles; i++){
        for(int j = 0; j < numDir; j++){
            char* path = malloc(strlen(dirList[j]) + strlen(files[i]) + 2);
            sprintf(path, "%s/%s", dirList[j],files[i]);
            if(file_exists(path)){
                fileExistsCounter++;
                printf("%s\n", path);
                if(!aFlag){
                    break;
                }
            }
            free(path);
        }
    }
    if(fileExistsCounter != numFiles){
        return 1;
    }else{
        return 0;
    }
}