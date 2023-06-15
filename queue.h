#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue{
    int capacity;  // Capacidade máxima da fila
    int front;  // Índice do elemento frontal da fila
    int rear;  // Índice do elemento traseiro da fila
    int size;  // Tamanho atual da fila
    int* array;  // Array para armazenar os elementos da fila
} Queue;

Queue* createQueue(int capacity);  // Cria uma nova fila com a capacidade especificada
void destroyQueue(Queue* queue);  // Libera a memória alocada para a fila
int isEmpty(Queue* queue);  // Verifica se a fila está vazia
int isQueueFull(Queue* queue);  // Verifica se a fila está cheia
void enqueue(Queue* queue, int item);  // Insere um elemento no final da fila
int dequeue(Queue* queue);  // Remove e retorna o elemento do início da fila

#endif  // QUEUE_H
