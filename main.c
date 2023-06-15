#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

// Estrutura de um nó de lista de adjacência
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Estrutura para representar o grafo
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Função para criar um novo nó de lista de adjacência
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com um número específico de vértices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Função para adicionar uma aresta ao grafo direcionado
void addEdge(Graph* graph, int src, int dest) {
    // Adicionar uma aresta do src para o dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Adicionar uma aresta do dest para o src (grafo não-direcionado)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Função auxiliar para explorar as células adjacentes em uma DFS
void DFSUtil(Graph* graph, int v,int* visited) {
    visited[v] = true;

    Node* temp = graph->adjLists[v];
    while (temp) {
        int adjVertex = temp->vertex;
        if (visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// Função para calcular o número de regiões e a área da maior região no mapa
void calculateRegions(Graph* graph, int numVertices) {
    int* visited = (int*)malloc(numVertices * sizeof(int));
    int i, numRegions = 0, maxRegionSize = 0;

    for (i = 0; i < numVertices; i++)
        visited[i] = false;

    for (i = 0; i < numVertices; i++) {
        if (visited[i]) {
            DFSUtil(graph, i, visited);
            numRegions++;
        }
    }

    printf("%d regioes; a maior tem area %d\n", numRegions, maxRegionSize);
    free(visited);
}

// Função para calcular o menor número de passos necessários para ir de uma posição para outra
int calculateShortestPath(Graph* graph, int startVertex, int endVertex, int numVertices) {
    if (startVertex == endVertex)
        return 0;

int* visited = (int*)malloc(numVertices * sizeof(int));
    int* distances = (int*)malloc(numVertices * sizeof(int));
    int i;
    for (i = 0; i < numVertices; i++) {
        visited[i] = false;
        distances[i] = -1;
    }

    Queue* queue = createQueue(numVertices);
    visited[startVertex] = true;
    distances[startVertex] = 0;
    enqueue(queue, startVertex);

    while (isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (visited[adjVertex]) {
                visited[adjVertex] = true;
                distances[adjVertex] = distances[currentVertex] + 1;
                enqueue(queue, adjVertex);
            }

            if (adjVertex == endVertex) {
                int shortestPath = distances[adjVertex];
                free(visited);
                free(distances);
                free(queue->array);
                free(queue);
                return shortestPath;
            }

            temp = temp->next;
        }
    }

    free(visited);
    free(distances);
    free(queue->array);
    free(queue);
    return -1; // Não há caminho entre as posições
}

// Função para imprimir o mapa atual da caverna
void printMap(char** map, int numRows, int numCols) {
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++)
            printf("%c ", map[i][j]);
        printf("\n");
    }
}

// Função para liberar a memória alocada para o mapa
void freeMap(char** map, int numRows) {
    int i;
    for (i = 0; i < numRows; i++)
        free(map[i]);
    free(map);
}

int main() {
    int numRows, numCols;
    printf("Digite o numero de linhas: ");
    scanf("%d", &numRows);
    printf("Digite o numero de colunas: ");
    scanf("%d", &numCols);

    // Alocar memória para o mapa
    char** map = (char**)malloc(numRows * sizeof(char*));
    int i, j;
    for (i = 0; i < numRows; i++)
        map[i] = (char*)malloc(numCols * sizeof(char));

    // Ler o mapa do usuário
    printf("Digite o mapa da caverna:\n");
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++)
            scanf(" %c", &map[i][j]);
    }

    // Criar o grafo a partir do mapa
    Graph* graph = createGraph(numRows * numCols);

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            if (map[i][j] == '.') {
                // Verificar as posições vizinhas
                if (i > 0 && map[i - 1][j] == '.')
                    addEdge(graph, i * numCols + j, (i - 1) * numCols + j);
                if (i < numRows - 1 && map[i + 1][j] == '.')
                    addEdge(graph, i * numCols + j, (i + 1) * numCols + j);
                if (j > 0 && map[i][j - 1] == '.')
                    addEdge(graph, i * numCols + j, i * numCols + (j - 1));
                if (j < numCols - 1 && map[i][j + 1] == '.')
                    addEdge(graph, i * numCols + j, i * numCols + (j + 1));
            }
        }
    }

    // Processar os comandos
    char command[10];
    while (command[0] != 'F') {
        printf("Digite um comando (regioes, cam, x, ., F): ");
        scanf(" %c\n", &command);

        if (strcmp(command, "regioes"))  {
            calculateRegions(graph, numRows * numCols);
        } else if (strcmp(command, "cam")) {
            int i1, j1, i2, j2;
            printf("Digite as posições i1, j1, i2, j2: ");
            scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
            int startVertex = i1 * numCols + j1;
            int endVertex = i2 * numCols + j2;
            int shortestPath = calculateShortestPath(graph, startVertex, endVertex, numRows * numCols);
            if (shortestPath == -1)
                printf("Não existe caminho entre as posições.\n");
            else
                printf("Menor número de passos necessários: %d\n", shortestPath);
        } else if (command[0] == 'x') {
            int i, j;
            printf("Digite a posição i, j: ");
            scanf("%d %d", &i, &j);
            map[i][j] = 'x';
            printf("Mapa atual:\n");
            printMap(map, numRows, numCols);
        } else if (command[0] == '.') {
            int i, j;
            printf("Digite a posição i, j: ");
            scanf("%d %d", &i, &j);
            map[i][j] = '.';
            printf("Mapa atual:\n");
            printMap(map, numRows, numCols);
        }
    }

    // Liberar a memória alocada
    freeMap(map, numRows);
    for (i = 0; i < numRows * numCols; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph);

    return 0;
}
