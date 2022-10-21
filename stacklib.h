#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef STACK_LIB
#define STACK_LIB
#define MAX_STACK_SIZE 200
#define MAX_STRING_SIZE 150
typedef struct Stack Stack_t;
struct Stack
{
    char stack[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int top;
};
// top = -1 at first

void initializeStack(Stack_t *stack);
bool isEmpty(Stack_t *stack);

bool isFull(Stack_t *stack);

char *peek(Stack_t *stack);

char *pop(Stack_t *stack);

void push(char *data, Stack_t *stack);

void inspectStack(Stack_t *stack);
void reverse(Stack_t *stack);
#endif // STACK_LIB