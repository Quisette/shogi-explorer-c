#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utilities.h"
#ifndef LL_H
#define LL_H
// structure of a node 
typedef struct Node {
    char *data;
    struct Node *next;
} Node_t;
// structure for a linked list (to get easier access)
typedef struct LinkedList {
    Node_t *head;
    Node_t *tail;
} List_t;
// initializes the node 
Node_t *genNode(char *str);
// initializes the list
List_t *initializeList(char *FirstNodeData);
// append node to existing list.
void append(char *str, List_t *list);
// inspects the whole list
void printList(List_t list);
//free the list after use 
void freeList(List_t *list);

#endif  // LL_H