//
// Created by Cameron Osborn on 10/10/17.
//

#include "alias.h"

void cleanTypeAlias(void * ptr){
    Alias * toRemove = (Alias *)ptr;
    int i;
    for(i = 0; i < toRemove->len; i++){
        free(toRemove->theAlias[i]);
    }
    free(toRemove->AKA);
    toRemove->AKA = NULL;
    free(toRemove->theAlias);
    toRemove->theAlias = NULL;
    free(toRemove);
    toRemove = NULL;
}
void * buildTypeAlias(char ** tempAlias, char * toAddAKA, int size){
    Alias * newAlias = (Alias *)calloc(1, sizeof(Alias));

    newAlias->theAlias = (char **)calloc(size, sizeof(char**));

    int i;
    for(i = 0; i < size; i++){
        newAlias->theAlias[i] = (char*)calloc(strlen(tempAlias[i])+1, sizeof(char*));
    }
    newAlias->len = size;

    newAlias->AKA = (char *)calloc((strlen(toAddAKA)+1), sizeof(char*));
    strcpy(newAlias->AKA, toAddAKA);

    return newAlias;
}
int isSameAlias(const void * p1, const void * p2){
    Alias left = *((Alias*)(p1));
    Alias right = *((Alias*)(p2));

    return strcmp(left.AKA, right.AKA);
}