#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void forkIt(char ** argv);
void forkItFileOut(char ** argv, int directTo);
void forkItFileIn(char ** argv, int directTo);

#endif
