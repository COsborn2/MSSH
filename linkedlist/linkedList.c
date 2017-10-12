/*
 * linkedList.c
 *
 *  Created on: September 23, 2017
 *      Author: Cameron Osborn
 *
 *  No known problems.
 */

#include "linkedList.h"

LinkedList * linkedList(){
  LinkedList * myLinkedList = (LinkedList *)calloc(1, sizeof(LinkedList));
  myLinkedList->head = (Node *) calloc(1, sizeof(Node));
  myLinkedList->size = 0;

  return myLinkedList;
}
void addLast(LinkedList * theList, Node * nn){
  if(theList == NULL || nn == NULL){
    exit(-99);
  }
  if(theList->size == 0){
    addFirst(theList, nn);
  }else{
    Node * cur = theList->head->next;
    Node * prev = cur->prev;
    while(cur->next != NULL){ //get to last node
      prev = cur;
      cur = cur->next;
    }
    cur->next = nn;
    nn->prev = cur;
    theList->size = theList->size+1;
  }
}
void addFirst(LinkedList * theList, Node * nn){
  if(theList == NULL || nn == NULL){
    exit(-99);
  }
  if(theList->size > 0){
    theList->head->next->prev = nn;
  }
  nn->next = theList->head->next;
  nn->prev = theList->head;
  theList->head->next = nn;
  theList->size = theList->size + 1;
}
void removeFirst(LinkedList * theList, void (*removeData)(void *)){
    if (theList == NULL) {
        exit(-99);
    }
    if(theList->size != 0){
        Node * cur = theList->head->next;
        
        if(theList->size > 1){
            theList->head->next = cur->next;
            cur->next->prev = theList->head;
            removeData(cur->data);
            free(cur);
            cur = NULL;
            theList->size = theList->size-1;
        }else{
            removeData(cur->data);
            free(cur);
            cur = NULL;
            theList->head->next = NULL;
            theList->size = theList->size-1;
        }
    }else{
        printf("\nEmpty List!\n\n");
    }
}
void removeLast(LinkedList * theList, void (*removeData)(void *)){
  if(theList == NULL){
    exit(-99);
  }
  if(theList->size > 0){
    Node * cur = theList->head->next;
    Node * prev = theList->head;
    while(cur->next != NULL){ //get to last node
      prev = cur;
      cur = cur->next;
    }
    prev->next = NULL;
    removeData(cur->data);
    free(cur);
    cur = NULL;
    theList->size = theList->size-1;
  }else{
    printf("\nList Empty\n\n");
  }
}
void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *)){
    if(theList == NULL || nn == NULL){
        exit(-99);
    }
    if (theList->size > 0) {
        if (theList->size == 1) {
            if(compare(nn->data, theList->head->next->data) == 0){
                //printf("Attemping to remove from a list of size 1\n");
                Node * cur = theList->head->next;
                removeData(cur->data);
                free(cur);
                cur = NULL;
                theList->head->next = NULL;
                theList->size = theList->size-1;
            }
        }else{
            //printf("In main statement:\n");
            Node * cur = theList->head;
            Node * prev;
            
            int count = 0;
            
            while (cur != NULL) {
                
                prev = cur;
                cur = cur->next;
                
                if(cur == NULL)
                    break;
                
                if (compare(cur->data, nn->data) == 0){
                    //printf("Found node matching what was passed in:\n");
                    if (count+1 != theList->size){
                        prev->next = cur->next;
                        cur->next->prev = prev;
                        theList->size = theList->size-1;
                    }else{
                        //printf("Removing last item in list (removeItem):\n");
                        prev->next = NULL;
                        removeData(cur->data);
                        free(cur);
                        cur = NULL;
                        theList->size = theList->size-1;
                    }
                    break;
                }//end if
                
                count = count + 1;
            }//end while
            
            if(cur != NULL){
                //printf("Freeing cur:\n");
                removeData(cur->data);
                free(cur);
                cur = NULL;
            }
        }//end if
    }else{
        printf("\nList Empty\n\n");
    }//end if
    
    //printf("Freeing nn:\n");
    removeData(nn->data);
    free(nn);
    nn = NULL;
}//end function
void clearList(LinkedList * theList, void (*removeData)(void *)){
    if(theList != NULL){
        if(theList->size != 0){
            Node * cur = theList->head->next;
            Node * temp;
            
            while(cur != NULL){
                temp = cur;
                cur = cur->next;
                removeData(temp->data);
                free(temp);
                temp = NULL;
            }
            
            free(cur);
            cur = NULL;
            free(theList->head);
            theList->head = NULL;
        }else{
            free(theList->head);
        }
    }
}
void printList(const LinkedList * theList, void (*convertData)(void *)){
  if(theList == NULL || theList->size == 0){
    printf("\nEmpty List\n");
  }else{
      printf("Array of size: %d\n", theList->size);
    Node * cur = theList->head->next;
    while(cur != NULL){
      convertData(cur->data);
      cur = cur->next;
    }

    printf("\n\n");
      
      /*
    printf("List in reverse:\n");
      cur = theList->head->next;
      while(cur->next != NULL){
          cur = cur->next;
      }
  
      printf("At end of list:\n");
      while(cur != theList->head){
          convertData(cur->data);
          cur = cur->prev;
      }
      printf("\n");
      */
  }
}
