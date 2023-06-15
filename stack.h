#ifndef STACK_H
#define STACK_H

typedef struct {
    int capacity;  // Capacidade máxima da pilha
    int top;  // Índice do topo da pilha
    int* array;  // Array para armazenar os elementos da pilha
} Stack;

Stack* createStack(int capacity);  // Cria uma nova pilha com a capacidade especificada
void destroyStack(Stack* stack);  // Libera a memória alocada para a pilha
int isStackEmpty(Stack* stack);  // Verifica se a pilha está vazia
int isStackFull(Stack* stack);  // Verifica se a pilha está cheia
void push(Stack* stack, int item);  // Insere um elemento no topo da pilha
int pop(Stack* stack);  // Remove e retorna o elemento do topo da pilha

#endif  // STACK_H