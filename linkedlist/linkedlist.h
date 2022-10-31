#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef LL_H
#define LL_H
typedef struct Node{
    struct Node *prev;
    void * data;
    struct Node *next;
}Node;


typedef struct LinkedList
{
    Node **head; // use double pointer to modify the value of pointer
    Node **tail;
    // or we can use *head and use &head to work as an argument of double pointer w/o malloc. 

}LinkedList;

// void insertInOrder(Node **list, node *newNode);
void pushFront(LinkedList *list, Node *newNode);
void pushBack(LinkedList *list, Node *newNode);
Node *createNode(void* data);
void insertInOrder(LinkedList *list, Node *node);
void print(LinkedList list);
void initializeList(LinkedList *list);
void getTail(LinkedList *list);

#endif //LL_H