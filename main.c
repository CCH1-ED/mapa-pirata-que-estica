#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo{
    int vertice;
    struct Nodo *next;
}Nodo;


char **create_matrix(int line, int colunm){
    char **Line = (char **)malloc(sizeof(char *)*line);
    for(int i; i < line;i++){
        Line[i] = (char *)malloc(sizeof(char)* colunm);
    }
    for(int i; i < line;i++){
        for(int j; j < colunm;j++){
            scanf(" %c", &Line[i][j]);
        }
    }
    return Line;
}

Nodo **adjacency_list(int all_vertice,int line, int colunm,char **matrix){
    Nodo ** adjacency = (Nodo **)malloc(sizeof(Nodo *)*all_vertice);
    char vertice;
    for(int i; i < line;i++){
        for(int j; j < colunm;j++){
            vertice = matrix[i][j];
            Nodo *visitable();//sei la pularei de um predio 
        }
    }
}


Nodo *visitable(Nodo *head,int value){
    if(head == NULL){
        Nodo *new = (Nodo*)malloc(sizeof(Nodo));
        new->vertice = value;
        new->next = NULL;
        return new;
    }
    else
        head;
}

int main(){
    int line, colunm;
    scanf("%d %d", &line, &colunm);
    Nodo *head = NULL;
    char **matrix = create_matrix(line, colunm);
    Nodo **adjacency_list(line, colunm, matrix);

    char command[10];
    do{
        scanf("%s", &command);
    }while (command != 'F');
    
    return 0;
}