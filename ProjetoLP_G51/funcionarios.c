#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionarios.h"
#include "input.h"
#include "Ficheiros.h"
 
void expandir_Funcs(Funcs *funcs) {
    Func *temp =  (Func*) realloc(funcs->func, sizeof (Func)* (funcs->tam + 2));
    if (temp != NULL) {   
        funcs->tam += 2;
        funcs->func = temp;
    }
}

void func_add(Funcs *funcs) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    Func temp;
    printf(MSG_FUNC_ADD);
    if (funcs->cont == funcs->tam) {
        expandir_Funcs(funcs);
    }
    int cod = obterInt(MIN_COD, MAX_COD, MSG_OBT_COD, VAL_INV);
    int ver = func_search(funcs, cod);
    if (ver == -1 || funcs->cont == 0) {
        funcs->func[funcs->cont].cod = cod;
        lerString(funcs->func[funcs->cont].nome, MAX_STRING, MSG_OBT_NOME);
        lerString(funcs->func[funcs->cont].funcao,MAX_STRING,MSG_OBT_FUNCAO);
        funcs->func[funcs->cont].cargo = obterInt(MIN_CARG, MAX_CARG, MSG_OBT_CARGO, VAL_INV);
        do {
            printf(MSG_OBT_DATA_NASC);
            funcs->func[funcs->cont].data_nasc.dia = obterInt(MIN_DIA, MAX_DIA, MSG_OBT_DATA_DIA, VAL_INV);
            funcs->func[funcs->cont].data_nasc.mes = obterInt(MIN_MES, MAX_MES, MSG_OBT_DATA_MES, VAL_INV);
            funcs->func[funcs->cont].data_nasc.ano = obterInt(MIN_ANO, MAX_ANO, MSG_OBT_DATA_ANO, VAL_INV);
            if(perg_s_n(MSG_CALC_AUTO_NASC)!=1){
            printf(MSG_OBT_DATA_ENTR);
            funcs->func[funcs->cont].data_entr.dia = obterInt(MIN_DIA, MAX_DIA, MSG_OBT_DATA_DIA, VAL_INV);
            funcs->func[funcs->cont].data_entr.mes = obterInt(MIN_MES, MAX_MES, MSG_OBT_DATA_MES, VAL_INV);
            funcs->func[funcs->cont].data_entr.ano = obterInt(MIN_ANO, MAX_ANO, MSG_OBT_DATA_ANO, VAL_INV);
            }else{
                funcs->func[funcs->cont].data_entr.dia = tm->tm_mday;
                funcs->func[funcs->cont].data_entr.mes = tm->tm_mon +1;
                funcs->func[funcs->cont].data_entr.ano = tm->tm_year+1900;
            }
        } while (ver_data((funcs->func[funcs->cont].data_nasc), (funcs->func[funcs->cont].data_entr),IDADE_MINIMA, ERR_DATA_ENTR) != 1);
        calcular_idades(&funcs->func[funcs->cont]);
        do {
            funcs->func[funcs->cont].tel=obterInt(MIN_TEL,MAX_TEL,MSG_OBT_TEL,VAL_INV);
        } while (ver_tel(funcs->func[funcs->cont].tel, VAL_INV) == -1);
        funcs->func[funcs->cont].dep = obterInt(MIN_DEP, MAX_DEP, MSG_OBT_DEP, VAL_INV);
        int estcivil = obterInt(MIN_ESTCIV, MAX_ESTCIV, MSG_OBT_ESTCIVIL, VAL_INV);
        if (estcivil == 2 && perg_s_n(PERG_ESTCIV_TITULAR) == 1) {
            funcs->func[funcs->cont].est_civil = Casado_2;
        } else {
            funcs->func[funcs->cont].est_civil = estcivil;
        }
        funcs->func[funcs->cont].val_hor = obterFloat(MIN_VAL, MAX_VAL, MSG_OBT_VALOR_HORA, VAL_INV);
        funcs->func[funcs->cont].val_sub = obterFloat(MIN_VAL, MAX_VAL, MSG_OBT_VALOR_SUB, VAL_INV);
        funcs->func[funcs->cont].del = Ativo;
        funcs->cont += 1;
        printf(MSG_CRIADO);
    } else {
        printf(ERR_EXISTE);
    }
}

int ver_data(Data data_menor, Data data_maior,int anos_minimos, char *err) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int calculo_minimo = anos_minimos * 365;
    int calculo_data_menor=365*data_menor.ano+30*data_menor.mes+data_menor.dia;
    int calculo_data_maior=365*data_maior.ano+30*data_maior.mes+data_maior.dia;
    if((calculo_data_maior-calculo_data_menor)<calculo_minimo){
    puts(err);
    return -1;
    }
    return 1;
}

