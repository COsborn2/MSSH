//
// Created by Cameron Osborn on 10/10/17.
//

#include "alias.h"

void cleanTypeAlias(void * ptr){
    Alias * toRemove = (Alias *)ptr;
    free(toRemove->theCommand);
    toRemove->theCommand = NULL;

    free(toRemove->AKA);
    toRemove->AKA = NULL;

    free(toRemove);
    toRemove = NULL;
}
void * buildTypeAlias(char * theCommand, char * toAddAKA) {
    if (theCommand != NULL) {
        Alias *newAlias = (Alias *) calloc(1, sizeof(Alias));

        newAlias->theCommand = (char *) calloc(strlen(theCommand)+1, sizeof(char));
        strcpy(newAlias->theCommand, theCommand);

        newAlias->AKA = (char *) calloc((strlen(toAddAKA) + 1), sizeof(char));
        strcpy(newAlias->AKA, toAddAKA);

        return newAlias;
    }else{
        Alias * newAlias = (Alias *)calloc(1, sizeof(Alias));

        newAlias->theCommand = NULL;

        newAlias->AKA = (char *) calloc((strlen(toAddAKA) + 1), sizeof(char));
        strcpy(newAlias->AKA, toAddAKA);

        return newAlias;
    }
}
int isSameAlias(const void * p1, const void * p2){
    Alias left = *((Alias*)(p1));
    Alias right = *((Alias*)(p2));

    return strcmp(left.AKA, right.AKA);
}
void printAlias(void * aliasItem, FILE * printTo){
    Alias * toPrint = (Alias *)aliasItem;
    //printf("len: %d\n", toPrint->len);

    fprintf(printTo, "alias %s='%s'\n", toPrint->AKA, toPrint->theCommand);
}
int doesContainAlias(char * toParse, void * data){
    if(toParse != NULL && data != NULL) {
        Alias *toTest = (Alias *) data;

        char * temp;
        temp = strstr(toParse, toTest->AKA);
        if(temp != NULL) {
            //printf("Alias found\n");
            return 1;
        }else {
            //printf("Alias not found\n");
            return 0;
        }
    }
}
void replaceAlias(char * toParse, void * data, void(*str_replace)(char *, const char *, const char *)){
    if(toParse != NULL && data != NULL) {
        //printf("In replaceAlias\n");
        Alias *toTest = (Alias *) data;

        //printf("Before: %s\n", toParse);
        char *foundThis;
        foundThis = strstr(toParse, toTest->AKA);
        if(foundThis != NULL){  //passed in void * IS an alias inside of toParse
            str_replace(toParse, toTest->AKA, toTest->theCommand);
        }
        //printf("After: %s\n", toParse);
    }
}