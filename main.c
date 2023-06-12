#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char create_matrix(int line,int colunm){
    char matrix[line][colunm];
    for(int i; i < line;i++){
        for(int j; j < colunm;j++){
            scanf("%c", &matrix[i][j]);
        }
    }
}

int main(){
    int line, colunm;
    scanf("%d %d", &line, &colunm);
    create_matrix(line, colunm);

    char command[10];
    do{
        scanf("%s", &command);
        if
    }while (command != 'F');
    
    return 0;
}