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

//main from Lab5
int main()
{
    LinkedList * theAlias;
    LinkedList * theHistory;

    int historyFileCount;
    int historyViewSize;

    char ** currentPath = NULL;

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
        }else if(doesContain(s, '|')) { //contains pipe
            if (doesContain(s, '>')) { //contains redirect FROM

            } else if (doesContain(s, '<')) {    //contains redirect TO

            } else {
                prePipe = parsePrePipe(s, &preCount);
                postPipe = parsePostPipe(s, &postCount);
                pipeIt(prePipe, postPipe, currentPath);
                clean(preCount, prePipe);
                clean(postCount, postPipe);
            }
        }else if(doesContain(s, '>')){ //contains redirect FROM & NO Pipe
            //
        }else if(doesContain(s, '<')){ //contains redirect TO & NO Pipe
            //
        }else {
            //parse and replace aliases with command

            argc = makeargs(s, &argv, " ");
            if(argc != -1)
                forkIt(argv, currentPath);

            clean(argc, argv);
            argv = NULL;
        }

        printf("command?: ");
        fgets(s, MAX, stdin);
        strip(s);

    }// end while

    return 0;

}// end main


