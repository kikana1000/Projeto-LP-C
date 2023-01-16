#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionarios.h"
#include "SegSoc.h"
#include "input.h"
#include "ficheiros.h"


void expandir_SegSoc(Tab_SS *segsoc) {
    Linha_segsoc *temp = (Linha_segsoc*) realloc(segsoc->linha, sizeof (Linha_segsoc)* (segsoc->tam + 2));
    if (temp != NULL) {
        segsoc->tam += 2;
        segsoc->linha = temp;
    }
}


void SegSoc_add(Tab_SS *segsoc) {
    printf(MSG_SEGSOC_ADD);

    if (segsoc->cont == segsoc->tam) {
        expandir_SegSoc(segsoc);
    }
    int ver = perg_s_n(MSG_CARGO_FUNCAO);
    int n=segsoc->cont;
    if (segsoc->cont == 0) {
        n=1;
    }
        do {
        if (ver == -1) {
            segsoc->linha[segsoc->cont].tipo.ativo = Ativo;
            segsoc->linha[segsoc->cont].tipo.cargo = obterInt(MIN_TIPO, MAX_TIPO, MSG_OBT_TIPO, VAL_INV);
        } else {
            segsoc->linha[segsoc->cont].tipo.ativo = Nao_ativo;
            lerString(segsoc->linha[segsoc->cont].funcao, MAX_STRING_SS, MSG_OBT_FUNCAO_SS);
        }
        } while (ver_criterio(*segsoc, n+1,n+1) != 0);
    segsoc->linha[segsoc->cont].entempregadora = obterFloat(MIN_PORC_TAB_SS, MAX_PORC_TAB_SS, MSG_OBT_VALOR_ENTEMPREGADORA, VAL_INV);
    segsoc->linha[segsoc->cont].trabalhador = obterFloat(MIN_PORC_TAB_SS, MAX_PORC_TAB_SS, MSG_OBT_VALOR_TRABALHADOR, VAL_INV);
    segsoc->linha[segsoc->cont].total = segsoc->linha[segsoc->cont].trabalhador + segsoc->linha[segsoc->cont].entempregadora;
    segsoc->cont += 1;
    printf(MSG_CRIADO_TAB_SS);
}

int carregar_SegSoc(Tab_SS *segsoc, char *file) {
    if (segsoc->tam != 0) {
        free(segsoc->linha);
    }
    FILE *fp;
    strcat(file,FILE_TYPE_BIN);
    fp = fopen(file, "rb");
    if (fp != NULL) {
        fread(&segsoc->cont, sizeof (int), 1, fp);
        if (segsoc->cont > 0) {
            segsoc->linha = (Linha_segsoc*) malloc(segsoc->cont * sizeof (Linha_segsoc));
            fread(segsoc->linha, sizeof (Linha_segsoc), segsoc->cont, fp);
            segsoc->tam = segsoc->cont;
            printf(MSG_SEGSOC_CARR, file);
             fclose(fp);
            return 1;
        } else {
            fclose(fp);
            printf(MSG_SEGSOC_N_CARR, file);
            return 0;
        }
    } else {
        printf(ERR_FILE_N_EXISTE_TAB_SS);
        return 0;
    }
}

void guardar_SegSoc(Tab_SS *segsoc, char *file) {
    
    if (segsoc->cont != 0) {
        strcat(file,FILE_TYPE_BIN);
        FILE *fp = fopen(file, "wb");
        if (fp != NULL) {
            fwrite(&segsoc->cont, sizeof (int), 1, fp);
            fwrite(segsoc->linha, sizeof (Linha_segsoc), segsoc->cont, fp);
            printf(MSG_GUARDAR_TAB_SS, file);
            fclose(fp);
        }
    } else {
        printf(ERR_VAZIA_GUARDAR_TAB_SS, file);
    }
}

void SegSoc_remove(Tab_SS *segsoc) {
    if (segsoc->cont != 0) {
        int nlinha = obterInt(MIN_LINHA_SEGSOC, segsoc->cont, MSG_OBT_NLINHA_REM , VAL_INV);
        if (segsoc->cont != 1) {
            for (int i = nlinha - 1; i < segsoc->cont; i++) {
                segsoc->linha[i].tipo.ativo = segsoc->linha[i + 1].tipo.ativo;
                segsoc->linha[i].tipo.cargo = segsoc->linha[i + 1].tipo.cargo;
                strcpy(segsoc->linha[i].funcao, segsoc->linha[i + 1].funcao);
                segsoc->linha[i].entempregadora = segsoc->linha[i + 1].entempregadora;
                segsoc->linha[i].trabalhador = segsoc->linha[i + 1].trabalhador;
                segsoc->linha[i].total = segsoc->linha[i + 1].total;
            }
        } else if (segsoc->cont == 1) {
            segsoc->linha[nlinha - 1].tipo.ativo = 1;
            segsoc->linha[nlinha - 1].tipo.cargo = 0;
            strcpy(segsoc->linha[nlinha - 1].funcao, "");
            segsoc->linha[nlinha - 1].entempregadora = 0;
            segsoc->linha[nlinha - 1].trabalhador = 0;
            segsoc->linha[nlinha - 1].total = 0;
        }
        segsoc->cont -= 1;
        printf(MSG_REMOV_TAB_SS);
    } else {
        printf(ERR_SEGSOC_VAZIA_LISTA);
    }
}

