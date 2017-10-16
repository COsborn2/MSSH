//
// Created by Cameron Osborn on 10/10/17.
//

#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct history
{
    char * theCommand;
};

typedef struct history History;

void cleanTypeHistory(void * ptr);
void * buildTypeHistory(char * theAlias);
int isSameHistory(const void * p1, const void * p2);
void printHistory(void * historyItem, FILE * printTo);
void printHistoryNumbers(void * historyItem, FILE * printTo, int numToPrint);

#endif //LAB6_HISTORY_H
