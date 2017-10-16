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
    char * AKA;
    char * theCommand;
};

typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char * theCommand, char * toAddAKA);
int isSameAlias(const void * p1, const void * p2);
void printAlias(void * aliasItem, FILE * printTo);
int doesContainAlias(char * toParse, void * data);
void replaceAlias(char * toParse, void * data, void(*str_replace)(char *, const char *, const char *));

#endif //LAB6_ALIAS_H
