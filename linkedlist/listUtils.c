/*
 * listUtils.c
 *
 *  Created on: September 23, 2017
 *      Author: Cameron Osborn
 *
 *  No known problems.
 */

#include "listUtils.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ){
  Node * nn = (Node *)calloc(1, sizeof(Node));
  nn->data = buildData(fin);

  return nn;
}
Node * buildNode_Type(void * passedIn){
  Node * nn = (Node *)calloc(1, sizeof(Node));
  nn->data = passedIn;

  return nn;
}
void sort(LinkedList * theList, int (*compare)(const void *, const void *)){
    if (theList == NULL) {
        exit(-99);
    }
    if(theList->size != 0 && theList->size != 1){
      Node * start = theList->head->next;
      Node * traverse = NULL;
      Node * min = NULL;
      void * temp;

      while(start != NULL){
         min = start;
         traverse = start->next;

         while(traverse != NULL){
            if(compare(traverse->data,min->data) < 0){
               min = traverse;
            }
            traverse = traverse->next;
         }

         //swap start, min

         temp = min->data;
         min->data = start->data;
         start->data = temp;
         start = start->next;
      }
    }
}
void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in)){
    if (myList == NULL || total <= 0){
        exit(-99);
    }
  int i;
  Node * add;
  for(i = 0; i < total; i++){
    add = buildNode(fin, buildData);
    addLast(myList, add);
  }
}
