#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Proc_Salario.h"
#include "input.h"
#include "ficheiros.h"
#include "logs.h"

void expandir_Proc_Salario_Bonus(Tab_Bonus *tabs) {
    Linha_bonus *temp = (Linha_bonus*) realloc(tabs->linha, sizeof (Linha_bonus)* (tabs->tam + 2));
    if (temp != NULL) {
        tabs->tam += 2;
        tabs->linha = temp;
    }
}

void listar_func_bonus(Funcs funcs, Tab_Bonus tab) {
    Linha_bonus maior = {.anosservico = 0, .bonus = 0, .idade = 0};
    int bool = 0, linha = 0;
    if (funcs.cont != 0) {
        if (tab.cont != 0) {
            printf("|------Tabela de o maior bonus que cada funcionario pode ter direito:-----|\n");
            printf("|---------Funcionario:----------|--------------Tabela Bonus:--------------|\n");
            printf("|Codigo:|Idade:|Anos de serviço:|L:|Idade:|Anos de serviço:|Faltas:|Bonus:|\n");
            for (int i = 0; i < funcs.cont; i++) {
                bool = 0, linha = 0;
                maior.anosservico = 0, maior.bonus = 0, maior.idade = 0;
                for (int j = 0; j < tab.cont; j++) {
                    if (maior.bonus <= tab.linha[j].bonus) {
                        if (tab.linha[j].idade <= funcs.func[i].idade) {
                            if (tab.linha[j].anosservico <= funcs.func[i].anos_servico) {
                                maior.bonus = tab.linha[j].bonus;
                                maior.anosservico = tab.linha[j].anosservico;
                                maior.idade = tab.linha[j].idade;
                                linha = j;
                                bool = 1;
                            }
                        }
                    }
                }
                if (bool == 1) {
                    printf(" %d    %.0f           %.0f         %d     %d           %d          %d     %.1f%%\n", funcs.func[i].cod, funcs.func[i].idade,
                            funcs.func[i].anos_servico, linha, maior.idade, maior.anosservico, maior.diasfaltas, maior.bonus);
                } else {
                    printf(" %d    %.0f           %.0f         --    --          ---        ---      -- \n", funcs.func[i].cod, funcs.func[i].idade,
                            funcs.func[i].anos_servico);
                }
            }
            printf("|-------------------------------------------------------------------------|\n");
        } else {
            printf(ERR_VAZIA_LISTA_BONUS);
        }
    } else {
        printf(ERR_VAZIA_LIST);
    }
}

void pergs_criterio(Linha_bonus *linha) {
    if (perg_s_n(MSG_OBT_SN_DEP) != -1) {
        linha->idade = obterInt(MIN_DEP_PS, MAX_DEP_PS, MSG_OBT_VALOR_DEP, VAL_INV_PS);
    } else {
        linha->idade = 0;
    }
    if (perg_s_n(MSG_OBT_SN_ANOSSERVICO) != -1) {
        linha->anosservico = obterInt(MIN_ANOSSERVICO_PS, MAX_ANOSSERVICO_PS, MSG_OBT_VALOR_ANOSSERVICO, VAL_INV_PS);
    } else {
        linha->anosservico = 0;
    }
    if (perg_s_n(MSG_OBT_SN_DIASFALTAS) != -1) {
        linha->diasfaltas = obterInt(MIN_DIAS_FALTAS, MAX_DIAS_FALTAS, MSG_OBT_VALOR_DIASFALTAS, VAL_INV_PS);
    } else {
        linha->diasfaltas = 30;
    }
}

void Proc_Salario_Bonus_add(Tab_Bonus *tabs) {
    printf(MSG_TABS_BONUS_ADD);
    tabs->cont++;
    while (tabs->cont >= tabs->tam) {
        expandir_Proc_Salario_Bonus(tabs);
    }
    do {
        pergs_criterio(&tabs->linha[tabs->cont - 1]);
    } while (ver_criterio_bonus(*tabs, tabs->cont - 1) != -1);
    tabs->linha[tabs->cont - 1].bonus = obterFloat(MIN_BONUS_PS, MAX_BONUS_PS, MSG_OBT_VALOR_BONUS_PS, VAL_INV_PS);
    printf(MSG_LINHA_ADICIONADA_PS);
}

int carregar_Proc_Salario_Bonus(Tab_Bonus *tabs, char *file) {
    if (tabs->tam != 0) {
        free(tabs->linha);
    }
    strcat(file, FILE_TYPE_BIN);
    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        fread(&tabs->cont, sizeof (int), 1, fp);
        if (tabs->cont > 0) {
            tabs->linha = (Linha_bonus*) malloc(tabs->cont * sizeof (Linha_bonus));
            fread(tabs->linha, sizeof (Linha_bonus), tabs->cont, fp);
            tabs->tam = tabs->cont;
            printf(MSG_CARR_PS);
            fclose(fp);
            return 1;
        } else {
            fclose(fp);
            printf(MSG_N_CARR_PS);
            return 0;
        }
    } else {
        printf(ERR_FILE_N_EXISTE_BONUS);
        return 0;
    }
}

