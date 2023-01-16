#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tabelas_IRS.h"
#include "input.h"
#include "funcionarios.h"
#include "ficheiros.h"

int carregar_tab_IRS(Tab_IRS *Tabs, char *file) {
    if (Tabs->tam != 0) {
        free(Tabs->Linha);
    }
    FILE *fp;
    strcat(file,FILE_TYPE_CSV);
        fp = fopen(file, "r");
        if (fp != NULL) {
            Tabs->cont = conta_linhas(file) - 1;
            fscanf(fp, "Valor:;Taxa D0:;Taxa D1:;Taxa D2:;Taxa D3:;Taxa D4:;Taxa D5+:\n");
            if (Tabs->cont > 0) {
                linha *temp = (linha*) malloc((Tabs->cont)*(sizeof (linha)));
                if (temp != NULL) {
                    Tabs->Linha = temp;
                    for (int i = 0; i < Tabs->cont; i++) {
                        fscanf(fp, "%f;%f;%f;%f;%f;%f;%f\n", &Tabs->Linha[i].col[0], &Tabs->Linha[i].col[1], &Tabs->Linha[i].col[2], &Tabs->Linha[i].col[3], &Tabs->Linha[i].col[4], &Tabs->Linha[i].col[5], &Tabs->Linha[i].col[6]);
                    }
                    Tabs->tam = Tabs->cont;
                }
                fclose(fp);
                return 1;
            } else {
                printf(ERR_FILE_N_CARR, file);
                fclose(fp);
                return 0;
            }
        } else {
            printf(ERR_FILE_N_EXISTE, file);
            return 0;
}
 }

void print_tab(Tab_IRS Tabs) {
    if (Tabs.cont != 0) {
        printf(" L|  Valor    | D0  |  D1 |  D2 |  D3 |  D4 | D5+\n");
        for (int i = 0; i < Tabs.cont; i++) {
            if (i != (Tabs.cont - 1)) {
                printf("[%d]Até %.1f€  %.1f%%  %.1f%%  %.1f%%  %.1f%%  %.1f%%  %.1f%%\n", i + 1, Tabs.Linha[i].col[0], Tabs.Linha[i].col[1], Tabs.Linha[i].col[2], Tabs.Linha[i].col[3], Tabs.Linha[i].col[4], Tabs.Linha[i].col[5], Tabs.Linha[i].col[6]);
            } else {
                printf("[%d]Sup. a %.1f€  %.1f%%  %.1f%%  %.1f%%  %.1f%%  %.1f%%  %.1f%%\n", i + 1, Tabs.Linha[i].col[0], Tabs.Linha[i].col[1], Tabs.Linha[i].col[2], Tabs.Linha[i].col[3], Tabs.Linha[i].col[4], Tabs.Linha[i].col[5], Tabs.Linha[i].col[6]);
            }
        }
    }
}

void guardar_tab(Tab_IRS *Tabs, char *file) {
    FILE *fp;
    strcat(file,FILE_TYPE_CSV);
        if (Tabs->cont > 0) { 
            if(conta_linhas(file)>2){
            if(perg_s_n("Deseja apagar a informação no ficheiro(S/N)?")!=1){
                return;
            }
        }
            fp = fopen(file, "w");
            if (fp != NULL) {
            fprintf(fp, "Valor:;Taxa D0:;Taxa D1:;Taxa D2:;Taxa D3:;Taxa D4:;Taxa D5+:\n");
            for (int i = 0; i < Tabs->cont; i++) {
                fprintf(fp, "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\n", Tabs->Linha[i].col[0], Tabs->Linha[i].col[1], Tabs->Linha[i].col[2], Tabs->Linha[i].col[3], Tabs->Linha[i].col[4], Tabs->Linha[i].col[5], Tabs->Linha[i].col[6]);
            }
            fclose(fp);
            printf(MSG_INFO_GRAV, file);
        } else {
            printf(ERR_FILE_N_EXISTE, file);
        }
    } else {
        printf(ERR_FILE_N_GRAV, file);
    }
}

void expandir_linhas(Tab_IRS *Tabs) {
    if (Tabs->cont == 0) {
        Tabs->Linha = (linha*) malloc(sizeof (linha));
    }
    linha *temp = (linha*) realloc(Tabs->Linha, (sizeof (linha)* (Tabs->tam + 2)));
    if (temp != NULL) {
        Tabs->tam += 2;
        Tabs->Linha = temp;
    }
}

