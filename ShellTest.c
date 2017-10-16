//
// Created by Cameron Osborn on 10/11/17.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX 100

int doesContain(char * toparse, char * token);
void makeLowerCase(char * toParse);
FILE * openInputFile(char * fileName);
int startsWith(const char *a, const char *b);
int makeargs(char *s, char *** argv, char * tokenToParse);
void strip(char *array);
void removeSpaces(char * toParse);
void clean(int argc, char **argv);
void removeQuotations(char * toParse);

int main(){
    /*
     * Test fileIO
    char test[9] = {'t', 'e', 's', 't', '.', 't', 'x', 't', '\0'};

    FILE * newFile = openInputFile(test);

    if(newFile != NULL){
        printf("Success!\n");
    }else{
        printf("Fail!\n");
    }
    */

    /*
     * Test startsWith
    char test[20] = {'a', 'L', 'i', 'a', 's', '\0'};

    if(startsWith(test, "alias") == 1)
        printf("True\n");
    else
        printf("False\n");

    printf("Original string: %s\n", test);
     */

    /*
     * test substring cut
     */

    char test[16] = {'a', 'l', 'i', 'a', 's', ' ', 'l', 'l', '=', 'l', 's', ' ', '-', 'a', 'l', '\0'};
    /*
    char ** argv = NULL;
    int argc;

    argc = makeargs(test, &argv, "=");

    printf("Argv[0]: %s\n", argv[0]);

    char aliasName[100];

    strncpy(aliasName, argv[0]+5, strlen(argv[0])-5);

    removeSpaces(aliasName);
    printf("aliasName: %s\n", aliasName);

    printf("alias: %s\n", argv[1]);
     */

    /*
    char * findThis = NULL;
    findThis = strstr(test, "lia");

    if(findThis != NULL){
        printf("findThis: %s\n", findThis);
    }else{
        printf("Not found!\n");
    }
     */
    char test[100] = {"'", 'l', '"', 'o', 'l', '"', '\0'};

    printf("Before parse: %s\n", test);

    removeQuotations(test);

    printf("After parse: %s\n", test);
}
int startsWith(const char *a, const char *b) {
    char temp1[strlen(a)+1];
    char temp2[strlen(b)+1];

    strcpy(temp1, a);
    strcpy(temp2, b);

    makeLowerCase(temp1);
    makeLowerCase(temp2);

    if(strncmp(temp1, temp2, strlen(temp2)) == 0) return 1;
    return 0;
}
int doesContain(char * toParse, char * token){
    //printf("In doesContain\n");
    //printf("Token: %c\n", token);
    //printf("toParse: %s\n", toParse);
    int i;
    for(i = 0; i < strlen(toParse); i++){
        //printf("Current token: %c\n", toParse[i]);
        if(toParse[i] == *token)
            return 1;
    }
    return 0;
}
void makeLowerCase(char * toParse){
    if(strlen(toParse) != 0) {
        int i;
        for (i = 0; i < strlen(toParse); i++) {
            toParse[i] = tolower(toParse[i]);
        }
    }
}
FILE * openInputFile(char * fileName) {
    FILE * fin = fopen(fileName, "r");

    return fin;
}// end openInputFile_Prompt
int makeargs(char *s, char *** argv, char * tokenToParse)
{
    char copy[MAX];
    char *tempPtr;
    char *tempPtr2;
    char *token;

    strcpy(copy, s);

    int count = 0;

    token = strtok_r(s, tokenToParse, &tempPtr);

    while(token != NULL){
        count++;
        token = strtok_r(NULL, tokenToParse, &tempPtr);
    }

    if(count == 0){
        return -1;
    }

    (*argv) = (char **)calloc(count+1, sizeof(char *));

    token = strtok_r(copy, tokenToParse, &tempPtr2);
    strip(token);

    (*argv)[0] = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy((*argv)[0], token);

    int x;
    for(x = 1; x < count; x++){
        token = strtok_r(NULL, tokenToParse, &tempPtr2);
        strip(token);
        (*argv)[x] = (char *)calloc(strlen(token)+1, sizeof(char));
        strcpy((* argv)[x], token);
    }

    return count;
}// end makeArgs
void strip(char *array)
{
    if(array == NULL)
    {
        perror("array is null");
        exit(-99);
    }// end if

    int len = strlen(array), x = 0;

    while(array[x] != '\0' && x < len)
    {
        if(array[x] == '\r')
            array[x] = '\0';

        else if(array[x] == '\n')
            array[x] = '\0';

        x++;

    }// end while

}// end strip
void removeSpaces(char * toParse) {
    int count = 0;

    for (int i = 0; i < strlen(toParse); i++) {
        if (toParse[i] != ' ') {
            toParse[count++] = toParse[i];
        }
    }
    toParse[count] = '\0';
}
void clean(int argc, char **argv)
{
    int x;
    for(x = 0; x < argc; x++){
        free(argv[x]);
        argv[x] = NULL;
    }
    free(argv);
    argv = NULL;
}// end clean
void removeQuotations(char * toParse){
    char temp[strlen(toParse)+1];
    if(toParse != NULL){
        int index = 0;
        int i;
        for(i = 0; i < strlen(toParse); i++){
            if(toParse[i] != '"' && toParse[i] != "'"){
                temp[index] = toParse[i];
                index++;
            }
        }
        strcmp(toParse, temp);
    }
}
