#include "stack.h"
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

void destroyStack(Stack* stack) {
    free(stack->array);
    free(stack);
}

int isStackEmpty(Stack* stack) {
    return (stack->top == -1);
}

int isStackFull(Stack* stack) {
    return (stack->top == stack->capacity - 1);
}

void push(Stack* stack, int item) {
    if (isStackFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}
