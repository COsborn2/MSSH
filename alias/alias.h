//
// Created by Cameron Osborn on 10/10/17.
//

#ifndef ALIAS_H
#define ALIAS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct alias
{
    char ** theAlias;
    char * AKA;
    int len;
};

typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char ** tempAlias, char * toAddAKA, int size);
int isSameAlias(const void * p1, const void * p2);
void printAlias(void * aliasItem, FILE * printTo);
int containsAliasHelper(char * toParse, void * data);

#endif //LAB6_ALIAS_H
