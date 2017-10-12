#include "makeArgs.h"

void clean(int argc, char **argv)
{
    int x;
    for(x = 0; x < argc; x++){
        free(argv[x]);
        argv[x] = NULL;
    }
    free(argv);
    argv = NULL;
}// end clean
void printargs(int argc, char **argv)
{
	int x;
    for(x = 0; x < argc; x++){
		printf("%s\n", argv[x]);
    }
}// end printargs
int makeargs(char *s, char *** argv, char * tokenToParse)
{
    char copy[MAX];
    char *tempPtr;
    char *tempPtr2;
    char *token;
    
    strcpy(copy, s);
    
    int count = 0;
    
    token = strtok_r(s, tokenToParse, &tempPtr);
    
    while(token != NULL){
        count++;
        token = strtok_r(NULL, tokenToParse, &tempPtr);
    }
    
    if(count == 0){
        return -1;
    }
    
    (*argv) = (char **)calloc(count+1, sizeof(char *));
    
    token = strtok_r(copy, tokenToParse, &tempPtr2);
    strip(token);
    
    (*argv)[0] = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy((*argv)[0], token);
    
    int x;
    for(x = 1; x < count; x++){
        token = strtok_r(NULL, tokenToParse, &tempPtr2);
        strip(token);
        (*argv)[x] = (char *)calloc(strlen(token)+1, sizeof(char));
        strcpy((* argv)[x], token);
    }
    
    return count;
}// end makeArgs
