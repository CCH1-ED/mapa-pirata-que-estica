#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int line, column;
    char command[10];
    scanf("%d %d \n", &line, &column);
    while(command != 'F'){
        scanf("%s", &command);
    }
    return 0;
}