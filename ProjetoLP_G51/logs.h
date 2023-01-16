/**
 * @file logs.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * @brief Este modulo contem todas as funções relativas ao relatorio de utilização do programa
 */

#ifndef LOGS_H
#define LOGS_H

#ifdef __cplusplus
extern "C" {
#endif


    //Mensagens de Log do menu principal
#define LOG_INIC "Iniciou o Programa."
#define LOG_OPC_SAIR_MENU "Voltou ao menu Principal."
#define LOG_OPC_SAIR "Saiu do Programa."

    //Mensagens de Log do menu funcionario
#define LOG_OPC_FUNC "Menu de Funcionario."
#define LOG_OPC_FUNC_CRIAR "Criou Funcionario."
#define LOG_OPC_FUNC_EDIT "Editou Informação de Funcionario."
#define LOG_OPC_FUNC_REMOVE "Removeu Funcionario."
#define LOG_OPC_FUNC_LIST "Listou os funcionarios."
#define LOG_OPC_FUNC_GRAVAR "Gravou os funcionarios no ficheiro"
#define LOG_OPC_FUNC_CARR "Carregou os funcionarios do ficheiro"

    //Mensagens de Log do menu de processamento de salario
#define LOG_OPC_SAL "Processou Salario"
#define LOG_OPC_CALC_SAL "Calculou Salarios"
#define LOG_OPC_LIST_MENU "Acedeu ao menu de Listar depesas da empresa"
#define LOG_OPC_LIST_MES "Listou mes."
#define LOG_OPC_LIST_ANO "Listou ano."
#define LOG_OPC_CARR_SAL "Carregou informações monetarias do ficheiro "
#define LOG_OPC_GRAV_SAL "Gravou informações monetarias relativas ao mês no ficheiro "
#define LOG_OPC_GRAV_ANO "Gravou informações monetarias relativas ao ano no ficheiro "

    //Mensagens de Log do menu das Tabelas de IRS
#define LOG_OPC_TAB_IRS "Menu do IRS."
#define LOG_OPC_VOLT_MENU_ANT_TAB_IRS "Voltou ao Menu das Tabelas do IRS."
#define LOG_OPC_TAB_IRS_GRAVAR_SOLT "Gravou a Tabela do IRS de Solteiro no ficheiro"
#define LOG_OPC_TAB_IRS_GRAVAR_CAS "Gravou a Tabela do IRS de Casado 1 Titular no ficheiro"
#define LOG_OPC_TAB_IRS_GRAVAR_CAS2 "Gravou a Tabela do IRS de Casado 2 Titular no ficheiro"
#define LOG_OPC_TAB_IRS_CARR_SOLT "Carregou a Tabela do IRS de Solteiro do ficheiro"
#define LOG_OPC_TAB_IRS_CARR_CAS "Carregou a Tabela do IRS de Casado 1 Titular do ficheiro"
#define LOG_OPC_TAB_IRS_CARR_CAS2 "Carregou a Tabela do IRS de Casado 2 Titular do ficheiro"
#define LOG_OPC_TAB_IRS_1 "Acedeu a Tabela de IRS de Solteiro." 
#define LOG_OPC_TAB_IRS_2 "Acedeu a Tabela de IRS de Casado 1 Titular." 
#define LOG_OPC_TAB_IRS_3 "Acedeu a Tabela de IRS de Casado 2 Titulares." 
#define LOG_OPC_TAB_IRS_CRIOU "Criou linha na Tabela do IRS."
#define LOG_OPC_TAB_IRS_ALT "Alterou linha na Tabela do IRS."
#define LOG_OPC_TAB_IRS_APG "Apagou linha na Tabela do IRS."
#define LOG_OPC_TAB_IRS_LIST "Listou todas as Tabelas do IRS."

    //Mensagens de Log do menu da Tabela da Segurança social
#define LOG_OPC_TAB_SS "Menu da SS."
#define LOG_OPC_TAB_SS_GRAVAR "Gravou a Tabela da segurança social no ficheiro"
#define LOG_OPC_TAB_SS_CARR "Carregou a Tabela da segurança social do ficheiro"
#define LOG_OPC_TAB_SS_ADD "Adicionou criterio na Tabela de segurança social."
#define LOG_OPC_TAB_SS_APG "Apagou criterio na Tabela de segurança social."
#define LOG_OPC_TAB_SS_ALT "Alterou criterio na Tabela de segurança social." 
#define LOG_OPC_TAB_SS_LIST "Listou criterio na Tabela de segurança social."

    //Mensagens de Log do menu da Tabela de bonus
#define LOG_OPC_TAB_BONUS "Acedeu ao menu da tabela de bonus."
#define LOG_OPC_TAB_BONUS_SAIR "Voltou ao menu do processamento de salario."
#define LOG_OPC_TAB_BONUS_GRAV "Gravou a Tabela de Bonus no ficheiro"
#define LOG_OPC_TAB_BONUS_CARR "Carregou a Tabela de Bonus do ficheiro"
#define LOG_OPC_TAB_BONUS_CRIOU "Adicionou criterios na Tabela de Bonus."
#define LOG_OPC_TAB_BONUS_APG "Apagou criterios na Tabela de Bonus."
#define LOG_OPC_TAB_BONUS_ALT "Alterou criterios na Tabela de Bonus."
#define LOG_OPC_TAB_BONUS_LIST "Listou o maior bonus que cada funcionario pode ter direito"
    
    //Constante do ficheiro LOG
#define LOG_FILE "log.txt"

    /**
     * Esta função tem como objetivo guardar a data e o que foi alterado para um ficheiro de texto
     * 
     * @param msg recebe como argumento um array de caracteres
     * @param filename recebe como argumento um array de caracteres
     */
    void logMsg(char *msg, char *filename);
    /**
     * Esta função tem como objetivo guardar a data e o que foi alterado para um ficheiro de texto mas diz também o nome do ficheiro
     * 
     * @param msg recebe como argumento um array de caracteres
     * @param filename recebe como argumento um array de caracteres
     * @param filename_1 recebe como argumento um array de caracteres
     */
    void logMsg_file(char *msg, char *filename, char *filename_1);

#ifdef __cplusplus
}
#endif

#endif /* FUNC_H */

