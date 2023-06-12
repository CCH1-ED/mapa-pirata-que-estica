#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** create_matrix(int line, int colunm){
    char ** Line = (char **)malloc(sizeof(char *)*line);
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

int main(){
    int line, colunm;
    scanf("%d %d", &line, &colunm);
    char ** matrix = create_matrix(line, colunm);

    char command[10];
    do{
        scanf("%s", &command);
        
    }while (command != 'F');
    
    return 0;
}