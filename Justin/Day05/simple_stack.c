#include "simple_stack.h"

int isempty( struct SIMPLE_STACK *stack) {

   if(stack->top == -1)
      return 1;
   else
      return 0;
}

int SimpleStackPop(struct SIMPLE_STACK *stack) {
    int data;
	
    if(!isempty(stack)) {
        data = stack->items[stack->top];
        stack->top = stack->top - 1;   
        return data;
    }
    
    printf("[!] Could not retrieve data, Stack is empty.\n");

    return -1;
}

bool SimpleStackPush(struct SIMPLE_STACK *stack, int data) {

    if(!isfull(stack)) {
        stack->top = stack->top + 1;   
        stack->items[stack->top] = data;
        return true;
    }

    printf("Could not insert data, Stack is full.\n");

    return false;
}

bool isfull(struct SIMPLE_STACK *stack) {

    if(stack->top == MAX_STACK_SIZE){
        return true;
    }
      
    return false;
}
