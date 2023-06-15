#include "queue.h"
#include <stdlib.h>

// Função para criar uma fila
Queue *createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

// Função para verificar se a fila está cheia
int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

// Função para adicionar um elemento à fila
void enqueue(Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Função para remover um elemento da fila
int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}