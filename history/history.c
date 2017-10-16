//
// Created by Cameron Osborn on 10/10/17.
//

#include "history.h"

void cleanTypeHistory(void * ptr){
    //printf("In cleanTypeHistory\n");
    History * theHistory = (History *)ptr;

    free(theHistory->theCommand);
    theHistory->theCommand = NULL;

    free(theHistory);
    theHistory = NULL;
}
void * buildTypeHistory(char * theHistoryItem){
    History * newHistoryItem = (History *)calloc(1, sizeof(History));

    newHistoryItem->theCommand = (char *)calloc(strlen(theHistoryItem)+1, sizeof(char));
    strcpy(newHistoryItem->theCommand, theHistoryItem);

    return newHistoryItem;
}
int isSameHistory(const void * p1, const void * p2){
    History left = *((History*)(p1));
    History right = *((History*)(p2));

    return strcmp(left.theCommand, right.theCommand);
}
void printHistory(void * historyItem, FILE * printTo){
    if(historyItem != NULL) {
        History *toPrint = (History *) historyItem;

        fprintf(printTo, "%s\n", toPrint->theCommand);
    }
}
void printHistoryNumbers(void * historyItem, FILE * printTo, int numToPrint){
    if(historyItem != NULL) {
        History *toPrint = (History *) historyItem;

        fprintf(printTo, "%d %s\n", numToPrint, toPrint->theCommand);
    }
}