void apagar_linha(Tab_IRS *Tabs) {
    int ver_ult_linha = 0;
    if (Tabs->cont != 0) {
        int nlinha = obterInt(MIN_LINHA, Tabs->cont + 1, MSG_OBT_NLINHA_APG, VAL_INV_LINHA);
        swap_linhas_eliminar(Tabs, nlinha);
        Tabs->cont--;
        if (Tabs->cont >= 2) {
            ver_vals(Tabs);
        }
        printf(MSG_TAB_IRS_LINHA_APG, nlinha);
    } else {
        printf(ERR_TAB_IRS_VAZIA);
    }
}

void ver_vals(Tab_IRS *Tabs) {
    int ver;
    int nlinha;
    if (Tabs->cont >= 2) {
        if (Tabs->Linha[Tabs->cont - 1].col[0] != Tabs->Linha[Tabs->cont - 2].col[0]) {
            printf(ERR_ULT_LINHA);
            printf("[%d]Até:%.1f€\n", Tabs->cont - 1, Tabs->Linha[Tabs->cont - 2].col[0]);
            printf("[%d]Superior a:%.1f€\n", Tabs->cont, Tabs->Linha[Tabs->cont - 1].col[0]);
            ver = perg_s_n(MSG_CONT_ERR_ULT_LINHA);
            if (ver == 1) {
                nlinha = obterInt(Tabs->cont - 1, Tabs->cont, MSG_CONT_ERR_ULT_LINHA_OBT_NLINHA, VAL_INV_LINHA);
                if (nlinha == Tabs->cont) {
                    printf(MSG_VAL_IGUAL, Tabs->Linha[Tabs->cont - 2].col[0], Tabs->Linha[Tabs->cont - 1].col[0]);
                    Tabs->Linha[Tabs->cont - 2].col[0] = Tabs->Linha[Tabs->cont - 1].col[0];
                } else if (nlinha == Tabs->cont - 1) {
                    printf(MSG_VAL_IGUAL, Tabs->Linha[Tabs->cont - 1].col[0], Tabs->Linha[Tabs->cont - 2].col[0]);
                    Tabs->Linha[Tabs->cont - 1].col[0] = Tabs->Linha[Tabs->cont - 2].col[0];
                }
            }
        }
    }
}

void alt_linha(Tab_IRS *Tabs) {
    if (Tabs->cont != 0) {
        linha min;
        linha max;
        int nlinha = obterInt_return(MIN_LINHA, Tabs->cont, MSG_OBT_NLINHA_ALT, VAL_INV_LINHA);
        if (nlinha == -1) {
            return;
        }
        int opc;
        int ver = 1;
        load_min_max(&min, &max, *Tabs, nlinha);
        do {
            printf("Escolha o que deseja alterar na linha %d:\n", nlinha);
            if (nlinha + 1 != Tabs->cont) {
                printf("1.Valor: Até %.1f€\t", Tabs->Linha[nlinha - 1].col[0]);
            } else {
                printf("1.Valor: Sup a %.1f€\t", Tabs->Linha[nlinha - 1].col[0]);
            }
            printf("2.D0:%.1f%%\n", Tabs->Linha[nlinha - 1].col[1]);
            printf("3.D1:%.1f%%\t\t", Tabs->Linha[nlinha - 1].col[2]);
            printf("4.D2:%.1f%%\n", Tabs->Linha[nlinha - 1].col[3]);
            printf("5.D3:%.1f%%\t\t", Tabs->Linha[nlinha - 1].col[4]);
            printf("6.D4:%.1f%%\n", Tabs->Linha[nlinha - 1].col[5]);
            printf("7.D5+:%.1f%%\t\t", Tabs->Linha[nlinha - 1].col[6]);
            printf("8.Sair\n");
            opc = obterInt(VAL_MIN_OPC_TAB_IRS, VAL_MAX_OPC_TAB_IRS, "", OPC_INV_TAB_IRS);
            switch (opc) {
                case 1:
                    if (nlinha + 1 != Tabs->cont) {
                        Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    } else {
                        Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_SUP, VAL_INV_VALOR);
                    }
                    break;
                case 2:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 3:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 4:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 5:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 6:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 7:
                    Tabs->Linha[nlinha - 1].col[opc - 1] = obterFloat(min.col[opc - 1], max.col[opc - 1], MSG_OBT_VAL_ATE, VAL_INV_VALOR);
                    break;
                case 8:
                    break;
                default:
                    puts(OPC_INV_TAB_IRS);
                    break;

            }
        } while (opc != 8);
        if (Tabs->cont >= 2 && (nlinha == Tabs->cont || nlinha == Tabs->cont - 1)) {
            ver_vals(Tabs);
        }
        printf(MSG_TAB_IRS_LINHA_ALT, nlinha);
    } else {
        printf(ERR_TAB_IRS_VAZIA);
    }
}

