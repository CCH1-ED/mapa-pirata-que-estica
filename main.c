#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

// Estrutura de um nó de lista de adjacência
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;




// Função para criar um novo nó de lista de adjacência
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}


// Função para adicionar uma aresta ao grafo direcionado
void addEdge(Node** graph, int src, int dest) {
    // Adicionar uma aresta do src para o dest
    Node* newNode = createNode(dest);
    newNode->next = graph[src]; 
    graph[src] = newNode;

}

// função para criar as listas adjascentes do grafo
void create_graph(Node** graph, char** map, int num_rows, int num_col){
    for (int i = 0; i < num_rows*num_col; i++){
        graph[i] = NULL;
    }
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_col; j++) {
            if (map[i][j] == '.') {
                // Verificar as posições vizinhas
                if (i > 0 && map[i - 1][j] == '.')
                    addEdge(graph, i * num_col + j, (i - 1) * num_col + j);
                if (i < num_rows - 1 && map[i + 1][j] == '.')
                    addEdge(graph, i * num_col + j, (i + 1) * num_col + j);
                if (j > 0 && map[i][j - 1] == '.')
                    addEdge(graph, i * num_col + j, i * num_col + (j - 1));
                if (j < num_col - 1 && map[i][j + 1] == '.')
                    addEdge(graph, i * num_col + j, i * num_col + (j + 1));
            }
        }
    }
}



// Função auxiliar para explorar as células adjacentes em uma DFS
void DFSUtil(Node** graph, int v, int* visited, int* regionSize) {
    visited[v] = 1;
    Node* temp = graph[v];
    while (temp) {
        int adjVertex = temp->vertex;
        if (visited[adjVertex] == 0) {
            DFSUtil(graph, adjVertex, visited, regionSize);
            (*regionSize)++;
        }
        temp = temp->next;
    }
}



// Função para calcular o número de regiões e a área da maior região no mapa
void calculateRegions(Node** graph, int numVertices, int* visited, int* numRegions, int* maxRegionSize) {
    
    for (int i = 0; i < numVertices; i++) {
        int regionSize = 0;
        if (visited[i] == 0) {
            regionSize = 1;
            DFSUtil(graph, i, visited, &regionSize);
            if (regionSize > *maxRegionSize)
                *maxRegionSize = regionSize;
            (*numRegions)++;
        }
    }
    free(visited);
}


// Função para calcular o menor número de passos necessários para ir de uma posição para outra
int calculateShortestPath(Node** graph, int startVertex, int endVertex, int numVertices) {
    if (startVertex == endVertex)
        return 0;

    int* visited = (int*)malloc(numVertices * sizeof(int));
    int* distances = (int*)malloc(numVertices * sizeof(int));
    int i;
    for (i = 0; i < numVertices; i++) {
        visited[i] = 0;
        distances[i] = -1;
    }

    Queue* queue = createQueue(numVertices);
    visited[startVertex] = 1;
    distances[startVertex] = 0;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        Node* temp = graph[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {  
                visited[adjVertex] = 1;
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
    return -1; // não há caminho entre as posições
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


// Função para liberar a memória alocada para as listas adjascentes do grafo
void freeGraph(Node** graph, int num_rows, int num_col){
    for (int i = 0; i < num_rows * num_col; i++) {
        Node* temp = graph[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
}



int main(){
    int num_col, num_rows;
    scanf("%d %d",&num_col, &num_rows); //lê o numero de linhas e colunas do mapa

    // aloca o espaço de memória para o mapa
    char** map = (char**)malloc(num_rows * sizeof(char*));
    for (int i = 0; i < num_rows; i++)
        map[i] = (char*)malloc(num_col * sizeof(char));

    // lê os valores do mapa
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_col; j++)
            scanf(" %c", &map[i][j]);
    }

    // Cria um vetor de listas para o grafo
    Node** graph = (Node**)malloc(sizeof(Node*)*(num_rows * num_col));
    create_graph(graph, map, num_rows, num_col);


    // Processar os comandos
    char command[10];
    scanf("%s", &command);
    while (strcmp(command, "F")!=0) {
        if (strcmp(command, "regioes")==0)  { //regioes
            int* visited = (int*)malloc((num_rows * num_col) * sizeof(int));
            for (int i = 0; i < num_rows*num_col; i++) { // deixa todos como não visitados
                visited[i] = 0;
            }
            for (int i = 0; i < num_rows; i++) { // coloca os x como vizitados para não contar com eles
                for (int j = 0;j<num_col; j++) {
                    if(map[i][j]=='x'){
                        visited[i*num_col+j] = 1;
                    }
                }
            }
            int numRegions = 0, maxRegionSize = 0;
            calculateRegions(graph, num_rows * num_col, visited, &numRegions, &maxRegionSize);
            printf("%d regioes; a maior tem area %d\n", numRegions, maxRegionSize);
        } 


        else if (strcmp(command, "cam")==0) { //cam
            int i1, j1, i2, j2;
            scanf("%d %d %d %d", &i1, &j1, &i2, &j2); 
            int startVertex = i1 * num_col + j1; // posição na lista de adjascencia
            int endVertex = i2 * num_col + j2; // posição na lista de adjascencia
            int shortestPath = calculateShortestPath(graph, startVertex, endVertex, num_rows * num_col);
            if (shortestPath == -1)
                printf("Nao ha caminho de (%d,%d) para (%d,%d)\n", i1, j1, i2, j2);
            else
                printf("De (%d,%d) para (%d,%d) em %d passos\n", i1, j1, i2, j2, shortestPath);
        } 


        else if (strcmp(command,"x")==0) { // altera para x nas coordenadas
            int i, j;
            scanf("%d %d", &i, &j);
            map[i][j] = 'x';
            freeGraph(graph, num_rows, num_col); // libera o grafo
            create_graph(graph, map, num_rows, num_col); // recria o grafo
            printMap(map, num_rows, num_col);
        } 
        else if (strcmp(command, ".")==0) { // altera para . nas coordenadas
            int i, j;
            scanf("%d %d", &i, &j);
            map[i][j] = '.';
            freeGraph(graph, num_rows, num_col); // libera o grafo
            create_graph(graph, map, num_rows, num_col); // recria o grafo
            printMap(map, num_rows, num_col);
        }
        scanf(" %s", &command);
    }

    // Liberar a memória alocada
    freeMap(map, num_rows);
    freeGraph(graph, num_rows, num_col);
    free(map);
    free(graph);


    return 0;
}