//
// Created by Cameron Osborn on 10/11/17.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int doesContain(char * toparse, char token);
void makeLowerCase(char * toParse);
FILE * openInputFile(char * fileName);
int startsWith(const char *a, const char *b);

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
int doesContain(char * toParse, char token){
    //printf("In doesContain\n");
    //printf("Token: %c\n", token);
    //printf("toParse: %s\n", toParse);
    int i;
    for(i = 0; i < strlen(toParse); i++){
        //printf("Current token: %c\n", toParse[i]);
        if(toParse[i] == token)
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
void getAlias(char * toParse){

}