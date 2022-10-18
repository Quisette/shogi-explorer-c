#include "stacklib.h"

#include<stdio.h>
void initializeStack(Stack_t *stack){
    stack->top = -1;

}
bool isEmpty(Stack_t *stack) {

   if(stack->top == -1)
      return 1;
   else
      return 0;
}
   
bool isFull(Stack_t *stack) {

   if(stack->top == MAX_STACK_SIZE)
      return 1;
   else
      return 0;
}

char* peek(Stack_t *stack) {
   return stack->stack[stack->top];
}

char* pop(Stack_t *stack) {
   char* data;
	
   if(!isEmpty(stack)) {
      data = stack->stack[stack->top];
      stack->top = stack->top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

void push(char* data,Stack_t *stack) {

   if(!isFull(stack)) {
      stack->top = stack->top + 1;
      strcpy(stack->stack[stack->top], data) ;  
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}