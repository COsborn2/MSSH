#include "myUtils.h"

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

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list\n");
   printf("2) Add First\n");
   printf("3) Add Last\n");
   printf("4) Sort\n");
   printf("5) Remove Item\n"); 
   printf("6) Quit\n"); 
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);

   
   while(choice < 1 || choice > 6)
   {
      printf("1) Print the list\n");
      printf("2) Add First\n");
      printf("3) Add Last\n");
      printf("4) Sort\n");
      printf("5) Remove Item\n"); 
      printf("6) Quit\n"); 
      printf("Choice --> ");
      fgets(temp, MAX, stdin);
      choice = atoi(temp);
   
   }// end while

   return choice;
   
}// end menu
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
int startsWith(const char *a, const char *b) {
    char temp1[strlen(a)+1];
    char temp2[strlen(b)+1];

    strcpy(temp1, a);
    strcpy(temp2, b);

    makeLowerCase(temp1);
    makeLowerCase(temp2);

    //printf("temp1: %s\n", temp1);
    //printf("temp2: %s\n", temp2);

    if(strncmp(temp1, temp2, strlen(temp2)) == 0) return 1;
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
void removeSpaces(char * toParse) {
    int count = 0;

    for (int i = 0; i < strlen(toParse); i++) {
        if (toParse[i] != ' ') {
            toParse[count++] = toParse[i];
        }
    }
    toParse[count] = '\0';
}
void removeQuotations(char * toParse){
    if(toParse != NULL){
        int count = 0;

        for (int i = 0; i < strlen(toParse); i++) {
            if (toParse[i] != '\'' && toParse[i] != '"') {
                toParse[count++] = toParse[i];
            }
        }
        toParse[count] = '\0';
    }
}
void str_replace(char *toParse, const char *toReplace, const char *replaceWith) {
    char temp[1024] = { 0 };
    char * startAt = &temp[0];
    const char * tempPtr = toParse;
    size_t lengthOfToReplace = strlen(toReplace);
    size_t lengthOfReplaceWith = strlen(replaceWith);

    while (1) {
        const char *tempPtr2 = strstr(tempPtr, toReplace);

        if (tempPtr2 == NULL) {
            strcpy(startAt, tempPtr);
            break;
        }

        memcpy(startAt, tempPtr, tempPtr2 - tempPtr);
        startAt += tempPtr2 - tempPtr;

        memcpy(startAt, replaceWith, lengthOfReplaceWith);
        startAt += lengthOfReplaceWith;
        
        tempPtr = tempPtr2 + lengthOfToReplace;
    }

    // write altered string back to toParse
    strcpy(toParse, temp);
}
void removePointers(char * toParse){
    if(toParse != NULL){
        int count = 0;

        for (int i = 0; i < strlen(toParse); i++) {
            if (toParse[i] != '>') {
                toParse[count++] = toParse[i];
            }
        }
        toParse[count] = '\0';
    }
}
void removeTrailingSpaces(char* source)
{
    char* i = source;
    char* j = source;
    while(*j != 0)
    {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
}