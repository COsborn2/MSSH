//
// Created by Cameron Osborn on 10/10/17.
//

#include "alias.h"

void cleanTypeAlias(void * ptr){
    Alias * toRemove = (Alias *)ptr;
    if(toRemove->theAlias != NULL) {
        int i;
        for (i = 0; i < toRemove->len; i++) {
            free(toRemove->theAlias[i]);
        }
        free(toRemove->theAlias);
        toRemove->theAlias = NULL;
    }
    free(toRemove->AKA);
    toRemove->AKA = NULL;
    free(toRemove);
    toRemove = NULL;
}
void * buildTypeAlias(char ** tempAlias, char * toAddAKA, int size) {
    if (tempAlias != NULL) {
        Alias *newAlias = (Alias *) calloc(1, sizeof(Alias));

        newAlias->theAlias = (char **) calloc(size, sizeof(char *));

        int i;
        for (i = 0; i < size; i++) {
            newAlias->theAlias[i] = (char *) calloc(strlen(tempAlias[i]) + 1, sizeof(char));
            strcpy(newAlias->theAlias[i], tempAlias[i]);
            //printf("%s\n", newAlias->theAlias[i]);
        }
        newAlias->len = size;

        newAlias->AKA = (char *) calloc((strlen(toAddAKA) + 1), sizeof(char));
        strcpy(newAlias->AKA, toAddAKA);

        return newAlias;
    }else{
        Alias * newAlias = (Alias *)calloc(1, sizeof(Alias));

        newAlias->theAlias = NULL;
        newAlias->AKA = (char *) calloc((strlen(toAddAKA) + 1), sizeof(char));
        strcpy(newAlias->AKA, toAddAKA);
        newAlias->len = size;

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

    if(toPrint->theAlias != NULL) {
        fprintf(printTo, "alias %s=", toPrint->AKA);
        if (toPrint->len > 0) {
            int i;
            for (i = 0; i < toPrint->len; i++) {
                if (i + 1 != toPrint->len)
                    fprintf(printTo, "'%s ", toPrint->theAlias[i]);
                else
                    fprintf(printTo, "%s'", toPrint->theAlias[i]);
            }
        }
        fprintf(printTo, "\n");
    }
}
//take in S as a char * and return it with an alias inside
void replaceAlias(char * toParse, void * data){
    if(toParse != NULL && data != NULL) {
        Alias *toTest = (Alias *) data;

        char *foundThis;
        foundThis = strstr(toParse, toTest->AKA);
    }
}