void SegSoc_edit(Tab_SS *segsoc) {
    int ver;
    if (segsoc->cont != 0) {
        int nlinha = obterInt(MIN_LINHA_SEGSOC, segsoc->cont, MSG_OBT_NLINHA_EDIT, VAL_INV);
        ver = perg_s_n(MSG_EDIT_TIPO);
        if (ver != -1) {
            do {
                ver = perg_s_n(MSG_CARGO_FUNCAO);
                if (ver == -1) {
                    segsoc->linha[nlinha - 1].tipo.ativo = Ativo;
                    segsoc->linha[nlinha - 1].tipo.cargo = obterInt(MIN_TIPO, MAX_TIPO, MSG_OBT_TIPO, VAL_INV);
                } else {
                    segsoc->linha[nlinha - 1].tipo.ativo = Nao_ativo;
                    lerString(segsoc->linha[nlinha - 1].funcao, MAX_STRING_SS, MSG_OBT_FUNCAO_SS);
                }
            } while (ver_criterio(*segsoc, nlinha,segsoc->cont) != 0);
        }
        ver = perg_s_n(MSG_EDIT_ENTEMPREGADORA);
        if (ver != -1) {
            segsoc->linha[nlinha - 1].entempregadora = obterFloat(MIN_PORC_TAB_SS, MAX_PORC_TAB_SS, MSG_OBT_VALOR_ENTEMPREGADORA, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_TRABALHADOR);
        if (ver != -1) {
            segsoc->linha[nlinha - 1].trabalhador = obterFloat(MIN_PORC_TAB_SS, MAX_PORC_TAB_SS, MSG_OBT_VALOR_TRABALHADOR, VAL_INV);
        }
        segsoc->linha[nlinha - 1].total = segsoc->linha[nlinha - 1].entempregadora + segsoc->linha[nlinha - 1].trabalhador;
        printf(MSG_EDIT_LINHA);
    } else {
        printf(ERR_N_EXISTE_LINHAS);
    }
}

void SegSoc_list(Tab_SS segsoc) {
    if (segsoc.cont != 0) {
        printf("\t - Taxas Contributivas -\n");
        printf("  L |\t\t\t\t\tTrabalhadores por conta de outrem\t\t  | Entidade Empregadora | Trabalhador | Global\n");
        for (int i = 0; i < segsoc.cont; i++) {
            printf(" [%d]", i + 1);
            if (segsoc.linha[i].tipo.ativo == Ativo) {
                if (segsoc.linha[i].tipo.cargo == Funcionario) {
                    printf("   \t\t\t\t\tFuncionário em geral\t\t\t\t\t");
                } else if (segsoc.linha[i].tipo.cargo == Chefe) {
                    printf("\t\t\tMembros dos órgãos estatutários das pessoas coletivas em geral\t\t");
                } else {
                    printf("    Membros dos órgãos estatutários das pessoas coletivas sejam gerentes ou admistradores\t");
                }
            } else {
                printf("\t\t\t\t\t\t %s \t\t\t\t\t  ", segsoc.linha[i].funcao);
            }
            printf("  %.2f%%\t", segsoc.linha[i].entempregadora);
            printf("\t%.2f%%\t", segsoc.linha[i].trabalhador);
            printf("\t%.2f%%\t\n", segsoc.linha[i].total);
        }
    }
}

int ver_criterio(Tab_SS segsoc,int nlinha,int cont) {
    int i;
    for (i = 0; i < cont; i++) {
        if(nlinha - 1!=i){
        if (segsoc.linha[i].tipo.ativo == segsoc.linha[nlinha - 1].tipo.ativo) {
            if (segsoc.linha[i].tipo.ativo == Ativo) {
                if (segsoc.linha[i].tipo.cargo == segsoc.linha[nlinha - 1].tipo.cargo) {
                    printf(ERR_EXISTE_CRIT);
                    return 1;
                }
            } else {
                int j;
                int cont = 0;
                if(strlen(segsoc.linha[i].funcao)==strlen(segsoc.linha[nlinha - 1].funcao)){
                for (j = 0; j < strlen(segsoc.linha[i].funcao); j++) {
                    if (segsoc.linha[nlinha - 1].funcao[j] == segsoc.linha[i].funcao[j]) {
                        cont++;
                    }
                }
                if (cont == strlen(segsoc.linha[i].funcao)) {
                    printf(ERR_EXISTE_CRIT);
                    return 1;
                }
            }
            }
        }
    }
    }
    return 0;
}