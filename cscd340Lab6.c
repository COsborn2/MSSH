//
// Created by Cameron Osborn on 10/10/17.
//

#include <ctype.h>
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/linkedList.h"
#include "./alias/alias.h"
#include "./history/history.h"

int doesContain(char * toParse, char token);
int startsWith(const char *a, const char *b);
void makeLowerCase(char * toParse);

//main from Lab5
int main()
{
    LinkedList * theAlias;
    LinkedList * theHistory;
    int historyFileCount;
    int historyViewSize;

    int argc, pipeCount;
    char **argv = NULL, s[MAX];
    int preCount = 0, postCount = 0;
    char ** prePipe = NULL, ** postPipe = NULL;

    FILE * fin = fopen(".msshrc", "r");
    if(fin == NULL){
        //create .mmshrc
    }else{
        //read from .msshrc
    }
    //.mssh_history

    printf("command?: ");
    fgets(s, MAX, stdin);
    strip(s);

    while(strcmp(s, "exit") != 0)
    {
        if(startsWith(s, "path")) {

        }else if(startsWith(s, "alias")){   //alias command
            //
        }else if(startsWith(s, "cd")){ //change directory command
            //
        }else if(doesContain()) { //contains pipe
            if (doesContain()) { //contains redirect FROM

            } else if (doesContain()) {    //contains redirect TO

            } else {
                prePipe = parsePrePipe(s, &preCount);
                postPipe = parsePostPipe(s, &postCount);
                pipeIt(prePipe, postPipe);
                clean(preCount, prePipe);
                clean(postCount, postPipe);
            }
        }else if(doesContain()){ //contains redirect FROM & NO Pipe
            //
        }else if(doesContain()){ //contains redirect TO & NO Pipe
            //
        }else {
            //parse and replace aliases with command

            argc = makeargs(s, &argv, " ");
            if(argc != -1)
                forkIt(argv);

            clean(argc, argv);
            argv = NULL;
        }

        printf("command?: ");
        fgets(s, MAX, stdin);
        strip(s);

    }// end while

    return 0;

}// end main
int doesContain(char * toParse, char token){
    //printf("In doesContain\n");
    //printf("Token: %c\n", token);
    //printf("toParse: %s\n", toParse);
    int i;
    for(i = 0; i < strlen(toParse); i++){
        //printf("Current token: %c\n", toParse[i]);
        if(toParse[i] == token)
            return 1;
    }
    return 0;
}
int startsWith(const char *a, const char *b) {
    char temp1[strlen(a)+1];
    char temp2[strlen(b)+1];

    strcpy(temp1, a);
    strcpy(temp2, b);

    makeLowerCase(temp1);
    makeLowerCase(temp2);

    if(strncmp(temp1, temp2, strlen(temp2)) == 0) return 1;
    return 0;
}
void makeLowerCase(char * toParse){
    if(strlen(toParse) != 0) {
        int i;
        for (i = 0; i < strlen(toParse); i++) {
            toParse[i] = tolower(toParse[i]);
        }
    }
}



