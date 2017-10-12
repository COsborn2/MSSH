//
// Created by Cameron Osborn on 10/10/17.
//

#include "history.h"

void cleanTypeHistory(void * ptr){
    History * theHistory = (History *)ptr;

    free(theHistory->theCommand);
    theHistory->theCommand = NULL;

    free(theHistory);
    theHistory = NULL;
}
void * buildTypeHistory(char * theAlias){
    History * newHistoryItem = (History *)calloc(1, sizeof(History*));

    newHistoryItem->theCommand = (char *)calloc(strlen(theAlias)+1, sizeof(char*));

    return newHistoryItem;
}
int isSameHistory(const void * p1, const void * p2){
    History left = *((History*)(p1));
    History right = *((History*)(p2));

    return strcmp(left.theCommand, right.theCommand);
}