void func_remove(Funcs *funcs) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int cod = obterInt(MIN_COD, MAX_COD, MSG_OBT_REM_COD, VAL_INV);
    int i = func_search(funcs, cod);
    int ver;
    if (i != -1) {
        funcs->func[i].del = Nao_ativo;
        ver=perg_s_n(MSG_CALC_AUTO_SAIDA);
        if(ver!=-1){
        funcs->func[i].data_saida.dia = tm->tm_mday;
        funcs->func[i].data_saida.mes = tm->tm_mon + 1;
        funcs->func[i].data_saida.ano = tm->tm_year + 1900;
        }else{
            do{
                puts(MSG_OBT_DATA_SAIDA);
                funcs->func[i].data_saida.dia = obterInt(MIN_DIA,MAX_DIA,MSG_OBT_DATA_DIA,VAL_INV);
                funcs->func[i].data_saida.mes = obterInt(MIN_MES,MAX_MES,MSG_OBT_DATA_MES,VAL_INV);
                funcs->func[i].data_saida.ano = obterInt(MIN_ANO,funcs->func[i].data_entr.ano,MSG_OBT_DATA_ANO,VAL_INV);
            }while(ver_data(funcs->func[i].data_entr,funcs->func[i].data_saida,0,ERR_DATA_SAIDA)!=-1);
        }
        printf(MSG_REMOV);
    } else {
        printf(ERR_N_EXISTE);
    }
}

void func_list(Funcs funcs) {
    printf(MSG_FUNC_LIST);
    if (funcs.cont != 0) {
        printf("Funcionarios Existentes:%d\n", funcs.cont);
        func_list_ativo(funcs);
        func_list_n_ativo(funcs);
        printf(MSG_LIST);
    } else {
        printf(ERR_VAZIA_LIST);
    }
}
void func_list_ativo(Funcs funcs) {
    for (int i = 0; i < funcs.cont; i++) {
        if (funcs.func[i].del == Ativo) {
            printf("\t->Funcionario-%d:\n", funcs.func[i].cod);
            printf("\t\tNome: %s\n", funcs.func[i].nome);
            printf("\t\tTel: %d\n", funcs.func[i].tel);
            printf("\t\tData de Nascimento(D/M/A): %d/%d/%d\n", funcs.func[i].data_nasc.dia, funcs.func[i].data_nasc.mes, funcs.func[i].data_nasc.ano);
            printf("\t\tData de Entrada(D/M/A): %d/%d/%d\n", funcs.func[i].data_entr.dia, funcs.func[i].data_entr.mes, funcs.func[i].data_entr.ano);
            calcular_idades(&funcs.func[i]);
            printf("\t\tIdade: %.0f\n", funcs.func[i].idade);
            printf("\t\tAnos de Serviço: %.0f\n", funcs.func[i].anos_servico);
            if (funcs.func[i].del == Ativo) {
                printf("\t\tAtivo:Sim\n");
            } else {
                printf("\t\tAtivo: Nao\n");
                printf("\t\tData de Saida(D/M/A): %d/%d/%d\n", funcs.func[i].data_saida.dia, funcs.func[i].data_saida.mes, funcs.func[i].data_saida.ano);
            }
            printf("\t\tEstado Civil: ");
            if (funcs.func[i].est_civil == Solteiro) {
                printf("Solteiro\n");
            } else if (funcs.func[i].est_civil == Casado_1||funcs.func[i].est_civil == Casado_2) {
                printf("Casado \n");
            } else if (funcs.func[i].est_civil == Viuvo) {
                printf("Viuvo\n");
            }
            printf("\t\tNº de Dependentes: %d\n", funcs.func[i].dep);
            printf("\t\tCargo: ");
            if (funcs.func[i].cargo == Chefe) {
                printf("Chefe na função %s\n",funcs.func[i].funcao);
            } else if (funcs.func[i].cargo == Administrador) {
                printf("Administrador na função %s\n",funcs.func[i].funcao);
            } else if (funcs.func[i].cargo == Funcionario) {
                printf("Funcionario na função %s\n",funcs.func[i].funcao);
            }
            printf("\t\tRecebe por hora: %.2f\n", funcs.func[i].val_hor);
            printf("\t\tRecebe de Subsidio de Alimentacao por dia: %.2f\n", funcs.func[i].val_sub);
        }
    }
} 


