#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK_LIB
#define STACK_LIB
#define MAX_STACK_SIZE 200
#define MAX_STRING_SIZE 150

typedef struct Stack {
    char stack[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int top;
}Stack;

// top = -1 at initializaion.
// initializes the stack. This function must be called after the memory is created.
void initializeStack(Stack *stack);
// Check if the stack is empty.
bool isEmpty(Stack *stack);
// Check if the stack is full.
bool isFull(Stack *stack);
// Inspect the top most element of stack.
char *peek(Stack *stack);
// get the top most object out of the stack.
char *pop(Stack *stack);
// push the data into the stack. 
void push(char *data, Stack *stack);
// inspect all the elements of the stack. (developing use)
void inspectStack(Stack *stack);
//reverses the stack
void reverse(Stack *stack);
#endif  // STACK_LIB