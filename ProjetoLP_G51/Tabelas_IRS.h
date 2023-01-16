/**
 * @file Tabelas_IRS.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Este modulo contem todas as funções relativas as tabelas de IRS
 */


#ifndef TABELAS_H
#define TABELAS_H

#ifdef __cplusplus
extern "C" {
#endif

    //Mensagens Gerais
#define FILE_TAB_0 "info\\Tab_solteiro.txt"
#define FILE_TAB_1 "info\\Tab_casado.txt"
#define FILE_TAB_2 "info\\Tab_casado_2.txt"
#define MSG_VAL_IGUAL "%.1f€ igualado a %.1f€\n"
#define MSG_PRINT_TAB_0 "\t-Tabela de IRS de Solteiro-\n"
#define MSG_PRINT_TAB_1 "\t-Tabela de IRS de Casado 1 Titular-\n"
#define MSG_PRINT_TAB_2 "\t-Tabela de IRS de Casado 2 Titulares-\n"
#define MSG_OBT_NLINHA_CRIAR "Insira o nº da linha que irá inserir uma nova linha(A linha inserida irá passar a linha inserida atual e as seguintes para as proximas linhas):"
#define MSG_OBT_NLINHA_APG "Insira o nº da linha que deseja apagar:"
#define MSG_TAB_IRS_LINHA_CRIADA "A linha %d foi criada.\n"
#define MSG_TAB_IRS_LINHA_ALT "A linha %d foi alterada.\n"
#define MSG_TAB_IRS_LINHA_APG "A linha %d foi apagada.\n"
#define MSG_OBT_NLINHA_ALT "Insira nº da linha que deseja alterar:"
#define MSG_OBT_PORC_D0 "Insira o valor da percentagem da taxa de 0 dependentes:"
#define MSG_OBT_PORC_D1 "Insira o valor da percentagem da taxa de 1 dependentes:"
#define MSG_OBT_PORC_D2 "Insira o valor da percentagem da taxa de 2 dependentes:"
#define MSG_OBT_PORC_D3 "Insira o valor da percentagem da taxa de 3 dependentes:"
#define MSG_OBT_PORC_D4 "Insira o valor da percentagem da taxa de 4 dependentes:"
#define MSG_OBT_PORC_D5 "Insira o valor da percentagem da taxa de 5+ dependentes:"
#define MSG_OBT_VAL_ATE "Insira até que valor as taxas devem ser aplicadas:"
#define MSG_OBT_VAL_SUP "Insira apartir de que valor as taxas devem ser aplicadas:"
#define MSG_PERG_TABS_IRS_GUARDAR "Deseja Guardar as Tabelas em ficheiros(S/N)?"
#define MSG_INFO_GRAV "Gravou a Tabela no ficheiro %s\n"
#define MSG_LER_FILE_TAB_IRS_1 "Insira o destino do Ficheiro da Tabela de IRS de Solteiro onde deseja carregar(Completo/Parcial):"
#define MSG_LER_FILE_TAB_IRS_3 "Insira o destino do Ficheiro da Tabela de IRS de Casado 2 Titulares onde deseja carregar(Completo/Parcial):"
#define MSG_LER_FILE_TAB_IRS_2 "Insira o destino do Ficheiro da Tabela de IRS de Casado 1 Titular onde deseja carregar(Completo/Parcial):"
#define MSG_GRAV_FILE_TAB_IRS_1 "Insira o destino do Ficheiro da Tabela de IRS de Solteiro onde deseja guardar(Completo/Parcial):"
#define MSG_GRAV_FILE_TAB_IRS_3 "Insira o destino do Ficheiro da Tabela de IRS de Casado 2 Titulares onde deseja guardar(Completo/Parcial):"
#define MSG_GRAV_FILE_TAB_IRS_2 "Insira o destino do Ficheiro da Tabela de IRS de Casado 1 Titular onde deseja guardar(Completo/Parcial):"
    
    //Mensagens de Erro
#define ERR_FILE_N_EXISTE "O ficheiro %s nao existe\n"
#define ERR_FILE_N_CARR "O ficheiro %s nao contém tabela\n"
#define ERR_FILE_N_GRAV "A tabela não contém linhas para guardar\n"
#define ERR_TAB_IRS_VAZIA "A tabela está vazia\n"
#define ERR_ULT_LINHA "Na Tabela a ultima linha e penultima linha têm de ter valor (€) iguais:\n"
#define MSG_CONT_ERR_ULT_LINHA "Deseja igualar as linhas(S/N)?"
#define MSG_CONT_ERR_ULT_LINHA_OBT_NLINHA "Insira o nº da linha que deseja que ambos os valores fiquem iguais:"  
#define ERR_FILE_IRS "Tipo de ficheiro invalido(.csv)!"
#define OPC_INV_TAB_IRS "Opção invalida.\n"
#define VAL_INV_LINHA "Linha invalida\n"
#define VAL_INV_VALOR "Valor invalido\n"
#define VAL_INV_PORC "Porcentagem invalida\n"   

    //Constantes
#define MIN_LINHA 1
#define MAX_TAX 100
#define MIN_VAL_IRS 0
#define MAX_VAL_IRS 99999.0
#define QUANT_TABS 3
#define COLUNAS 7
#define VAL_MIN_OPC_TAB_IRS 0
#define VAL_MAX_OPC_TAB_IRS 9

    /**
     * Estrutura com de cada linha das tabelas de IRS 
     *              Indices:
     * 0-Valor/1-D0/2-D1/3-D2/4-D3/5-D4/6-D5
     */
    typedef struct {
        float col[COLUNAS];
    } linha;

    /**
     * Estrutura de cada Tabela de IRS com as variaveis de o tamanho alocado na memoria para as linhas da tabela de IRS
     * e o contador de linhas ocupadas com informação desse tamanho alocado e o apontador da a memoria dinamica para as linhas
     */
    typedef struct {
        int cont;//Contador referente as linhas da Tabelas de IRS na memoria dinamica com a informação
        int tam;//Tamanho alocado para as linhas da Tabelas de IRS na memoria dinamica 
        linha *Linha; //Apontador para as linhas da Tabela de IRS
    } Tab_IRS;

    /**
     * Esta função tem o propósito de carregar de uma ficheiro em .csv para memória dinámica os valores de uma tabela de IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     * @param file recebe como argumento um array de caracteres
     * @return dá return de um inteiro com significado de um boolean
     */
    int carregar_tab_IRS(Tab_IRS *Tabs, char *file);
    /**
     * Esta função imprime os valores da variavel da estrutura Tab_IRS
     * 
     * @param Tabs recebe como argumento uma variavel da estrutura Tab_IRS 
     */
    void print_tab(Tab_IRS Tabs);
    /**
     * Esta função tem como finalidade guardar o valor das variáveis para um ficheiro .csv
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     * @param file recebe como argumento um array de caracteres
     */
    void guardar_tab(Tab_IRS *Tabs, char *file);
    /**
     * Esta função tem como finalidade apagar valores de uma linha especifica da struct Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     */
    void apagar_linha(Tab_IRS *Tabs);
    /**
     * Esta função serve para linha com valores inseridos pelo utilizador para serem inseridos na struct de Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     */
    void criar_linha(Tab_IRS *Tabs);
    /**
     * Esta função serve para alterar os valores de uma linha especifica da struct de Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     */
    void alt_linha(Tab_IRS *Tabs);
    /**
     * Esta função serve para imprimir no ecra os valores de uma linha especifica da struct de Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     */
    void ver_vals(Tab_IRS *Tabs);
    /**
     * Esta função tem como objetivo alocar mais espaço na memória dinamica para as variáveis da struct Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     */
    void expandir_linhas(Tab_IRS *Tabs);
    /**
     * Esta função troca as linhas para a criação da linha no meio da tabela da stuct Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     * @param linha recebe como argumento um inteiro
     */
    void swap_linhas_criar(Tab_IRS *Tabs, int linha);
    /**
     * Esta função troca as linhas para a eliminação da linha no meio da tabela da stuct Tab_IRS
     * 
     * @param Tabs recebe como argumento um apontador da struct Tab_IRS
     * @param linha recebe como argumento um inteiro
     */
    void swap_linhas_eliminar(Tab_IRS *Tabs, int linha);
    /**
     * Esta função carrega os valores mínimmos e máximos de cada linha referente à struct linha referente à Tab_IRS
     * 
     * @param min recebe como argumento um apontador da struct linha
     * @param max recebe como argumento um apontador da struct linha
     * @param Tabs recebe como argumento uma variavel da struct Tab_IRS
     * @param nlinha recebe como argumento um inteiro
     */
    void load_min_max(linha *min, linha *max, Tab_IRS Tabs, int nlinha);

#ifdef __cplusplus
}
#endif
#endif /* TABELAS_H */

