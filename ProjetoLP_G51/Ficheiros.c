
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ficheiros.h"

int conta_linhas(char *file) {
    FILE *fp = fopen(file, "r");
    if(fp!=NULL){
    int count;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            count++;
            
        }
    }
    fclose(fp);
    return count;
    }else{
        return -1;
    }
}
/*
int ver_tipo_ficheiro(char *file) {
    int cont;
    if (file[strlen(file) - 4] == '.') {
        if (file[strlen(file) - 3] == 't' && file[strlen(file) - 2] == 'x' && file[strlen(file) - 1] == 't') {
            return 1;
        } else if (file[strlen(file) - 3] == 'c' && file[strlen(file) - 2] == 's' && file[strlen(file) - 1] == 'v') {
            return 2;
        } else if (file[strlen(file) - 3] == 'b' && file[strlen(file) - 2] == 'i' && file[strlen(file) - 1] == 'n') {
            return 3;
        }
    }
    return 0;

}
    
*/

