/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char dataDir[256] = "./data";

void setupPath(){
    #ifdef DATADIR
    strcpy(dataDir, DATADIR);
    strcat(dataDir, "/data");
    #endif // DATADIR
    char *envPath = getenv("BLACKPYRE_DATA");
    if(envPath){
        strcat(dataDir, envPath);
    }else{
        #ifdef macintosh
        strcpy(dataDir, ":data");
        #else
        strcpy(dataDir, "./data");
        #endif // macintosh
    }
    fprintf(stderr, "Using %s for data path\n", dataDir);
}

const char* dataPath(const char* path){
    static char buffer[256];
    if((strlen(dataDir)+strlen(path)) < 254){
        sprintf(buffer, "%s/%s", dataDir, path); 
    }else{
        fprintf(stderr, "Filename too long\n");
		fprintf(stderr, "dataDir  = \"%s\"\n", dataDir);
		fprintf(stderr, "path = \"%s\"\n", path);
        return "badFilename";
    }

    // normalize path for OSX
    #ifdef macintosh
    char *bp = buffer;
    while(*bp){
        if(*bp == "/"){
            *bp = ":";
        }
        bp++;
    }
    #endif

    return buffer;
}