void guardar_Proc_Salario_Bonus(Tab_Bonus tabs, char *file) {
    strcat(file, FILE_TYPE_BIN);
    if (tabs.cont != 0) {
        FILE *fp = fopen(file, "wb");
        if (fp != NULL) {
            fwrite(&tabs.cont, sizeof (int), 1, fp);
            fwrite(tabs.linha, sizeof (Linha_bonus), tabs.cont, fp);
            printf(MSG_TAB_GUARDAR_PS);
            fclose(fp);
        }
    } else {
        printf(ERR_VAZIA_GUARDAR_PS);
    }
}

void Proc_Salario_remove_Bonus(Tab_Bonus *tabs) {
    if (tabs->cont != 0) {
        int i;
        int nlinha = obterInt(MIN_LINHA_PS, tabs->cont, MSG_OBT_NLINHA_PS, VAL_INV_PS);
        for (i = nlinha - 1; i < tabs->cont; i++) {
            tabs->linha[i].idade = tabs->linha[i + 1].idade;
            tabs->linha[i].anosservico = tabs->linha[i + 1].anosservico;
            tabs->linha[i].bonus = tabs->linha[i + 1].bonus;
            tabs->linha[i].diasfaltas = tabs->linha[i + 1].diasfaltas;
        }
        tabs->cont -= 1;
        printf(MSG_REMOV_PS);
    } else {
        printf(ERR_VAZIA_LISTA_PS);
    }
}

void Proc_Salario_edit_Bonus(Tab_Bonus *tabs) {
    if (tabs->cont != 0) {
        int i, opc;
        int nlinha = obterInt(MIN_LINHA_PS, tabs->cont, MSG_OBT_NLINHA_EDIT_PS, VAL_INV_PS);
        do {
            printf("Escolha o que deseja editar na linha %d: \n", nlinha);
            printf("1. Criterios\n");
            printf("2. Bónus: %.2f%%\n", tabs->linha[nlinha - 1].bonus);
            printf("0. Voltar ao menu anterior\n");
            opc = obterInt(VAL_MIN_OPC_PS, VAL_MAX_OPC_PS, "", OPC_INV_PS);
            switch (opc) {
                case 1:
                    do {
                        pergs_criterio(&tabs->linha[nlinha - 1]);
                    } while ((ver_criterio_bonus(*tabs, nlinha)) != -1);
                    break;
                case 2:
                    tabs->linha[nlinha - 1].bonus = obterFloat(MIN_BONUS_PS, MAX_BONUS_PS, MSG_OBT_VALOR_BONUS_PS, VAL_INV_PS);
                    break;
                case 0:
                    break;
                default:
                    puts(OPC_INV_PS);
                    break;
            }
        } while (opc != 0);
    } else {
        printf(ERR_VAZIA_LISTA_PS);
    }
}

