#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utilities.h"
#ifndef LL_H
#define LL_H

typedef struct Node {
    char *data;
    struct Node *next;
} Node_t;

typedef struct LinkedList {
    Node_t *head;
    Node_t *tail;
} List_t;

Node_t *genNode(char *str);
List_t *initializeList(char *FirstNodeData);
void append(char *str, List_t *list);
void printList(List_t list);
void freeList(List_t *list);

#endif  // LL_H