void func_list_n_ativo(Funcs funcs) {
    for (int i = 0; i < funcs.cont; i++) {
        if (funcs.func[i].del == Nao_ativo) {
            printf("\t->Funcionario-%d:\n", funcs.func[i].cod);
            printf("\t\tNome: %s\n", funcs.func[i].nome);
            printf("\t\tTel: %d\n", funcs.func[i].tel);
            printf("\t\tData de Nascimento(D/M/A): %d/%d/%d\n", funcs.func[i].data_nasc.dia, funcs.func[i].data_nasc.mes, funcs.func[i].data_nasc.ano);
            printf("\t\tData de Entrada(D/M/A): %d/%d/%d\n", funcs.func[i].data_entr.dia, funcs.func[i].data_entr.mes, funcs.func[i].data_entr.ano);
            calcular_idades(&funcs.func[i]);
            printf("\t\tIdade: %.0f\n", funcs.func[i].idade);
            printf("\t\tAnos de Serviço: %.0f\n", funcs.func[i].anos_servico);
            if (funcs.func[i].del == Ativo) {
                printf("\t\tAtivo:Sim\n");
            } else {
                printf("\t\tAtivo: Nao\n");
                printf("\t\tData de Saida(D/M/A): %d/%d/%d\n", funcs.func[i].data_saida.dia, funcs.func[i].data_saida.mes, funcs.func[i].data_saida.ano);
            }
            printf("\t\tEstado Civil: ");
            if (funcs.func[i].est_civil == Solteiro) {
                printf("Solteiro\n");
            } else if (funcs.func[i].est_civil == Casado_1||funcs.func[i].est_civil == Casado_2) {
                printf("Casado\n");
            } else if (funcs.func[i].est_civil == Viuvo) {
                printf("Viuvo\n");
            }
            printf("\t\tNº de Dependentes: %d\n", funcs.func[i].dep);
            printf("\t\tCargo: ");
            if (funcs.func[i].cargo == Chefe) {
                printf("Chefe na função %s\n",funcs.func[i].funcao);
            } else if (funcs.func[i].cargo == Administrador) {
                printf("Administrador na função %s\n",funcs.func[i].funcao);
            } else if (funcs.func[i].cargo == Funcionario) {
                printf("Funcionario na função %s\n",funcs.func[i].funcao);
            }
            printf("\t\tRecebe por hora: %.2f\n", funcs.func[i].val_hor);
            printf("\t\tRecebe de Subsidio de Alimentacao por dia: %.2f\n", funcs.func[i].val_sub);
        }
    }
}


