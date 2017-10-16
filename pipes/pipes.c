//
// Created by Cameron Osborn on 10/8/17.
//

#define _GNU_SOURCE
#include "pipes.h"
#include "../tokenize/makeArgs.h"

int containsPipe(char *s){
    int i;
    int count = 0;
    for(i = 0; i < strlen(s); i++){
        if(s[i] == '|')
            count = count+1;
    }

    //printf("There are %d pipes\n", count);

    return count;
}
char ** parsePrePipe(char *s, int * preCount){
    char ** argv;
    int argc;

    int i;
    for(i = 0; i < strlen(s); i++){
        if(s[i] == '|')
            *preCount = i;
    }

    char parsedString[*preCount+1];

    strncpy(parsedString, s, *preCount);

    parsedString[*preCount] = '\0';

    argc = makeargs(parsedString, &argv, " ");

    //printf("prePipe array is size: %d\n", argc);
    //int j;
    //for(i = 0; i < argc; i++){
    //    printf("%s\n", argv[i]);
    //}

    //printf("\n");

    *preCount = argc;

    return argv;
}
char ** parsePostPipe(char *s, int * postCount){
    char ** argv;
    int argc;

    int i;
    for(i = 0; i < strlen(s); i++){
        if(s[i] == '|')
            *postCount = i+1;   //get next thing after pipe character
    }

    int beginIndex = *postCount;
    int endIndex = strlen(s)+1; //grab \0

    char parsedString[(endIndex-beginIndex)];

    strncpy(parsedString, s + beginIndex, endIndex - beginIndex);   //copy from after pipe to end of string + \0

    //printf("parsedString: %s\n", parsedString);

    argc = makeargs(parsedString, &argv, " ");

    //printf("postPipe array is size: %d\n", argc);
    //int j;
    //for(i = 0; i < argc; i++){
    //    printf("%s\n", argv[i]);
    //}

    //printf("\n");


    *postCount = argc;


    return argv;
}
void pipeIt(char ** prePipe, char ** postPipe){
    pid_t pid2;
    int fd[2], res, status2;

    res = pipe(fd);

    if(res < 0)
    {
        printf("Pipe Failure\n");
        exit(-1);
    }// end if

    pid2 = fork();

    if(pid2 == 0) {  //parent
        pipe(fd);
        waitpid(pid2, &status2, 0);
        pid_t pid = fork();

        int status;

        if (pid != 0) {    //parent
            waitpid(pid, &status, 0);
            close(fd[1]);
            close(0);   //close stdin
            dup(fd[0]);
            close(fd[0]);   //close unused
            execvp(postPipe[0], postPipe);
            exit(-1);
        }
        else {  //child
            close(fd[0]);
            close(1);   //close stdout
            dup(fd[1]); //stout now points to stdin
            close(fd[1]);   //close unused
            execvp(prePipe[0], prePipe);
            exit(-1);
        }
    }else{
        waitpid(pid2, &status2, 0);
    }
}
void pipeItFileOut(char ** prePipe, char ** postPipe, int outFD){
    pid_t pid2;
    int fd[2], res, status2;

    res = pipe(fd);

    if(res < 0)
    {
        printf("Pipe Failure\n");
        exit(-1);
    }// end if

    pid2 = fork();

    if(pid2 == 0) {  //parent
        pipe(fd);
        waitpid(pid2, &status2, 0);
        pid_t pid = fork();

        int status;

        if (pid != 0) {    //parent
            waitpid(pid, &status, 0);
            close(fd[1]);
            close(0);   //close stdin
            dup(fd[0]);
            close(fd[0]);   //close unused
            execvp(postPipe[0], postPipe);
            exit(-1);
        }
        else {  //child
            close(fd[0]);
            close(1);   //close stdout
            dup(fd[1]); //stout now points to stdin
            close(fd[1]);   //close unused
            execvp(prePipe[0], prePipe);
            exit(-1);
        }
    }else{
        waitpid(pid2, &status2, 0);
    }
}