#include <stdio.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 500

struct SIMPLE_STACK{
    int top; 
    int items[MAX_STACK_SIZE]; 
};

int SimpleStackPop(struct SIMPLE_STACK *stack);
bool SimpleStackPush(struct SIMPLE_STACK *stack, int data);
bool isfull(struct SIMPLE_STACK *stack);