int ver_criterio_bonus(Tab_Bonus tabela, int nlinha) {
    for (int i = 0; i < tabela.cont; i++) {
        if (i != nlinha - 1) {
            if (tabela.linha[nlinha - 1].idade == tabela.linha[i].idade) {
                if (tabela.linha[nlinha - 1].anosservico == tabela.linha[i].anosservico) {
                    if (tabela.linha[nlinha - 1].diasfaltas == tabela.linha[i].diasfaltas) {
                        printf(ERR_CRIT_EXIST);
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

void Proc_Salario_Bonus_list(Tab_Bonus tabs) {
    if (tabs.cont != 0) {
        printf("| L|Idade (Maior): | Nº Anos de serviço(Maior): |Dias de Falta(Menor):| Valor  Bónus |\n");
        for (int i = 0; i < tabs.cont; i++) {
            printf(" [%d] \t", i + 1);
            if (tabs.linha[i].idade > 0) {
                printf("  %d \t\t", tabs.linha[i].idade);
            } else {
                printf(" ------- \t");
            }
            if (tabs.linha[i].anosservico > 0) {
                printf("\t %d\t\t", tabs.linha[i].anosservico);
            } else {
                printf("\t ------- \t");
            }

            if (tabs.linha[i].diasfaltas < 30) {
                printf("\t %d\t", tabs.linha[i].diasfaltas);
            } else {
                printf("\t ------- \t");
            }
            printf("  %.2f%% \t\n", tabs.linha[i].bonus);
        }
    }
}

void expandir_meses(MESES_TOTAL *mes_total) {
    MES *temp = (MES*) realloc(mes_total->mes, sizeof (Linha_segsoc)* (mes_total->tam + 2));
    if (temp != NULL) {
        mes_total->tam += 2;
        mes_total->mes = temp;
    }
}

void calculo_salario(Funcs *func_info, Tab_IRS *tab_irs, Tab_SS *tab_ss, Tab_Bonus *tab_Bonus, MESES_TOTAL *mes_total) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char file[MAX_STRING];
    int mes, ano, ver_bonus = 1;
    int ficheiros_falta = 5, n;
    int carregados = 0;
    if (tab_Bonus->cont == 0) {
        ver_bonus = perg_s_n(MSG_OBT_SN_BONUS);
        if (ver_bonus == 1) {
            do {
                lerString(file, MAX_FILE, MSG_LER_FILE);
                if (ver_char(file, CHAR_SAIR) == 1) {
                    return;
                }
            } while (carregar_Proc_Salario_Bonus(tab_Bonus, file) != 1);
        }
    }
    while (ficheiros_falta > 0 || carregados == 1) {

        if (func_info->cont != 0 && tab_irs[0].cont != 0 && tab_irs[1].cont != 0 && tab_irs[2].cont != 0 && tab_ss->cont != 0) {
            ficheiros_falta = 0;
            carregados = 0;
            printf(MSG_OBTER_DATA);
            ano = obterInt(MIN_ANO, tm->tm_year + 1900, MSG_OBTER_ANO, INV_DATA_ANO);
            if (ano == tm->tm_year + 1900) {
                mes = obterInt(MIN_MES, tm->tm_mon + 2, MSG_OBTER_MES, INV_DATA_MES);
            } else {
                mes = obterInt(MIN_MES, MAX_MES, MSG_OBTER_MES, INV_DATA_MES);
            }
            n = ver_mes(*mes_total, ano, mes);
            if (n == -1) {
                if (mes_total->cont == mes_total->tam) {
                    expandir_meses(mes_total);
                }
                n = mes_total->cont;
                mes_total->mes[n].cont = 0;
                mes_total->mes[n].tam = 0;
            }
            lerString(file, MAX_FILE, MSG_LER_FILE_PROC);
            int carrs = carregar_tab_Funcionario_Mes(&mes_total->mes[n], file);
            if (carrs > 0) {
                printf(MSG_INFO_FUNC, carrs, ano, mes);
                mes_total->mes[n].ano = ano;
                mes_total->mes[n].mes = mes;
                mes_total->mes[n].emp_mes.valor_bonus_total =0;
                mes_total->mes[n].emp_mes.valor_bruto_total =0;
                mes_total->mes[n].emp_mes.valor_segsoc_total = 0;
                mes_total->mes[n].emp_mes.valor_sub_total = 0;
                mes_total->mes[n].emp_mes.valor_total =0;
                for (int i = 0; i < mes_total->mes[n].cont; i++) {
                    int i_info = func_search(func_info, mes_total->mes[n].funcionario[i].cod);
                    if (i_info != -1) {
                        if (func_info->func[i_info].del == Ativo) {
                            calculo_bruto(func_info->func[i_info], &mes_total->mes[n].funcionario[i]);
                            if (ver_bonus == 1) {
                                calcular_Salario_Bonus(&mes_total->mes[n].funcionario[i], func_info->func[i_info], *tab_Bonus);
                            } else {
                                mes_total->mes[n].funcionario[i].func.valor_bonus = 0;
                            }
                            calcular_Salario_Tabela_IRS(&mes_total->mes[n].funcionario[i], func_info->func[i_info], tab_irs);
                            calcular_Salario_Tabela_SegSoc(&mes_total->mes[n].funcionario[i], func_info->func[i_info], *tab_ss);
                            mes_total->mes[n].funcionario[i].func.valor_liquido = mes_total->mes[n].funcionario[i].func.valor_bruto + mes_total->mes[n].funcionario[i].func.valor_bonus + mes_total->mes[n].funcionario[i].func.valor_sub_alimentacao - mes_total->mes[n].funcionario[i].func.valor_irs_funcionario - mes_total->mes[n].funcionario[i].func.valor_segsoc_funcionario;
                            mes_total->mes[n].funcionario[i].emp.valor_total = mes_total->mes[n].funcionario[i].func.valor_bruto + mes_total->mes[n].funcionario[i].emp.valor_segsoc_empresa + mes_total->mes[n].funcionario[i].func.valor_sub_alimentacao + mes_total->mes[n].funcionario[i].func.valor_bonus;
                            calcular_depesas_emp(mes_total, n, i);
                            mes_total->mes[n].funcionario[i].calculado = 1;
                        } else {
                            printf(ERR_FUNC_N_ATIV, func_info->func[i_info].cod);
                            mes_total->mes[n].funcionario[i].calculado = 0;
                        }
                    } else {
                        mes_total->mes[n].funcionario[i].calculado = 0;
                        printf(ERR_FUNC_N_MEM, mes_total->mes[n].funcionario[i].cod);
                    }
                }
                mes_total->cont++;
            }
        }
        if (func_info->cont == 0) {
            do {
                printf(ERR_FUNC);
                lerString(file, MAX_FILE, MSG_LER_FILE);
                if (ver_char(file, CHAR_SAIR) == 1) {
                    return;
                }
            } while (carregar_Funcs(func_info, file) != 1);
            ficheiros_falta--;
            carregados = 1;
        } else {
            ficheiros_falta--;
        }
        for (int i = 0; i < 3; i++) {
            char msg[MAX_STRING];
            if (i == 0) {
                strcpy(msg, ERR_N_TAB_IRS_SOLT);
            } else if (i == 1) {
                strcpy(msg, ERR_N_TAB_IRS_CAS_1);
            } else {
                strcpy(msg, ERR_N_TAB_IRS_CAS_2);
            }
            if (tab_irs[i].cont == 0) {
                do {
                    printf("%s\n", msg);
                    lerString(file, MAX_FILE, MSG_LER_FILE);
                    if (ver_char(file, CHAR_SAIR) == 1) {
                        return;
                    }
                } while (carregar_tab_IRS(&tab_irs[i], file) != 1);
                ficheiros_falta--;
                carregados = 1;
            } else {
                ficheiros_falta--;
            }
        }
        if (tab_ss->cont == 0) {
            do {
                printf(ERR_TAB_SS);
                lerString(file, MAX_FILE, MSG_LER_FILE);
                if (ver_char(file, CHAR_SAIR) == 1) {
                    return;
                }
            } while (carregar_SegSoc(tab_ss, file) != 1);
            carregados = 1;
            ficheiros_falta--;
        } else {
            ficheiros_falta--;
        }
    }
}

int ver_char(char *file, char letra) {
    if (strlen(file) == 1) {
        if (*file == letra) {
            return 1;
        }
    }
    return 0;
}

int carregar_tab_Funcionario_Mes(MES *Tabs, char *file) {
    if (Tabs->tam != 0) {
        free(Tabs->funcionario);
    }
    int car = 0;
    char string[MAX_STRING];
    strcat(file, FILE_TYPE_CSV);
    FILE *fp;
    Tabs->cont = conta_linhas(file) - 1;
    fp = fopen(file, "r");
    if (fp != NULL) {
        if (Tabs->cont > 0) {
            Info_funcionario_mes *temp = (Info_funcionario_mes*) malloc((Tabs->cont)*(sizeof (Info_funcionario_mes)));
            if (temp != NULL) {
                Tabs->funcionario = temp;
                fscanf(fp, "Cod. Funcionario:;Dias Completos:;Meios Dias:;Fins de Semana:;Faltas:\n");
                for (int i = 0; i < Tabs->cont; i++) {
                    fgets(string, MAX_STRING, fp);
                    sscanf(string, "%d;%d;%d;%d;%d", &Tabs->funcionario[i].cod, &Tabs->funcionario[i].dias_comp, &Tabs->funcionario[i].dias_meio,
                            &Tabs->funcionario[i].dias_fimsemana, &Tabs->funcionario[i].dias_faltas);
                    car++;
                }
                Tabs->tam = Tabs->cont;
            }
            fclose(fp);
        } else {
            printf(ERR_FILE_N_CARR_PS, file);
            fclose(fp);
        }
    } else {

        printf(ERR_FILE_N_EXISTE_PS, file);
    }
    return car;
}

int ver_mes(MESES_TOTAL meses_total, int ano, int mes) {
    if (meses_total.cont != 0) {
        for (int i = 0; i < meses_total.cont; i++) {
            if (meses_total.mes[i].ano == ano) {
                if (meses_total.mes[i].mes == mes) {
                    return i;
                }
            }
        }
    }
    return -1;
}

int ver_ano_meses(MESES_TOTAL meses_total, int ano) {
    int cont = 0;
    if (meses_total.cont != 0) {
        for (int i = 0; i < meses_total.cont; i++) {
            if (meses_total.mes[i].ano == ano) {
                cont++;
            }
        }
    }
    return cont;
}

void calcular_depesas_emp(MESES_TOTAL *mes_total, int mes, int func) {
    mes_total->mes[mes].emp_mes.valor_bonus_total += mes_total->mes[mes].funcionario[func].func.valor_bonus;
    mes_total->mes[mes].emp_mes.valor_bruto_total += mes_total->mes[mes].funcionario[func].func.valor_bruto;
    mes_total->mes[mes].emp_mes.valor_segsoc_total += mes_total->mes[mes].funcionario[func].emp.valor_segsoc_empresa;
    mes_total->mes[mes].emp_mes.valor_sub_total += mes_total->mes[mes].funcionario[func].func.valor_sub_alimentacao;
    mes_total->mes[mes].emp_mes.valor_total += mes_total->mes[mes].funcionario[func].func.valor_bonus + mes_total->mes[mes].funcionario[func].func.valor_bruto + mes_total->mes[mes].funcionario[func].emp.valor_segsoc_empresa + mes_total->mes[mes].funcionario[func].func.valor_sub_alimentacao;
}

void calculo_bruto(Func func_info, Info_funcionario_mes *func) {
    func->func.valor_hora = func_info.val_hor;
    func->func.valor_sub_alimentacao = (func_info.val_sub * func->dias_comp)+ (func_info.val_sub * func->dias_fimsemana);
    func->func.valor_bruto = (func->dias_comp * (func->func.valor_hora * HORAS_DIACOMP))+ (func->dias_meio * (func->func.valor_hora * HORAS_MEIODIAS))+
            (func->dias_fimsemana * ((func->func.valor_hora * PORC_EXTRA_FIMSEMANA) * HORAS_DIACOMP));
}

void calcular_Salario_Tabela_IRS(Info_funcionario_mes *funcionario, Func func, Tab_IRS *tabela) {
    int i, j;
    int tab;
    if (func.est_civil == Solteiro || func.est_civil == Viuvo) {
        tab = 0;
    } else if (func.est_civil == Casado_1) {
        tab = 1;
    } else {
        tab = 2;
    }
    for (i = 0; i < tabela[tab].cont; i++) {
        if (i == 0) {
            if (tabela[tab].Linha[i].col[0] > funcionario->func.valor_bruto) {
                for (int j = 0; j < COLUNAS - 1; j++) {
                    if (j <= func.dep) {
                        funcionario->func.valor_irs_funcionario = funcionario->func.valor_bruto * (tabela[tab].Linha[i].col[j + 1] / 100);
                    }
                }
                return;
            }
        } else if (i == tabela[tab].cont - 1) {
            if (tabela[tab].Linha[i].col[0] <= funcionario->func.valor_bruto) {
                for (int j = 0; j < COLUNAS - 1; j++) {
                    if (j <= func.dep) {
                        funcionario->func.valor_irs_funcionario = funcionario->func.valor_bruto * (tabela[tab].Linha[i].col[j + 1] / 100);
                    }
                }
                return;
            }
        } else {
            if (tabela[tab].Linha[i - 1].col[0] < funcionario->func.valor_bruto && funcionario->func.valor_bruto <= tabela[tab].Linha[i].col[0]) {
                for (int j = 0; j < COLUNAS - 1; j++) {
                    if (j <= func.dep) {
                        funcionario->func.valor_irs_funcionario = funcionario->func.valor_bruto * (tabela[tab].Linha[i].col[j + 1] / 100);

                    }
                }
                return;
            }
        }


    }
}

void calcular_Salario_Tabela_SegSoc(Info_funcionario_mes *funcionario, Func func, Tab_SS tabela) {
    int i;
    for (i = 0; i < tabela.cont; i++) {
        if (tabela.linha[i].tipo.ativo == Ativo) {
            if (func.cargo == tabela.linha[i].tipo.cargo) {
                funcionario->func.valor_segsoc_funcionario = funcionario->func.valor_bruto * (tabela.linha[i].trabalhador / 100);
                funcionario->emp.valor_segsoc_empresa = funcionario->func.valor_bruto * (tabela.linha[i].entempregadora / 100);
            }
        }
    }
    int j;
    for (i = 0; i < tabela.cont; i++) {
        int contador = 0;
        if (tabela.linha[i].tipo.ativo == Nao_ativo) {
            if (strlen(func.funcao) == strlen(tabela.linha[i].funcao)) {
                for (j = 0; j < strlen(func.funcao); j++) {
                    if (tabela.linha[i].funcao[j] == func.funcao[j]) {
                        contador++;
                    }
                }
            }
            if (contador == strlen(func.funcao)) {
                funcionario->func.valor_segsoc_funcionario = funcionario->func.valor_bruto * (tabela.linha[i].trabalhador / 100);
                funcionario->emp.valor_segsoc_empresa = funcionario->func.valor_bruto * (tabela.linha[i].entempregadora / 100);
            }
        }
    }
}

void calcular_Salario_Bonus(Info_funcionario_mes *funcionario, Func func, Tab_Bonus tabela) {
    float bonus;
    for (int i = 0; i < tabela.cont; i++) {
        if (tabela.linha[i].bonus >= bonus) {
            if (tabela.linha[i].idade <= func.idade) {
                if (tabela.linha[i].anosservico <= func.anos_servico) {
                    if (tabela.linha[i].diasfaltas >= funcionario->dias_faltas) {
                        bonus = tabela.linha[i].bonus;
                    }
                }
            }
        }
    }
    funcionario->func.valor_bonus = (bonus / 100) * funcionario->func.valor_bruto;
}

void menu_Listar_ano_mes(MESES_TOTAL mes_total) {
    int opc;
    int cod, mes, ano;
    if (mes_total.cont != 0) {
        logMsg(LOG_OPC_LIST_MENU, LOG_FILE);
        do {
            opc = obterInt(VAL_MIN_OPC_PS, VAL_MAX_OPC_PS, MSG_LISTAR, OPC_INV_PS);
            switch (opc) {
                case 1:
                    Listar_ano_comp(mes_total);
                    logMsg(LOG_OPC_LIST_ANO, LOG_FILE);
                    break;
                case 2:
                    Listar_mes(mes_total);
                    logMsg(LOG_OPC_LIST_MES, LOG_FILE);
                    break;
                case 3:
                    Listar_funcionario_ano(mes_total);
                    logMsg(LOG_OPC_LIST_MES, LOG_FILE);
                    break;
                case 0:
                    logMsg(LOG_OPC_TAB_BONUS_SAIR, LOG_FILE);
                    break;
            }
        } while (opc != 0);
    } else {
        printf("Tabela vazia!\n");
    }
}

void Listar_ano_comp(MESES_TOTAL meses_total) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int ano = obterInt(MIN_ANO_PS, tm->tm_year + 1900, MSG_OBTER_ONLY_ANO, INV_DATA_ANO);
    int ver = ver_ano_meses(meses_total, ano);
    int n;
    if (ver > 0) {
        if (ver != 12) {
            printf(ERR_MESES_EXIST, ver);
        }
        printf("------------------------------------------------------Ano:%d--------------------------------------------------\n", ano);
        printf("| Ano | Mês | Valor Bruto Total:|Valor Sub. Ali. Total:||Valor Bonus Total:|Valor Seg. Soc. Total:|Valor Total:|\n");
        for (int i = 0; i < MAX_MES_PS; i++) {
            n = ver_mes(meses_total, ano, i);
            if (n != -1) {
                printf("  %d   %d        %.1f€               %.1f€                 %.1f€               %.1f€            %.1f€\n", meses_total.mes[n].ano, meses_total.mes[n].mes, meses_total.mes[n].emp_mes.valor_bruto_total, meses_total.mes[n].emp_mes.valor_sub_total, meses_total.mes[n].emp_mes.valor_bonus_total, meses_total.mes[n].emp_mes.valor_segsoc_total, meses_total.mes[n].emp_mes.valor_total);
            }
        }
    } else {
        printf(ERR_ANO_N_EXISTE, ano);
    }
}

void Listar_mes(MESES_TOTAL meses_total) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int mes;
    int ano = obterInt(MIN_ANO_PS, tm->tm_year + 1900, MSG_OBTER_ANO, INV_DATA_ANO);
    if (ano == tm->tm_year + 1900) {
        mes = obterInt(MIN_MES_PS, tm->tm_mon + 2, MSG_OBTER_MES, INV_DATA_MES);
    } else {
        mes = obterInt(MIN_MES_PS, MAX_MES_PS, MSG_OBTER_MES, INV_DATA_MES);
    }
    int ver = ver_mes(meses_total, ano, mes);
    if (ver != -1) {
        printf("------------------------------------Funcinarios Calculados relativamente ao mês %d/%d----------------------------------\n", ano, mes);
        printf("|Cod.Funcionario:|Valor Bruto:|Valor Sub.Ali.:|Valor Bonus:|Valor IRS:|Valor liquido:|Valor Seg. Soc.:|Valor Total Gasto:|\n");
        for (int i = 0; i < meses_total.mes[ver].cont; i++) {
            if (meses_total.mes[ver].funcionario[i].calculado = 1) {
                printf("      %d            %.1f€        %.1f€         %.1f€       %.1f€      %.1f€         %.1f€        %.1f€\n", meses_total.mes[ver].funcionario[i].cod, meses_total.mes[ver].funcionario[i].func.valor_bruto, meses_total.mes[ver].funcionario[i].func.valor_sub_alimentacao, meses_total.mes[ver].funcionario[i].func.valor_bonus, meses_total.mes[ver].funcionario[i].func.valor_irs_funcionario, meses_total.mes[ver].funcionario[i].func.valor_liquido, meses_total.mes[ver].funcionario[i].emp.valor_segsoc_empresa, meses_total.mes[ver].funcionario[i].emp.valor_total);
            }
        }

    } else {

        printf(ERR_LISTAR_MES, mes, ano);
    }
}

void carregar_Salario_Calculado(MESES_TOTAL *mestotal, char *file) {
    if (mestotal->cont == mestotal->tam) {
        expandir_meses(mestotal);
    }
    int ver_existe, n;
    float mesf, anof;
    char string[MAX_STRING];
    strcat(file, FILE_TYPE_CSV);
    FILE *fp;
    fp = fopen(file, "r");
    if (fp != NULL) {
        fscanf(fp, "%f/%f\n", &anof, &mesf);
        ver_existe = ver_mes(*mestotal, (int) anof, (int) mesf);
        if (ver_existe != -1) {
            if (perg_s_n(MSG_MES_EXISTE) == -1) {
                return;
            }
            n = ver_existe;
        } else {
            mestotal->mes[n].emp_mes.valor_bonus_total =0;
            mestotal->mes[n].emp_mes.valor_bruto_total =0;
            mestotal->mes[n].emp_mes.valor_segsoc_total = 0;
            mestotal->mes[n].emp_mes.valor_sub_total = 0;
            mestotal->mes[n].emp_mes.valor_total =0;
            n = mestotal->cont;
            mestotal->mes[n].cont = conta_linhas(file) - 2;
            fscanf(fp, "%f/%f\n", &anof, &mesf);
            mestotal->mes[n].ano = anof;
            mestotal->mes[n].mes = mesf;
            Info_funcionario_mes *temp = (Info_funcionario_mes*) malloc((mestotal->mes[n].cont)*(sizeof (Info_funcionario_mes)));
            if (temp != NULL) {
                mestotal->mes[n].funcionario = temp;
                mestotal->mes[n].tam = mestotal->mes[n].cont;
            }
            mestotal->cont++;
        }
        if (mestotal->mes[n].cont > 0) {
            fscanf(fp, "Cod. Funcionario:;Dias Completos:;Meios Dias:;Fins de Semana:;Faltas:;Valor p/hora:;Valor Bruto:; Valor sub. ali.:;IRS Func.:;Valor Seg. Soc. Func.:;Valor Bonus:;Valor Seg. Soc. Empresa:;Valor Total Gasto:;Valor Liquido Func:\n");
            for (int i = 0; i < mestotal->mes[n].cont; i++) {
                fgets(string, MAX_STRING, fp);
                sscanf(string, "%d;%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", &mestotal->mes[n].funcionario[i].cod, &mestotal->mes[n].funcionario[i].dias_comp, &mestotal->mes[n].funcionario[i].dias_meio, &mestotal->mes[n].funcionario[i].dias_fimsemana, &mestotal->mes[n].funcionario[i].dias_faltas, &mestotal->mes[n].funcionario[i].func.valor_hora, &mestotal->mes[n].funcionario[i].func.valor_bruto, &mestotal->mes[n].funcionario[i].func.valor_sub_alimentacao, &mestotal->mes[n].funcionario[i].func.valor_irs_funcionario, &mestotal->mes[n].funcionario[i].func.valor_segsoc_funcionario, &mestotal->mes[n].funcionario[i].func.valor_bonus, &mestotal->mes[n].funcionario[i].emp.valor_segsoc_empresa, &mestotal->mes[n].funcionario[i].emp.valor_total, &mestotal->mes[n].funcionario[i].func.valor_liquido);
                calcular_depesas_emp(mestotal, n, i);
                mestotal->mes[n].funcionario[i].calculado = 1;
            }
            mestotal->mes[n].tam = mestotal->mes[n].cont;

        } else {
            printf(ERR_FILE_N_CARR_PS, file);
        }
        fclose(fp);
    } else {

        printf(ERR_FILE_N_EXISTE_PS, file);
    }
}

void guardar_Salario_Calculado(MESES_TOTAL *mestotal, char *file) {
    FILE *fp;
    int mes = 0, ano = 0;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strcat(file, FILE_TYPE_CSV);
    int n;
    if (mestotal->cont != 0) {
        if (conta_linhas(file) > 1) {
            if (perg_s_n("Deseja apagar a informação no ficheiro(S/N)?") != 1) {
                return;
            }
        }
        fp = fopen(file, "w");
        printf(MSG_GUARDAR_MES);
        ano = obterInt(MIN_ANO_PS, tm->tm_year + 1900, MSG_OBTER_ANO, INV_DATA_ANO);
        if (ano == tm->tm_year + 1900) {
            mes = obterInt(MIN_MES_PS, tm->tm_mon + 2, MSG_OBTER_MES, INV_DATA_MES);
        } else {
            mes = obterInt(MIN_MES_PS, MAX_MES_PS, MSG_OBTER_MES, INV_DATA_MES);
        }
        n = ver_mes(*mestotal, ano, mes);
        if (n != -1) {
            if (mestotal->mes[n].cont > 0) {
                if (fp != NULL) {
                    fprintf(fp, "%d/%d\n", mestotal->mes[n].ano, mestotal->mes[n].mes);
                    fprintf(fp, "Cod. Funcionario:;Dias Completos:;Meios Dias:;Fins de Semana:;Faltas:;Valor p/hora:;Valor Bruto:; Valor sub. ali.:;IRS Func.:;Valor Seg. Soc. Func.:;Valor Bonus:;Valor Seg. Soc. Empresa:;Valor Total Gasto:;Valor Liquido Func:\n");
                    for (int i = 0; i < mestotal->mes[n].cont; i++) {
                        fprintf(fp, "%d;%d;%d;%d;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n", mestotal->mes[n].funcionario[i].cod, mestotal->mes[n].funcionario[i].dias_comp, mestotal->mes[n].funcionario[i].dias_meio, mestotal->mes[n].funcionario[i].dias_fimsemana, mestotal->mes[n].funcionario[i].dias_faltas, mestotal->mes[n].funcionario[i].func.valor_hora, mestotal->mes[n].funcionario[i].func.valor_bruto, mestotal->mes[n].funcionario[i].func.valor_sub_alimentacao, mestotal->mes[n].funcionario[i].func.valor_irs_funcionario, mestotal->mes[n].funcionario[i].func.valor_segsoc_funcionario, mestotal->mes[n].funcionario[i].func.valor_bonus, mestotal->mes[n].funcionario[i].emp.valor_segsoc_empresa, mestotal->mes[n].funcionario[i].emp.valor_total, mestotal->mes[n].funcionario[i].func.valor_liquido);
                    }
                    fclose(fp);
                } else {
                    printf(ERR_FILE_N_GRAV_PS, file);
                }
            } else {
                printf(ERR_LISTAR_MES, mes, ano);
                fclose(fp);
            }
        } else {
            printf(ERR_LISTAR_MES, ano, mes);
        }
    } else {
        printf(ERR_MESES_0);
    }
}

void guardar_ficheiro_Despesas_ano(MESES_TOTAL mestotal, char *file) { //Relatorio
    time_t t = time(NULL);
    FILE *fp;
    struct tm *tm = localtime(&t);
    strcat(file, FILE_TYPE_CSV);
    if (mestotal.cont != 0) {
        printf(MSG_ANO_DESPES);
        int ano = obterInt(MIN_ANO_PS, tm->tm_year + 1900, MSG_OBTER_ANO, INV_DATA_ANO);
        int ver = ver_ano_meses(mestotal, ano);
        if (ver > 0) {
            if (conta_linhas(file) > 1) {
                if (perg_s_n(MSG_SN_APG_FILE) != 1) {
                    return;
                }
            }
            fp = fopen(file, "w");
            if (fp != NULL) {
                fprintf(fp, "Ano;Mes;Valor Bruto Total:;Valor Sub. Ali. Total:;Valor Bonus Total:;Valor Seg. Soc. Total:;Valor Total:\n");
                for (int i = 0; i < MAX_MES_PS; i++) {
                    int n = ver_mes(mestotal, ano, i);
                    if (n != -1) {
                        fprintf(fp, "%d;%d;%.1f;%.1f;%.1f;%.1f;%.1f\n", mestotal.mes[n].ano, mestotal.mes[n].mes, mestotal.mes[n].emp_mes.valor_bruto_total
                                , mestotal.mes[n].emp_mes.valor_sub_total, mestotal.mes[n].emp_mes.valor_bonus_total,
                                mestotal.mes[n].emp_mes.valor_segsoc_total, mestotal.mes[n].emp_mes.valor_total);
                    }
                }
                fclose(fp);
            } else {
                printf(ERR_FILE_N_GRAV_PS, file);
            }
        } else {
            printf(ERR_ANO_N_EXISTE, ano);
        }
    } else {
        printf(ERR_MESES_0);
    }
}

int ver_func_ano(MESES_TOTAL mes, int ano, int cod) {
    int n, cont = 0;
    if (mes.cont != 0) {
        for (int i = 0; i < mes.cont; i++) {
            if (mes.mes[i].ano == ano) {
                for (int j = 0; j < mes.mes[i].cont; j++) {
                    if (mes.mes[i].funcionario[j].cod == cod) {
                        cont++;
                    }
                }
            }
        }
    }
    return cont;
}

int ver_func_ano_mes(MESES_TOTAL mesestotal, int ano, int cod, int mes) {
    int n, cont = 0;
    if (mesestotal.cont != 0) {
        for (int i = 0; i < mesestotal.cont; i++) {
            if (mesestotal.mes[i].ano == ano && mesestotal.mes[i].mes == mes) {
                for (int j = 0; j < mesestotal.mes[i].cont; j++) {
                    if (mesestotal.mes[i].funcionario[j].cod == cod) {
                        return j;
                    }
                }
            }
        }
    }
    return -1;
}

void Listar_funcionario_ano(MESES_TOTAL mestotal) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int ver, n, m;
    int cod = obterInt(MIN_COD, MAX_COD, MSG_OBT_COD_LIST, VAL_INV);
    int ano = obterInt(MIN_ANO_PS, tm->tm_year + 1900, MSG_OBTER_ANO, INV_DATA_ANO);
    ver = ver_func_ano(mestotal, ano, cod);
    if (ver_func_ano(mestotal, ano, cod) > 0) {
        if (ver < 12) {
            printf(ERR_MESES_FUNC_EXIST, ver, cod, ano);
        }
        printf("----------------------------------Informações monetarias relativamente ao Funcionario:%d no Ano:%d------------------------------------\n", cod, ano);
        printf("|----|                  Dias                 |------------------------------------------------------------------------------------------|\n");
        printf("|Mes:|Completos:|Meios:|Fim de semana:|Falta:|Valor Bruto:|Valor Sub.Alimentação:|Valor Bonus:|Valor IRS:|Valor Seg.Soc.:|Valor Liquido:|\n");
        for (int i = 0; i < MAX_MES_PS; i++) {
            m = ver_mes(mestotal, ano, i);
            n = ver_func_ano_mes(mestotal, ano, cod, i);
            if (n != -1 && m != -1) {
                if (mestotal.mes[m].funcionario[n].calculado == 1) {
                    printf(" %d       %d        %d         %d         %d       %.1f€              %.1f€             %.1f€      %.1f€          %.1f€         %.1f€\n", i, mestotal.mes[m].funcionario[n].dias_comp, mestotal.mes[m].funcionario[n].dias_meio, mestotal.mes[m].funcionario[n].dias_fimsemana, mestotal.mes[m].funcionario[n].dias_faltas, mestotal.mes[m].funcionario[n].func.valor_bruto, mestotal.mes[m].funcionario[n].func.valor_sub_alimentacao, mestotal.mes[m].funcionario[n].func.valor_bonus, mestotal.mes[m].funcionario[n].func.valor_irs_funcionario, mestotal.mes[m].funcionario[n].func.valor_segsoc_funcionario, mestotal.mes[m].funcionario[n].func.valor_liquido);
                } else {
                    printf(" %d       %d        %d         %d         %d       ----              -----             ------       -----          -----         -----\n", mestotal.mes[m].funcionario[n].cod, mestotal.mes[m].funcionario[n].dias_comp, mestotal.mes[m].funcionario[n].dias_meio, mestotal.mes[m].funcionario[n].dias_fimsemana, mestotal.mes[m].funcionario[n].dias_faltas);
                }
            }
        }
    } else {
        printf(ERR_FUNC_S_SAL_ANO, cod, ano);
    }
}