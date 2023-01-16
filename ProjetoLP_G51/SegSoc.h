/**
 * @file SegSoc.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Este modulo contem todas as funções relativas a segurança social
 */


#ifndef SEGSOC_H
#define SEGSOC_H

#ifdef __cplusplus
extern "C" {
#endif

    //Mensagens Gerais
#define MSG_EDIT_FUNCAO_SS "Deseja alterar o nome da função a qual esta taxa será aplicada(S/N)?"
#define MSG_EDIT_TIPO_OU_FUNCAO_SS "Deseja alterar "
#define MSG_OBT_FUNCAO_SS "Insira o nome da função a que se vai aplicar a taxa:"
#define MSG_EDIT_LINHA "Linha da tabela de segurança social editada com sucesso.\n"
#define MSG_EDIT_TRABALHADOR "Deseja editar o valor a pagar pelo trabalhador que se aplica o critério(S/N)?"
#define MSG_EDIT_ENTEMPREGADORA "Deseja editar o valor a pagar pela entidade empregadora que se aplica o critério(S/N)?"
#define MSG_EDIT_AUTO "Deseja inserir como data "
#define MSG_EDIT_TIPO "Deseja editar a que tipo de cargo se aplica o critério(S/N)?"
#define MSG_EDIT_TAB_SS "Tabela da segurança social editada com sucesso.\n"    
#define MSG_REMOV_TAB_SS "Linha removida com sucesso.\n"
#define MSG_OBT_NLINHA_REM "Insira o número da linha que deseja remover:"
#define MSG_OBT_NLINHA_EDIT "Insira o número da linha que deseja editar:"
#define MSG_CRIADO_TAB_SS "Valores foram adicionados a tabela.\n"
#define MSG_OBT_VALOR_ENTEMPREGADORA "Insira a taxa a pagar pela entidade empregadora para a segurança social:"
#define MSG_OBT_VALOR_TRABALHADOR "Insira a taxa a pagar pelo funcionário para a segurança social:"
#define MSG_SEGSOC_ADD "Opção de adicionar valores a tabela de Segurança Social escolhida.\n"
#define MSG_OBT_TIPO "A qual cargo este criterio aplica-se(1-Chefes/2-Administradores/3-Funcionarios):"    
#define MSG_SEGSOC_CARR "Tabelas carregadas do Ficheiro %s\n"
#define MSG_GUARDAR_TAB_SS "Tabela guardada no ficheiro %s\n"
#define MSG_LIST_TAB_SS "Lista de taxas contributivas foram carregadas.\n"
#define MSG_CARGO_FUNCAO "Deseja fazer para uma função especifica(S/N)?"

    //Mensagens de Erro
#define MSG_SEGSOC_N_CARR " %d sem tabela de segurança social.\n"    
#define ERR_N_EXISTE_LINHAS "Não existe linhas para editar.\n"    
#define ERR_SEGSOC_VAZIA_LISTA "Tabela vazia. \n"    
#define ERR_FILE_N_EXISTE_TAB_SS "Ficheiro %s não existe.\n"
#define ERR_VAZIA_GUARDAR_TAB_SS "Sem tabelas para Guardar no ficheiro %s\n"   
#define ERR_VAZIA_LIST_TAB_SS "Sem tabelas para listar.\n"    
#define ERR_EXISTE_CRIT "Ja existe este criterio na tabela!\n"
#define ERR_FILE_SS "Tipo de ficheiro invalido(.bin)!"
#define VAL_INV "Informação inserida invalida!\n"

    //Contantes
#define MAX_STRING_SS 50
#define MIN_TIPO 1
#define MAX_TIPO 3
#define MIN_PORC_TAB_SS 0
#define MAX_PORC_TAB_SS 100
#define MIN_LINHA_SEGSOC 1
#define MIN_DEP_TAB_SS 0
#define MAX_DEP_TAB_SS 100 
#define MIN_ANOSSERVICO 1
#define MAX_ANOSSERVICO 60
#define MIN_ESTADOCIVIL 1
#define MAX_ESTADOCIVIL 4

    /**
     * Estrutura referente ao cargo geral de cada linha
     */
    typedef struct {
        Bool ativo; //Boolean a dizer se o criterio de cargo geral está ativo
        Cargo cargo; //Cargo geral
    } CargoSS;

    /**
     * Estrutura referente a informação de cada linha da segurança social
     */
    typedef struct {
        CargoSS tipo; //Cargo geral
        char funcao[MAX_STRING]; //Função especifica
        float entempregadora; //Taxa da entidade empregadora
        float trabalhador; //Taxa do Trabalhador
        float total; //Taxa Total
    } Linha_segsoc;

    /**
     * Estrutura referente a informação da tabela da segurança social com as variaveis de o tamanho alocado na memoria para as linhas 
     * e o contador desse tamanho alocado e o apontador das linhas que estão na memoria dinamica 
     */
    typedef struct {
        int cont; //Contador de memoria dinamica das linhas da Tabela da Segurança Social com informação
        int tam; //Tamanho alocado na memoria dinamica para as linhas da Tabela da Segurança Social
        Linha_segsoc *linha; //Apontador para a memoria dinamica das linhas da Tabela da Segurança Social
    } Tab_SS;

    /**
     * Esta função serve para a verificação do estado do cargo e se ele já existe
     * 
     * @param segsoc recebe como argumento uma variavel da estrutura Tab_SS
     * @param nlinha recebe um inteiro
     * @param cont recebe um inteiro
     * @return dá return de um inteiro com significado de um boolean
     */
    int ver_criterio(Tab_SS segsoc, int nlinha, int cont);
    /**
     * Esta função tem como finalidade apagar valores de uma linha especifica da struct Tab_SS
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     */
    void SegSoc_remove(Tab_SS *segsoc);
    /**
     * Esta função tem como objetivo alocar mais espaço na memória dinamica para as variáveis da struct Tab_SS
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     */
    void expandir_SegSoc(Tab_SS *segsoc);
    /**
     * Esta função tem como objetivo adicionar variáveis para a memória dinamica para a struct Tab_SS
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     */
    void SegSoc_add(Tab_SS *segsoc);
    /**
     * Esta função tem o propósito de carregar de uma ficheiro em .bin para memória dinámica os valores de uma tabela de Segurança Social Tab_SS
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     * @param file recebe como argumento um array de caracteres
     * @return dá return de um inteiro com significado de um boolean
     */
    int carregar_SegSoc(Tab_SS *segsoc, char *file);
    /**
     * Esta função tem como finalidade guardar o valor das variáveis para um ficheiro (.bin)
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     * @param file recebe como argumento um array de caracteres
     */
    void guardar_SegSoc(Tab_SS *segsoc, char *file);
    /**
     * Esta função serve para imprimir no ecra os valores da tabela da struct de Tab_SS
     * 
     * @param segsoc recebe como argumento uma variavel da estrutura Tab_SS
     */
    void SegSoc_list(Tab_SS segsoc);
    /**
     * Esta função tem como objetivo editar os valores apontados  da struct Tab_SS
     * 
     * @param segsoc recebe como argumento um apontador da struct Tab_SS
     */
    void SegSoc_edit(Tab_SS *segsoc);

#ifdef __cplusplus
}
#endif

#endif /* SEGSOC_H */

