//
// Created by Cameron Osborn on 10/10/17.
//

#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>

struct history
{
    char * theCommand;
};

typedef struct history History;

void cleanTypeHistory(void * ptr);
void * buildTypeHistory(char * theAlias);
int isSameHistory(const void * p1, const void * p2);

#endif //LAB6_HISTORY_H