void criar_linha(Tab_IRS *Tabs) {
    linha temp, max, min;
    char msg[MAX_STRING];
    if (Tabs->tam == Tabs->cont) {
        expandir_linhas(Tabs);
    }
    int nlinha = obterInt(MIN_LINHA, Tabs->cont + 1, MSG_OBT_NLINHA_CRIAR, VAL_INV_LINHA);
    if (nlinha == -1) {
        return;
    }
    if (nlinha != Tabs->cont + 1) {
        swap_linhas_criar(Tabs, nlinha);
    }
    load_min_max(&min, &max, *Tabs, nlinha - 1);
    for (int i = 0; i < COLUNAS; i++) {
        if (i == 0) {
            if (nlinha != Tabs->cont + 1) {
                strcpy(msg, MSG_OBT_VAL_ATE);
            } else {
                strcpy(msg, MSG_OBT_VAL_SUP);
            }
        } else if (i == 1) {
            strcpy(msg, MSG_OBT_PORC_D0);
        } else if (i == 2) {
            strcpy(msg, MSG_OBT_PORC_D1);
        } else if (i == 3) {
            strcpy(msg, MSG_OBT_PORC_D2);
        } else if (i == 4) {
            strcpy(msg, MSG_OBT_PORC_D3);
        } else if (i == 5) {
            strcpy(msg, MSG_OBT_PORC_D4);
        } else if (i == 6) {
            strcpy(msg, MSG_OBT_PORC_D5);
        }
        temp.col[i] = obterFloat(min.col[i], max.col[i], msg, VAL_INV_VALOR);
        Tabs->Linha[nlinha - 1].col[i] = temp.col[i];
    }
    printf(MSG_TAB_IRS_LINHA_CRIADA, nlinha);
    Tabs->cont++;
    if (Tabs->cont >= 2 && (nlinha == Tabs->cont || nlinha == Tabs->cont - 1)) {
        ver_vals(Tabs);
    }
}

void load_min_max(linha *min, linha *max, Tab_IRS Tabs, int nlinha) {
    for (int i = 0; i < COLUNAS; i++) {
        if (nlinha != Tabs.cont && nlinha != MIN_LINHA) {
            min->col[i] = Tabs.Linha[nlinha - 1].col[i];
            max->col[i] = Tabs.Linha[nlinha + 1].col[i];
        } else if (nlinha == MIN_LINHA && nlinha != Tabs.cont) {
            min->col[i] = MIN_VAL_IRS;
            max->col[i] = Tabs.Linha[nlinha + 1].col[i];
        } else if (nlinha == MIN_LINHA && nlinha == Tabs.cont) {
            min->col[i] = MIN_VAL_IRS;
            if (i == 0) {
                max->col[i] = MAX_VAL_IRS;
            } else {
                max->col[i] = MAX_TAX;
            }
        } else if (nlinha != MIN_LINHA && nlinha == Tabs.cont) {
            min->col[i] = Tabs.Linha[nlinha - 1].col[i];
            if (i == 0) {
                max->col[i] = MAX_VAL_IRS;
            } else {
                max->col[i] = MAX_TAX;
            }
        }
    }
}

void swap_linhas_criar(Tab_IRS *Tabs, int linha) {
    for (int i = Tabs->cont; i > linha - 1; i--) {
        for (int j = 0; j < COLUNAS; j++) {
            Tabs->Linha[i].col[j] = Tabs->Linha[i - 1].col[j];
        }
    }
}

void swap_linhas_eliminar(Tab_IRS *Tabs, int linha) {
    for (int i = linha - 1; i < Tabs->cont; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            Tabs->Linha[i].col[j] = Tabs->Linha[i - 1].col[j];
        }
    }
}