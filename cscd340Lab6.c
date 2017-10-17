//
// Created by Cameron Osborn on 10/10/17.
//
// Need to add redirection for pipe both directions
// Need to add aliasing
//

#include <ctype.h>
#include <stdio.h>
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/linkedList.h"
#include "./alias/alias.h"
#include "./history/history.h"
#include "./linkedlist/listUtils.h"

//main from Lab5
int main()
{
    LinkedList * theAlias = linkedList();
    LinkedList * theHistory = linkedList();

    int histCount = 100;
    int histFileCount = 1000;

    int currentHistoryCount = 0;

    int enter = 1;

    char currentPath[100];
    int printPath = 0;

    char temporaryS[100];

    char startingHOME[1024];

    int argc, pipeCount;
    char **argv = NULL, s[MAX];
    int preCount = 0, postCount = 0;
    char ** prePipe = NULL, ** postPipe = NULL;

    char ** redirectionArgv;
    int redirectionArgc;

    char temp[100];
    char tempSpaces[100];

    //handle opening msshrc
    FILE * finMSSHRC = fopen(".msshrc", "r");

    if(finMSSHRC != NULL){
        //printf("Found msshrc\n");

        fgets(temp, MAX, finMSSHRC);
        strip(temp);
        strcpy(tempSpaces, temp);
        removeSpaces(temp);

        while(!feof(finMSSHRC)){
            //printf("Temp is: %s\n", temp);
            if(startsWith(temp, "histcount")) {
                //printf("In HistoryCount\n");
                char ** temp2;
                int tempCount = makeargs(temp, &temp2, "=");
                if(tempCount >= 1)
                    strip(temp2[1]);
                histCount = atoi(temp2[1]);
                //printf("histCount: %d\n", histCount);
                clean(tempCount, temp2);
            }else if(startsWith(temp, "histfilecount")){
                //printf("In HistoryFileCount\n");
                char ** temp2;
                int tempCount = makeargs(temp, &temp2, "=");
                if(tempCount >= 1)
                    strip(temp2[1]);
                histFileCount = atoi(temp2[1]);
                //printf("histFileCount: %d\n", histFileCount);
                clean(tempCount, temp2);
            }else if(startsWith(temp, "alias")) {
                //alias ll='ls -al | wc -w'
                //printf("Building new Alias\n");
                char **aliasTempNew;
                int iATempNew;

                iATempNew = makeargs(temp, &aliasTempNew, "=");

                //printf("aliasTemp[0]: %s\n", aliasTempNew[0]); //alias ll
                //printf("aliasTemp[1]: %s\n", aliasTempNew[1]); //'ls -al | wc -w'


                if (iATempNew > 1) {
                    //printf("In first\n");
                    char **aliasTemp2New;
                    int iATemp2New;

                    iATemp2New = makeargs(aliasTempNew[0], &aliasTemp2New, " ");

                    //printf("aliasTemp2[0]: %s\n", aliasTemp2New[0]); //alias
                    //printf("aliasTemp2[1]: %s\n", aliasTemp2New[1]); //ll

                    if (iATemp2New > 1) {
                        //printf("In second\n");
                        char aliasName[100];

                        strip(aliasTemp2New[1]);
                        strcpy(aliasName, aliasTemp2New[1]);

                        strip(aliasTempNew[1]);
                        removeQuotations(aliasTempNew[1]);

                        removeItem(theAlias, buildNode_Type(buildTypeAlias(aliasTempNew[1], aliasName)), cleanTypeAlias,
                                   isSameAlias);
                        addLast(theAlias, buildNode_Type(buildTypeAlias(aliasTempNew[1], aliasName)));
                    }
                    clean(iATemp2New, aliasTemp2New);
                }
                clean(iATempNew, aliasTempNew);
            }else if(startsWith(temp, "path")){
                strcpy(currentPath, temp);

                putenv(currentPath);
                printPath = 1;
            }

            fgets(temp, MAX, finMSSHRC);
            strip(temp);
            strcpy(tempSpaces, temp);
            removeSpaces(temp);
        }
    }

    //.mssh_history
    FILE * finHISTORY = fopen(".mssh_history", "r");
    if(finHISTORY != NULL){

        fgets(temp, MAX, finHISTORY);
        strip(temp);

        while(!feof(finHISTORY)){
            currentHistoryCount++;
            addLast(theHistory, buildNode_Type(buildTypeHistory(temp)));

            fgets(temp, MAX, finHISTORY);
            strip(temp);
        }
    }

    printf("command?: ");
    fgets(s, MAX, stdin);
    strip(s);

    strcpy(temporaryS, s);
    makeLowerCase(temporaryS);

    if(doesMatchLastItem(theHistory, buildNode_Type(buildTypeHistory(temporaryS)), isSameHistory, cleanTypeHistory) == 0 && strcmp(s, "exit") != 0 && !startsWith(s, "!")){
        currentHistoryCount++;
        addLast(theHistory, buildNode_Type(buildTypeHistory(s)));
    }

    while(strcmp(s, "exit") != 0) {
        if(startsWith(s, "!") || startsWith(s, "!!")) {
            if(startsWith(s, "!")){
                char historyTemp[100];
                strcpy(historyTemp, s);
                removeSpaces(historyTemp);
                if(historyTemp[1] == '!') {
                    //!!
                    //printf("Starts with !!\n");

                    void * lastItemHistory = NULL;
                    lastItemHistory = returnLastItem(theHistory);

                    if(lastItemHistory != NULL) {
                        History *lastItemInHistory = (History *) lastItemHistory;

                        strcpy(s, lastItemInHistory->theCommand);
                    }

                }else{
                    //!
                    //printf("Starts with !\n");

                    int getItemAt;

                    char tempForInt[100] = {'-', '1', '\0'};

                    int startIndex = 1;
                    int endIndex = strlen(historyTemp);

                    bzero(tempForInt, 100);

                    strncpy(tempForInt, historyTemp + startIndex, endIndex-startIndex);

                    getItemAt = atoi(tempForInt);

                    //printf("GetItemAt: %d\n", getItemAt);

                    void *findHistoryItem = NULL;
                    findHistoryItem = findIndex(theHistory, getItemAt-1);

                    if (findHistoryItem != NULL) {
                        History *foundHistoryItem = (History *) findHistoryItem;

                        strcpy(s, foundHistoryItem->theCommand);
                    }
                }
            }
        }
        if(startsWith(s, "history")) {
            int count = 0;
            if (theHistory != NULL && theHistory->size > 0) {
                Node *cur = theHistory->head;
                int printCount = 0;
                int startingIndex = currentHistoryCount;
                startingIndex = startingIndex - histCount;
                int index = 0;

                while (cur != NULL) {
                    if (count < histCount && index > startingIndex) {
                        printHistoryNumbers(cur->data, stdout, printCount);
                        count++;
                    }
                    cur = cur->next;
                    printCount++;
                    index++;
                }
            }
        }
        if(startsWith(s, "cd")){ //change directory command
            char * temp;
            temp = getenv("HOME");
            //printf("%s\n", temp);

            char ** cdArgv;
            int cdArgc = makeargs(s, &cdArgv, " ");
            //printf("cdArgc: %d\n", cdArgc);
            if(cdArgc > 1) {
                chdir(cdArgv[1]);
            }else{
                chdir(temp);
            }

            clean(cdArgc, cdArgv);
            cdArgv = NULL;
        }

        if (startsWith(s, "alias")) {
            char tempTest[100];
            strcpy(tempTest, s);

            removeSpaces(tempTest);

            if (strlen(tempTest) == 5) {    //only alias, print all aliases to screen
                printList(theAlias, printAlias, stdout);
            }else if (!doesContain(s, "=")) {  //single alias, print out alias
                char ** aliasTemp;
                int iATemp;

                iATemp = makeargs(s, &aliasTemp, " ");

                if(iATemp > 1){
                    void * tempHolder = NULL;
                    char aliasName[100];
                    strcpy(aliasName, aliasTemp[1]);
                    removeSpaces(aliasName);
                    tempHolder = findItem(theAlias, buildNode_Type(buildTypeAlias(NULL, aliasName)), cleanTypeAlias, isSameAlias);

                    if(tempHolder != NULL) {
                        printAlias(tempHolder, stdout);
                    }
                }
                clean(iATemp, aliasTemp);
            }else {  //add alias
                //alias ll='ls -al | wc -w'
                //printf("Building new Alias\n");
                char **aliasTempNew;
                int iATempNew;

                iATempNew = makeargs(s, &aliasTempNew, "=");

                //printf("aliasTemp[0]: %s\n", aliasTempNew[0]); //alias ll
                //printf("aliasTemp[1]: %s\n", aliasTempNew[1]); //'ls -al | wc -w'


                if (iATempNew > 1) {
                    //printf("In first\n");
                    char **aliasTemp2New;
                    int iATemp2New;

                    iATemp2New = makeargs(aliasTempNew[0], &aliasTemp2New, " ");

                    //printf("aliasTemp2[0]: %s\n", aliasTemp2New[0]); //alias
                    //printf("aliasTemp2[1]: %s\n", aliasTemp2New[1]); //ll

                    if (iATemp2New > 1) {
                        //printf("In second\n");
                        char aliasName[100];

                        strip(aliasTemp2New[1]);
                        removeSpaces(aliasTemp2New[1]);
                        strcpy(aliasName, aliasTemp2New[1]);

                        strip(aliasTempNew[1]);
                        removeQuotations(aliasTempNew[1]);

                        removeItem(theAlias, buildNode_Type(buildTypeAlias(aliasTempNew[1], aliasName)), cleanTypeAlias,
                                   isSameAlias);
                        addLast(theAlias, buildNode_Type(buildTypeAlias(aliasTempNew[1], aliasName)));
                    }
                    clean(iATemp2New, aliasTemp2New);
                }
                clean(iATempNew, aliasTempNew);
            }
        }else if(startsWith(s, "unalias")){
            char ** unaliasTemp;
            int unAliasTemp;

            unAliasTemp = makeargs(s, &unaliasTemp, " ");

            if(unAliasTemp > 1) {
                removeItem(theAlias, buildNode_Type(buildTypeAlias(NULL, unaliasTemp[1])), cleanTypeAlias, isSameAlias);
            }
            clean(unAliasTemp, unaliasTemp);
        }else if (startsWith(s, "path")) {
            removeSpaces(s);

            strcpy(currentPath, s);

            putenv(currentPath);

            printPath = 1;
        }

        if(!startsWith(s, "alias") && !startsWith(s, "!") && !startsWith(s, "history") && !startsWith(s, "unalias") && !startsWith(s, "path") && !startsWith(s, "cd")) {
            //printf("S before: %s\n", s);
            replaceAliasMain(theAlias, s, doesContainAlias, str_replace);
            //printf("S after: %s\n", s);
        }

        if(doesContain(s, "|")) { //contains pipe
            if (doesContain(s, ">")) { //contains redirect FROM
                char * temp;
                temp = strstr(s, ">>");
                if(temp != NULL){
                    //printf("In pipe WITH redirect TO - append\n");

                    //ls -al | wc -w >> test.txt

                    redirectionArgc = makeargs(s, &redirectionArgv, ">");

                    if(redirectionArgc > 1) {
                        strip(redirectionArgv[1]);//test.txt
                        removePointers(redirectionArgv[1]);
                        removeSpaces(redirectionArgv[1]);
                        //printf("redirectionArgv[1]: %s\n", redirectionArgv[1]);
                        FILE * redirectTo = fopen(redirectionArgv[1], "a");
                        if(redirectTo != NULL) {
                            int redirectOutFD = fileno(redirectTo);
                            removePointers(redirectionArgv[0]);

                            prePipe = parsePrePipe(redirectionArgv[0], &preCount);
                            postPipe = parsePostPipe(redirectionArgv[0], &postCount);
                            pipeItFileOut(prePipe, postPipe, redirectOutFD);
                            clean(preCount, prePipe);
                            clean(postCount, postPipe);

                            fclose(redirectTo);
                        }
                    }

                    clean(redirectionArgc, redirectionArgv);
                }else{
                    //printf("In pipe WITH redirect TO\n");

                    redirectionArgc = makeargs(s, &redirectionArgv, ">");

                    if(redirectionArgc > 1) {
                        strip(redirectionArgv[1]);
                        removeSpaces(redirectionArgv[1]);
                        //printf("redirectionArgv[1]: %s\n", redirectionArgv[1]);
                        FILE * redirectTo = fopen(redirectionArgv[1], "w");
                        if(redirectTo != NULL) {
                            int redirectOutFD = fileno(redirectTo);

                            prePipe = parsePrePipe(redirectionArgv[0], &preCount);
                            postPipe = parsePostPipe(redirectionArgv[0], &postCount);
                            pipeItFileOut(prePipe, postPipe, redirectOutFD);
                            clean(preCount, prePipe);
                            clean(postCount, postPipe);

                            fclose(redirectTo);
                        }
                    }

                    clean(redirectionArgc, redirectionArgv);
                }
            } else if (doesContain(s, "<")) {    //contains redirect TO
                //printf("In pipe WITH redirect FROM\n");
                redirectionArgc = makeargs(s, &redirectionArgv, "<");

                if(redirectionArgc > 1) {
                    strip(redirectionArgv[1]);
                    FILE * redirectFrom = fopen(redirectionArgv[1], "r");
                    if(redirectFrom != NULL) {
                        int redirectOutFD = fileno(redirectFrom);

                        prePipe = parsePrePipe(redirectionArgv[0], &preCount);
                        postPipe = parsePostPipe(redirectionArgv[0], &postCount);
                        pipeItFileIn(prePipe, postPipe, redirectOutFD);
                        clean(preCount, prePipe);
                        clean(postCount, postPipe);

                        fclose(redirectFrom);
                    }
                }

                clean(redirectionArgc, redirectionArgv);
            } else {
                //printf("In pipe\n");
                prePipe = parsePrePipe(s, &preCount);
                postPipe = parsePostPipe(s, &postCount);
                pipeIt(prePipe, postPipe);
                clean(preCount, prePipe);
                clean(postCount, postPipe);
            }
        }else if(doesContain(s, ">")){ //contains redirect FROM & NO Pipe
            char * temp;
            temp = strstr(s, ">>");
            if(temp != NULL) {
                //printf("NO pipe redirect from - append\n");
                redirectionArgc = makeargs(s, &redirectionArgv, ">");

                if (redirectionArgc > 1) {
                    strip(redirectionArgv[0]);
                    strip(redirectionArgv[1]);

                    removePointers(redirectionArgv[0]);
                    removePointers(redirectionArgv[1]);

                    strip(redirectionArgv[1]);
                    removeSpaces(redirectionArgv[1]);
                    //printf("Create FILE: %s\n", redirectionArgv[1]);
                    FILE *redirectTo = fopen(redirectionArgv[1], "a");

                    if (redirectTo != NULL) {
                        argc = makeargs(redirectionArgv[0], &argv, " ");
                        if (argc != -1)
                            forkItFileOut(argv, fileno(redirectTo));

                        clean(argc, argv);
                        argv = NULL;

                        fclose(redirectTo);
                    }
                }
                clean(redirectionArgc, redirectionArgv);
            }else{
                //printf("NO pipe redirect from\n");
                redirectionArgc = makeargs(s, &redirectionArgv, ">");

                if (redirectionArgc > 1) {
                    strip(redirectionArgv[0]);
                    strip(redirectionArgv[1]);

                    strip(redirectionArgv[1]);
                    removeSpaces(redirectionArgv[1]);
                    //printf("Create FILE: %s\n", redirectionArgv[1]);
                    FILE *redirectTo = fopen(redirectionArgv[1], "w");

                    if (redirectTo != NULL) {
                        argc = makeargs(redirectionArgv[0], &argv, " ");
                        if (argc != -1)
                            forkItFileOut(argv, fileno(redirectTo));

                        clean(argc, argv);
                        argv = NULL;

                        fclose(redirectTo);
                    }
                }
                clean(redirectionArgc, redirectionArgv);
            }
        }else if(doesContain(s, "<")){ //contains redirect TO & NO Pipe
            //printf("NO pipe redirect to\n");
            redirectionArgc = makeargs(s, &redirectionArgv, "<");

            if(redirectionArgc > 1){
                strip(redirectionArgv[0]);
                strip(redirectionArgv[1]);

                strip(redirectionArgv[1]);
                removeSpaces(redirectionArgv[1]);
                //printf("Create FILE: %s\n", redirectionArgv[1]);
                FILE * redirectTo = fopen(redirectionArgv[1], "r");

                if(redirectTo != NULL) {
                    argc = makeargs(redirectionArgv[0], &argv, " ");
                    if (argc != -1)
                        forkItFileIn(argv, fileno(redirectTo));

                    clean(argc, argv);
                    argv = NULL;

                    fclose(redirectTo);
                }
            }
            clean(redirectionArgc, redirectionArgv);
        }else {
            if (!startsWith(s, "alias") && !startsWith(s, "!") && !startsWith(s, "history") && !startsWith(s, "unalias") && !startsWith(s, "path") && !startsWith(s, "cd")) {
                argc = makeargs(s, &argv, " ");
                if (argc != -1)
                    forkIt(argv);

                clean(argc, argv);
                argv = NULL;
            }

        }

        printf("command?: ");
        fgets(s, MAX, stdin);
        strip(s);

        strcpy(temporaryS, s);
        makeLowerCase(temporaryS);

        if(doesMatchLastItem(theHistory, buildNode_Type(buildTypeHistory(temporaryS)), isSameHistory, cleanTypeHistory) == 0 && strcmp(s, "exit") != 0 && !startsWith(s, "!")){
            currentHistoryCount++;

            addLast(theHistory, buildNode_Type(buildTypeHistory(s)));
        }
    }// end while

    //printf("Create .msshrc file\n");
    FILE * foutMSSHRC = fopen(".msshrc", "w");
    if(foutMSSHRC != NULL) {
        //printf(".msshrc created\n");
        fprintf(foutMSSHRC, "HISTCOUNT=%d\n", histCount);
        fprintf(foutMSSHRC, "HISTFILECOUNT=%d\n", histFileCount);

        printList(theAlias, printAlias, foutMSSHRC);


        if (printPath == 1) {
            fprintf(foutMSSHRC, "%s\n", currentPath);
        }


        fclose(foutMSSHRC);
    }

    //printf("Create .mssh_history file\n");
    FILE * foutHISTORY = fopen(".mssh_history", "w");
    if(foutHISTORY != NULL) {
        //printf(".mssh_history created\n");

        printDefinedList(theHistory, printHistory, foutHISTORY, currentHistoryCount, histFileCount);

        fclose(foutHISTORY);
    }

    if(finMSSHRC != NULL)
        fclose(finMSSHRC);
    if(finHISTORY != NULL)
        fclose(finHISTORY);

    clearList(theAlias, cleanTypeAlias);
    free(theAlias);
    theAlias = NULL;

    clearList(theHistory, cleanTypeHistory);
    free(theHistory);
    theHistory = NULL;

    return 0;

}// end main