void func_edit(Funcs *funcs) {
    int cod = obterInt(MIN_COD, MAX_COD, MSG_OBT_EDIT_COD, VAL_INV);
    int i = func_search(funcs, cod);
    int ver;
    if (i != -1) {
        
        ver = perg_s_n(MSG_EDIT_COD);
        if (ver != -1) {
            do{
            cod = obterInt(MIN_COD, MAX_COD, MSG_OBT_EDIT_COD, VAL_INV);
            }while(func_search(funcs, cod)!=-1);
        }
        ver = perg_s_n(MSG_EDIT_NOME);
        if (ver != -1) {
            lerString(funcs->func[i].nome, MAX_STRING, MSG_OBT_NOME);
        }
        ver = perg_s_n(MSG_EDIT_FUNCAO);
        if (ver != -1) {
            lerString(funcs->func[i].funcao,MAX_STRING,MSG_OBT_FUNCAO);
        }
        ver = perg_s_n(MSG_EDIT_CARGO);
        if (ver != -1) {
            funcs->func[i].cargo = obterInt(MIN_CARG, MAX_CARG, MSG_OBT_CARGO, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_DATA_NASC);
        if (ver != -1) {
            printf(MSG_OBT_DATA_NASC);
            funcs->func[i].data_nasc.dia = obterInt(MIN_DIA, MAX_DIA, MSG_OBT_DATA_DIA, VAL_INV);
            funcs->func[i].data_nasc.mes = obterInt(MIN_MES, MAX_MES, MSG_OBT_DATA_MES, VAL_INV);
            funcs->func[i].data_nasc.ano = obterInt(MIN_ANO, MAX_ANO, MSG_OBT_DATA_ANO, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_DATA_ENTR);
        if (ver != -1) {
            do {
                printf(MSG_OBT_DATA_ENTR);
                funcs->func[i].data_entr.dia = obterInt(MIN_DIA, MAX_DIA, MSG_OBT_DATA_DIA, VAL_INV);
                funcs->func[i].data_entr.mes = obterInt(MIN_MES, MAX_MES, MSG_OBT_DATA_MES, VAL_INV);
                funcs->func[i].data_entr.ano = obterInt(MIN_ANO, MAX_ANO, MSG_OBT_DATA_ANO, VAL_INV);
            } while (ver_data((funcs->func[i].data_nasc), (funcs->func[i].data_entr),1, ERR_DATA_ENTR) != 1);
        }
        calcular_idades(&funcs->func[i]);
        ver = perg_s_n(MSG_EDIT_TEL);
        if (ver != -1) {
            do {
                printf(MSG_OBT_TEL);
                funcs->func[funcs->cont].tel=obterInt(MIN_TEL,MAX_TEL,MSG_OBT_TEL,VAL_INV);
            } while (ver_tel(funcs->func[i].tel, VAL_INV) == -1);
        }
        ver = perg_s_n(MSG_EDIT_ESTCIV);
        if (ver != -1) {
            funcs->func[i].est_civil = obterInt(MIN_ESTCIV, MAX_ESTCIV, MSG_OBT_ESTCIVIL, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_DEP);
        if (ver != -1) {
            funcs->func[i].dep = obterInt(MIN_DEP, MAX_DEP, MSG_OBT_DEP, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_VAL_HORA);
        if (ver != -1) {
            funcs->func[i].val_hor = obterFloat(MIN_VAL, MAX_VAL, MSG_OBT_VALOR_HORA, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_VAL_SUB);
        if (ver != -1) {
            funcs->func[i].val_sub = obterFloat(MIN_VAL, MAX_VAL, MSG_OBT_VALOR_SUB, VAL_INV);
        }
        ver = perg_s_n(MSG_EDIT_ATIVO);
        if (ver != -1) {
            funcs->func[i].del = Ativo;
        } else {
            funcs->func[i].del = Nao_ativo;
            printf(MSG_EDIT_ATIVO_DATA);
            funcs->func[i].data_saida.dia = obterInt(MIN_DIA, MAX_DIA, MSG_OBT_DATA_DIA, VAL_INV);
            funcs->func[i].data_saida.mes = obterInt(MIN_MES, MAX_MES, MSG_OBT_DATA_MES, VAL_INV);
            funcs->func[i].data_saida.ano = obterInt(MIN_ANO, MAX_ANO, MSG_OBT_DATA_ANO, VAL_INV);
        }
        printf(MSG_EDIT);
    } else {
        printf(ERR_N_EXISTE);
    }
}


int carregar_Funcs(Funcs *funcs, char *file) {
    strcat(file,FILE_TYPE_BIN);
    if (funcs->tam != 0) {
        free(funcs->func);
    }
    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        fread(&funcs->cont, sizeof (int), 1, fp);
        if (funcs->cont > 0) {
            funcs->func = (Func*) malloc(funcs->cont * sizeof (Func));
            fread(funcs->func, sizeof (Func), funcs->cont, fp);
            for(int i=0;i<funcs->cont;i++){
            calcular_idades(funcs->func);
            }
            funcs->tam = funcs->cont;
            printf(MSG_FUNC_CARR,file);
            fclose(fp);
            return 1;
        } else {
            printf(MSG_FUNC_N_CARR,file);
            fclose(fp);
            return 0;
        }
    } else {
        printf(ERR_FILE_FUNC_N_EXISTE, file);
        return 0;
    }
}

void guardar_Funcs(Funcs *funcs, char *file) {
    strcat(file,FILE_TYPE_BIN);
    if (funcs->cont != 0) {
        FILE *fp = fopen(file, "wb");
        if (fp != NULL) {
            fwrite(&funcs->cont, sizeof (int), 1, fp);
            fwrite(funcs->func, sizeof (Func), funcs->cont, fp);
            fclose(fp);
            printf(MSG_FUNC_GRAV,file);
        }
    } else {
        printf(ERR_VAZIA_GUARDAR,file);
    }
}

int func_search(Funcs *funcs, int cod) {
    int i;
    for (i = 0; i <= funcs->cont; i++) {
        if (funcs->func[i].cod == cod) {
            return i;
        }
    }
    return -1;
}


void calcular_idades(Func *func) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int calculo;
    calculo = 365 * (tm->tm_year + 1900) + tm->tm_yday - 365 * func->data_nasc.ano - 30 * func->data_nasc.mes - func->data_nasc.dia;
    func->idade = calculo / 365;
    calculo = 365 * (tm->tm_year + 1900) + tm->tm_yday - (365 * func->data_entr.ano) - (30 * func->data_entr.mes) - (func->data_entr.dia);
    func->anos_servico = calculo / 365;
}


int ver_tel(int num, char *err) {
    char str[MAX_STRING];
    sprintf(str, "%d", num);
    if (str[0] == '9') {
        if (str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '6') {
            return (1);
        }
    }
    printf(err);
    return (-1);
}
