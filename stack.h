#ifndef stack_H_INCLUDED
#define stack_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    char local;
    struct stack *top;
    struct stack *next;
}stack;


#endif