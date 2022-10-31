// This is a double pointer version of linked list.

#include "linkedlist.h"

Node *createNode(void* data){
    Node *p = malloc(sizeof(Node));
    (p->data) = (char*) data;
    p->next = NULL;
    return p;
}

void pushFront(LinkedList *list, Node *newNode){
    newNode->next = *list->head;
    *list->head = newNode;
}

void pushBack(LinkedList *list, Node *newNode){
    Node **tracer;
    tracer = list->head;
    while(*tracer){
        tracer = &(*tracer)-> next;
    }
    newNode -> next = *tracer;
    *tracer = newNode;
    *list->tail = newNode;
}

void insertInOrder(LinkedList *list, Node *node){
    Node **curr = list->head;
    while(*curr && (*curr)->data < node->data){
        curr = &((*curr)->next);
    }
    node->next = *curr;
    *curr = node;
    if(!*list->tail) getTail(list);
    else if((*list->tail)->next != NULL)
        *list->tail = (*list->tail)->next;
}
void print(LinkedList list){
    Node *tracer = *list.head; // we want to make a copy of a value, so we do not use double pointers.
    
    while(tracer){
        printf("(%s)->", (char*)tracer->data);// this can be edited 
        tracer = (tracer)->next;
    }
    printf("NULL\n");
    
}



void initializeList(LinkedList *list){
    list->head = malloc(sizeof(LinkedList*)); //  pointer to pointer declaration
    list->tail = malloc(sizeof(LinkedList*));
}

void getTail(LinkedList *list){
    Node * tracer   = *list->head;
    while(tracer){
        if((tracer)->next == NULL){
            printf("reached\n");
            *(list->tail) = tracer;
            // printf("%d\n", (*list->tail)->data);
            return;
        }
        tracer = (tracer) ->next;
    }
}























