#include <stdio.h>
#include <string.h>
#include "input.h"

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int obterInt(int minValor, int maxValor, char *msg, char *err) {
    int valor;
    printf(msg);
    while (scanf(" %d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(err);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


float obterFloat(float minValor, float maxValor, char *msg,char *err) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(err);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


int obterInt_return(int minValor, int maxValor, char *msg, char *err) {
    int valor;
    int ver;
    printf(msg);
    ver=scanf("%d", &valor);
    cleanInputBuffer();
    while (ver != 1 || valor < minValor || valor > maxValor) {
        if(ver==1){
            puts(err);
            printf(msg);
           ver=scanf("%d", &valor);
        }
        if(ver!=1){
            printf(ERRO_RETURN);
            return -1;
        }
        cleanInputBuffer();
    }
    return valor;
}


float obterFloat_return(float minValor, float maxValor, char *msg,char *err) {
    int ver;
    float valor;
    printf(msg);
   ver=scanf("%f", &valor);
   cleanInputBuffer();
    while (ver != 1 || valor < minValor || valor > maxValor) {
        if(ver==1){
            puts(err);
            printf(msg);
           ver=scanf("%f", &valor);
        }
        if(ver!=1){
            printf(ERRO_RETURN);
           return -1;
        }
        cleanInputBuffer();
    }
    return valor;
}

double obterDouble(double minValor, double maxValor, char *msg,char *err) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(err);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


int perg_s_n(char *msg) {
    char valor;
    do{
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    if(valor!='S'&&valor!='s'&&valor!='N'&&valor!='n'){
        printf("Opção Invalida!\n");
    }
    }while(valor!='S'&&valor!='s'&&valor!='N'&&valor!='n');
    if(valor=='S'||valor=='s'){
        return 1;
    }else{
    return (-1);
    }
}


void lerString(char *string, unsigned int tamanho, char *msg) {
printf(msg);
if (fgets(string, tamanho, stdin) != NULL) {
unsigned int len = strlen(string) - 1;
if (string[len] == '\n') {
string[len] = '\0';
} else {
cleanInputBuffer();
}
}
}

