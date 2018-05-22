#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char * argv[]){

    DIR * dp;
    
    if(argc >= 2){
        char gamesDir[512];
        sprintf(gamesDir, "%s/Games", argv[1]);
        dp = opendir(gamesDir);
    }else{
        dp = opendir("./");
    }

    
    if(dp == NULL){
        puts("Failed to open dir");
        return EXIT_FAILURE;
    }


    FILE * jsonDB;


    {
        char jsonName[512];
        sprintf(jsonName, "%s/GamesInfo.json", argv[1]);

        jsonDB = fopen(jsonName, "w");
        if(jsonDB == NULL){
            puts("Failed to open DB file");
            return EXIT_FAILURE;
        }
    }


    fputc('[', jsonDB);


    struct dirent * ep;
    FILE * jsonFile;
    char jsonFileName[1024];

    bool isAlreadyWritten = false;
    while(ep = readdir(dp)){
        if(!strcmp(ep -> d_name, "."))continue;
        if(!strcmp(ep -> d_name, ".."))continue;
        if(ep -> d_type != DT_DIR)continue;
        printf("inode %lu\n", ep -> d_ino);
        sprintf(jsonFileName, "%s/Games/%s/.signature.json", argv[1], ep -> d_name);
        jsonFile = fopen(jsonFileName, "r");

        if(jsonFile == NULL){
            fprintf(stderr, "Failed to open %s\n", jsonFileName);
            fprintf(stderr, "ERRNO is %d\n", errno);
            continue;
        }

        char buffer[1024] = {};
        const size_t readBytes = fread(buffer, 1, 1024, jsonFile);
        const size_t end = strlen(buffer);
        buffer[end - 1] = '\0';

        if(isAlreadyWritten)fputc(',', jsonDB);
        fprintf(jsonDB, "%s", buffer + 1);
        fclose(jsonFile);
        isAlreadyWritten = true;
    }

    fputc(']', jsonDB);

    closedir(dp);

    return EXIT_SUCCESS;
}
