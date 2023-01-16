/**
 * @file main.c
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Contem os Menus. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tabelas_IRS.h"
#include "Funcionarios.h"
#include "logs.h"
#include "SegSoc.h"
#include "input.h"
#include "Proc_Salario.h"
#include "Ficheiros.h"

//Mensagens dos menus
#define OPC_ESC "\t\tEscolha uma das opções:\n"
#define MENU_PRINCIPAL "\t\t   -Menu Principal-\n"
#define MENU_FUNC "\t   -Menu de Gestão de Funcionarios-\n"
#define MENU_TAB_SS "     -Menu de Gestão da Tabela da Segurança Social-\n"
#define MENU_TAB_IRS "\t  -Menu de Gestão da Tabela do IRS-\n"
#define MENU_PROC_SAL "\t  -Menu de Processamento de Salario-\n"
#define OPCS_MENU_PRINC "1.Gerir Funcionarios\t\t\t2.Processar Salarios\n3.Gerir Tabela de Descontos da SS\t4.Gerir Tabela de retenção do IRS\n9.Sair\n"
#define OPCS_MENU_FUNC "1.Criar Funcionario\t\t\t2.Editar Funcionario\n3.Remover Funcionario\t\t\t4.Listar Funcionarios Existente\n5.Gravar Funcionarios em ficheiros\t6.Carregar Funcionarios de um ficheiro\n0.Voltar ao menu anterior\n"
#define OPCS_MENU_TAB_SS "1.Adicionar Critério\t\t2.Alterar Criterio\n3.Apagar Criterio\t\t4.Gravar Tabela de Criterios em ficheiro\n5.Carregar Tabela de Criterios\t0.Voltar ao menu anterior\n  de um ficheiro\n"
#define OPCS_MENU_TAB_IRS "1.Aceder a Tabela de Solteiro\t\t2.Aceder a Tabela Casado 1 Titular\n3.Aceder a Tabela Casado 2 Titulares\t4.Listar todas as Tabelas\n5.Gravar Tabelas em ficheiro\t\t6.Carregar Tabelas de ficheiros\n0.Voltar ao menu anterior\n"
#define OPCS_MENU_TAB_IRS_OPC "1.Criar linha\t\t2.Apagar linha\n3.Alterar linha\t\t4.Gravar tabela\n5.Carregar Tabela\t0.Voltar ao menu anterior\n"
#define OPCS_MENU_PROC_SAL "1.Calcular Salarios\t\t\t2.Menu de Listar depesas de Meses Calculados\n3.Guardar Meses Calculados em ficheiro\t4.Guardar depesas de ano em ficheiro\n5.Carregar Mes Calculado de um ficheiro\t6.Menu Tabela de Bonus\n0.Voltar ao menu anterior\n"
#define MENU_TAB_BONUS "\t-Menu da Tabela de Bonus-\n"
#define OPCS_MENU_TAB_BONUS "1.Criar linha\t\t2.Alterar linha\n3.Apagar linha\t\t4.Carregar Tabela\n5.Gravar Tabela\t\t6.Listar o maior bonus que cada funcionario tem direito\n0.Sair\n"

//Mensagens de Erro
#define OPC_INV "Opção invalida.\n"

//Constantes
#define VAL_MIN_OPC 0
#define VAL_MAX_OPC 9
#define MAX_QUANT 3

int main(int argc, char** argv) {
    int opc;
    Funcs funcs = {.cont = 0, .tam = 0};
    Tab_IRS tabelas_irs[QUANT_TABS];
    Tab_Bonus tabela_bonus = {.cont = 0, .tam = 0};
    MESES_TOTAL mes_total = {.cont = 0, .tam = 0};
    char file[MAX_FILE];
    for (int i = 0; i < MAX_QUANT; i++) {
        tabelas_irs[i].cont = 0;
        tabelas_irs[i].tam = 0;
    }
    Tab_SS tabela_SS = {.cont = 0, .tam = 0};
    logMsg(LOG_INIC, LOG_FILE);
    do {
        printf(MENU_PRINCIPAL); // Menu Principal
        printf(OPC_ESC);
        opc = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_PRINC, OPC_INV);
        switch (opc) {
            case 1:
                logMsg(LOG_OPC_FUNC, LOG_FILE);
                do {
                    printf(MENU_FUNC); // Menu Funcionário
                    printf(OPC_ESC);
                    opc = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_FUNC, OPC_INV);
                    switch (opc) {
                        case 1:
                            func_add(&funcs);
                            logMsg(LOG_OPC_FUNC_CRIAR, LOG_FILE);
                            break;
                        case 2:
                            func_edit(&funcs);
                            logMsg(LOG_OPC_FUNC_EDIT, LOG_FILE);
                            break;
                        case 3:
                            func_remove(&funcs);
                            logMsg(LOG_OPC_FUNC_REMOVE, LOG_FILE);
                            break;
                        case 4:
                            func_list(funcs);
                            logMsg(LOG_OPC_FUNC_LIST, LOG_FILE);
                            break;
                        case 5:
                            lerString(file, MAX_FILE, MSG_GRAV_FILE);
                            guardar_Funcs(&funcs, file);
                            logMsg_file(LOG_OPC_FUNC_GRAVAR, LOG_FILE, file);
                            break;
                        case 6:
                            lerString(file, MAX_FILE, MSG_LER_FILE);
                            carregar_Funcs(&funcs, file);
                            logMsg_file(LOG_OPC_FUNC_CARR, LOG_FILE, file);
                            break;
                        case 0:
                            logMsg(LOG_OPC_SAIR_MENU, LOG_FILE);
                            break;
                        default:
                            printf(OPC_INV);
                            break;
                    }
                } while (opc != 0);
                break;
            case 2:
                logMsg(LOG_OPC_SAL, LOG_FILE);
                int opc2 = 0;
                do {
                    printf(MENU_PROC_SAL); // Menu Processamento de Salário
                    printf(OPC_ESC);
                    opc = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_PROC_SAL, OPC_INV);
                    switch (opc) {
                        case 1:
                            calculo_salario(&funcs, tabelas_irs, &tabela_SS, &tabela_bonus, &mes_total);
                            logMsg(LOG_OPC_CALC_SAL, LOG_FILE);
                            break;
                        case 2:
                            menu_Listar_ano_mes(mes_total);
                            break;
                        case 3:
                            lerString(file, MAX_FILE, MSG_GRAV_FILE);
                            guardar_Salario_Calculado(&mes_total, file);
                            logMsg_file(LOG_OPC_GRAV_SAL, LOG_FILE, file);
                            break;
                        case 4:
                            lerString(file, MAX_FILE, MSG_GRAV_FILE);
                            guardar_ficheiro_Despesas_ano(mes_total, file);
                            logMsg_file(LOG_OPC_GRAV_ANO, LOG_FILE, file);
                            break;
                        case 5:
                            lerString(file, MAX_FILE, MSG_LER_FILE);
                            carregar_Salario_Calculado(&mes_total, file);
                            logMsg_file(LOG_OPC_CARR_SAL, LOG_FILE, file);
                            break;
                        case 6:
                            logMsg(LOG_OPC_TAB_BONUS, LOG_FILE);
                            do {

                                printf(MENU_TAB_BONUS); // Menu Tabela de bonus
                                Proc_Salario_Bonus_list(tabela_bonus);
                                printf(OPC_ESC);
                                opc2 = obterInt(VAL_MIN_OPC_PS, VAL_MAX_OPC_PS, OPCS_MENU_TAB_BONUS, VAL_INV);
                                switch (opc2) {
                                    case 1:
                                        logMsg(LOG_OPC_TAB_BONUS_CRIOU, LOG_FILE);
                                        Proc_Salario_Bonus_add(&tabela_bonus);
                                        break;
                                    case 2:
                                        logMsg(LOG_OPC_TAB_BONUS_ALT, LOG_FILE);
                                        Proc_Salario_edit_Bonus(&tabela_bonus);
                                        break;
                                    case 3:
                                        logMsg(LOG_OPC_TAB_BONUS_APG, LOG_FILE);
                                        Proc_Salario_remove_Bonus(&tabela_bonus);
                                        break;
                                    case 4:
                                        logMsg_file(LOG_OPC_TAB_BONUS_CARR, LOG_FILE, file);
                                        lerString(file, MAX_FILE, MSG_LER_FILE);
                                        carregar_Proc_Salario_Bonus(&tabela_bonus, file);
                                        break;
                                    case 5:
                                        logMsg_file(LOG_OPC_TAB_BONUS_GRAV, LOG_FILE, file);
                                        lerString(file, MAX_FILE, MSG_GRAV_FILE);
                                        guardar_Proc_Salario_Bonus(tabela_bonus, file);
                                        break;
                                    case 6:
                                        logMsg(LOG_OPC_TAB_BONUS_LIST, LOG_FILE);
                                        listar_func_bonus(funcs, tabela_bonus);
                                        break;
                                    case 0:
                                        logMsg(LOG_OPC_TAB_BONUS_SAIR, LOG_FILE);
                                        break;
                                    default:
                                        printf(OPC_INV);
                                        break;
                                }
                            } while (opc2 != 0);
                            break;
                        case 0:
                            break;

                    }
                } while (opc != 0);
                break;
            case 3:
                logMsg(LOG_OPC_TAB_SS, LOG_FILE); //Menu da Tabela da SS
                do {
                    printf(MENU_TAB_SS);
                    SegSoc_list(tabela_SS);
                    printf(OPC_ESC);
                    opc = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_TAB_SS, OPC_INV);
                    switch (opc) {
                        case 1:
                            SegSoc_add(&tabela_SS);
                            logMsg(LOG_OPC_TAB_SS_ADD, LOG_FILE);
                            break;
                        case 2:
                            SegSoc_edit(&tabela_SS);
                            logMsg(LOG_OPC_TAB_SS_ALT, LOG_FILE);
                            break;
                        case 3:
                            SegSoc_remove(&tabela_SS);
                            logMsg(LOG_OPC_TAB_SS_APG, LOG_FILE);
                            break;
                        case 4:
                            lerString(file, MAX_FILE, MSG_GRAV_FILE);
                            guardar_SegSoc(&tabela_SS, file);
                            logMsg_file(LOG_OPC_TAB_SS_GRAVAR, LOG_FILE, file);
                            break;
                        case 5:
                            lerString(file, MAX_FILE, MSG_LER_FILE);
                            carregar_SegSoc(&tabela_SS, file);
                            logMsg_file(LOG_OPC_TAB_SS_CARR, LOG_FILE, file);
                            break;
                        case 0:
                            logMsg(LOG_OPC_SAIR_MENU, LOG_FILE);
                            break;
                        default:
                            printf(OPC_INV);
                            break;
                    }
                } while (opc != 0);
                break;
            case 4:
                logMsg(LOG_OPC_TAB_IRS, LOG_FILE);
                do {
                    int opc1;
                    printf(MENU_TAB_IRS); //Menu da Tabela de IRS
                    printf(OPC_ESC);
                    opc = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_TAB_IRS, OPC_INV);
                    switch (opc) {
                        case 1:
                            do {
                                printf(MSG_PRINT_TAB_0); //Menu da Tabela de IRS de solteiro
                                print_tab(tabelas_irs[opc - 1]);
                                logMsg(LOG_OPC_TAB_IRS_1, LOG_FILE);
                                opc1 = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_TAB_IRS_OPC, OPC_INV);
                                switch (opc1) {
                                    case 1:
                                        criar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_CRIOU, LOG_FILE);
                                        break;
                                    case 2:
                                        apagar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_APG, LOG_FILE);
                                        break;
                                    case 3:
                                        alt_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_ALT, LOG_FILE);
                                        break;
                                    case 4:
                                        lerString(file, MAX_FILE, MSG_GRAV_FILE);
                                        guardar_tab(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_SOLT, LOG_FILE, file);
                                        break;
                                    case 5:
                                        lerString(file, MAX_FILE, MSG_LER_FILE);
                                        carregar_tab_IRS(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_1, LOG_FILE, file);
                                        break;
                                    case 0:
                                        logMsg(LOG_OPC_VOLT_MENU_ANT_TAB_IRS, LOG_FILE);
                                        break;
                                    default:
                                        printf(OPC_INV);
                                        break;
                                }
                            } while (opc1 != 0);
                            break;
                        case 2:
                            do {
                                printf(MSG_PRINT_TAB_1); //Menu da Tabela de IRS de casado 1 titular
                                print_tab(tabelas_irs[opc - 1]);
                                logMsg(LOG_OPC_TAB_IRS_2, LOG_FILE);
                                opc1 = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_TAB_IRS_OPC, OPC_INV);
                                switch (opc1) {
                                    case 1:
                                        criar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_CRIOU, LOG_FILE);
                                        break;
                                    case 2:
                                        apagar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_APG, LOG_FILE);
                                        break;
                                    case 3:
                                        alt_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_ALT, LOG_FILE);
                                        break;
                                    case 4:
                                        lerString(file, MAX_FILE, MSG_GRAV_FILE);
                                        guardar_tab(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_CAS, LOG_FILE, file);
                                        break;
                                    case 5:
                                        lerString(file, MAX_FILE, MSG_LER_FILE);
                                        carregar_tab_IRS(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_2, LOG_FILE, file);
                                        break;
                                    case 0:
                                        logMsg(LOG_OPC_VOLT_MENU_ANT_TAB_IRS, LOG_FILE);
                                        break;
                                    default:
                                        printf(OPC_INV);
                                        break;

                                }
                            } while (opc1 != 0);
                            break;
                        case 3:
                            do {
                                printf(MSG_PRINT_TAB_2); //Menu da Tabela de IRS de casado 2 titulares
                                print_tab(tabelas_irs[opc - 1]);
                                logMsg(LOG_OPC_TAB_IRS_3, LOG_FILE);
                                opc1 = obterInt(VAL_MIN_OPC, VAL_MAX_OPC, OPCS_MENU_TAB_IRS_OPC, OPC_INV);
                                switch (opc1) {
                                    case 1:
                                        criar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_CRIOU, LOG_FILE);
                                        break;
                                    case 2:
                                        apagar_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_APG, LOG_FILE);
                                        break;
                                    case 3:
                                        alt_linha(&tabelas_irs[opc - 1]);
                                        logMsg(LOG_OPC_TAB_IRS_ALT, LOG_FILE);
                                        break;
                                    case 4:
                                        lerString(file, MAX_FILE, MSG_GRAV_FILE);
                                        guardar_tab(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_CAS2, LOG_FILE, file);
                                        break;
                                    case 5:
                                        lerString(file, MAX_FILE, MSG_GRAV_FILE);
                                        carregar_tab_IRS(&tabelas_irs[opc - 1], file);
                                        logMsg_file(LOG_OPC_TAB_IRS_3, LOG_FILE, file);
                                        break;
                                    case 0:
                                        logMsg(LOG_OPC_VOLT_MENU_ANT_TAB_IRS, LOG_FILE);
                                        break;
                                    default:
                                        printf(OPC_INV);
                                        break;

                                }
                            } while (opc1 != 0);
                            break;
                        case 4:
                            logMsg(LOG_OPC_TAB_IRS_LIST, LOG_FILE);
                            for (int i = 0; i < QUANT_TABS; i++) {
                                if (i == 0) {
                                    printf(MSG_PRINT_TAB_0);
                                } else if (i == 1) {
                                    printf(MSG_PRINT_TAB_1);
                                } else {
                                    printf(MSG_PRINT_TAB_2);
                                }
                                print_tab(tabelas_irs[i]);
                            }
                            break;
                        case 5:
                            for (int i = 0; i < QUANT_TABS; i++) {
                                if (i == 0) {
                                    lerString(file, MAX_FILE, MSG_LER_FILE_TAB_IRS_1);
                                    logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_SOLT, LOG_FILE, file);
                                } else if (i == 1) {
                                    lerString(file, MAX_FILE, MSG_LER_FILE_TAB_IRS_2);
                                    logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_CAS, LOG_FILE, file);
                                } else if (i == 2) {
                                    lerString(file, MAX_FILE, MSG_LER_FILE_TAB_IRS_3);
                                    logMsg_file(LOG_OPC_TAB_IRS_GRAVAR_CAS2, LOG_FILE, file);
                                }
                                guardar_tab(&tabelas_irs[i], file);
                            }
                            break;
                        case 6:
                            for (int i = 0; i < QUANT_TABS; i++) {
                                if (i == 0) {
                                    lerString(file, MAX_FILE, MSG_GRAV_FILE_TAB_IRS_1);
                                    logMsg_file(LOG_OPC_TAB_IRS_CARR_SOLT, LOG_FILE, file);
                                } else if (i == 1) {
                                    lerString(file, MAX_FILE, MSG_GRAV_FILE_TAB_IRS_2);
                                    logMsg_file(LOG_OPC_TAB_IRS_CARR_CAS, LOG_FILE, file);
                                } else if (i == 2) {
                                    lerString(file, MAX_FILE, MSG_GRAV_FILE_TAB_IRS_3);
                                    logMsg_file(LOG_OPC_TAB_IRS_CARR_CAS2, LOG_FILE, file);
                                }
                                carregar_tab_IRS(&tabelas_irs[i], file);
                            }
                            break;
                        case 0:
                            logMsg(LOG_OPC_SAIR_MENU, LOG_FILE);
                            break;
                        default:
                            printf(OPC_INV);
                            break;
                    }
                } while (opc != 0);
                break;
            case 9:
                logMsg(LOG_OPC_SAIR, LOG_FILE);
                break;
            default:
                printf(OPC_INV);
                break;
        }
        //free da memoria dinamica se tiver tamanho alocado
    } while (opc != 9);
    if (funcs.tam > 0) {
        free(funcs.func);
    }
    for (int i = 0; i < MAX_QUANT; i++) {
        if (tabelas_irs[i].tam > 0) {
            free(tabelas_irs[i].Linha);
        }
    }
    if (tabela_SS.tam > 0) {
        free(tabela_SS.linha);
    }
    if (mes_total.tam > 0) {
        for (int j = 0; j < mes_total.tam; j++) {
            if (mes_total.mes[j].tam > 0) {
                free(mes_total.mes[j].funcionario);
            }
        }
        free(mes_total.mes);
    }
    if (tabela_bonus.tam > 0) {
        free(tabela_bonus.linha);
    }
    return (EXIT_SUCCESS);
}