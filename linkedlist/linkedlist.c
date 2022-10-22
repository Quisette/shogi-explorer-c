#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkedlist.h"
#include "../utilities.h"

Node_t *genNode(char* str){
    Node_t *node = (Node_t*) malloc(sizeof(Node_t));
    node -> next = NULL;
    node -> data = str;
    return node;
}

List_t *initializeList(char* firstNodeData){
    List_t *list = (List_t*) malloc(sizeof(List_t));
    Node_t *node = genNode(firstNodeData);
    list-> head = node;
    list-> tail = node;
    return list;
}

void append(char* str, List_t *list){
    Node_t *newNode = genNode(str);
    list->tail->next = newNode;
    list->tail = newNode;
}
void printList(List_t list){
    int count = 0;
    Node_t *ptr = list.head;
    while(ptr  != NULL){
        printf("L:: %s\n", ptr->data);
        ptr = ptr->next;
    }
        
}
void delete(char* str, List_t *list){
    
}
void freeList(List_t *list){
    
    Node_t *temp ;
    while( list->head != NULL){
        temp = list->head;
        list->head = temp->next;
        free(temp);
    }
    free(list);
}