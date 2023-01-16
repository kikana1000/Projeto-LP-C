/**
 * @file funcionarios.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Este modulo contem todas as funções relativas aos funcionarios
 */


#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H


#ifdef __cplusplus
extern "C" {
#endif

    //Mensagens Gerais
#define MSG_CALC_AUTO_NASC "Deseja inserir a data atual na data de entrada(S/N)?\n"
#define MSG_CALC_AUTO_SAIDA "Deseja inserir a data atual na data de Saida(S/N)?\n"
#define MSG_FUNC_ADD "Opção de adicionar Funcionario escolhida.\n"
#define MSG_FUNC_EDIT "Opção de editar Funcionario escolhida.\n"
#define MSG_FUNC_REMOVE "Opção de remover Funcionario escolhida.\n"  
#define MSG_CRIADO "Funcionario foi criado.\n"
#define MSG_REMOV "Funcionario foi removido.\n"
#define MSG_EDIT "Funcionario foi editado.\n"
#define MSG_LIST "Funcionarios foram todos listados.\n"
#define MSG_FUNC_CARR "Funcionarios Carregados do Ficheiro %s.\n"
#define MSG_FUNC_GRAV "Funcionarios guardado no Ficheiro %s.\n"
#define MSG_OBT_NOME "Insira o Nome do funcionario:"
#define MSG_OBT_COD "Insira o codigo do funcionario(MAX 4 NUM):"
#define MSG_OBT_REM_COD "Insira o codigo do funcionario que deseja remover(MAX 4 NUM):"
#define MSG_OBT_EDIT_COD "Insira o codigo do funcionario que deseja editar(MAX 4 NUM):"
#define MSG_OBT_TEL "Insira o telemovel do funcionario(MAX 9 NUM):"
#define MSG_OBT_DATA_ENTR "Insira a data de entrada do Funcionario:\n"
#define MSG_OBT_DATA_SAIDA "Insira a data de saida do Funcionario:\n"
#define MSG_OBT_DATA_NASC "Insira a data de nascimento do Funcionario:\n"
#define MSG_OBT_DATA_DIA "->Dia(1-31):"
#define MSG_OBT_DATA_MES "->Mes(1-12):"
#define MSG_OBT_DATA_ANO "->Ano:"
#define MSG_OBT_DEP "Insira o numero de dependentes do funcionario:"
#define MSG_OBT_CARGO "Insira o cargo do funcionario na sua funcao(1-Chefe/2-Administrador/3-Funcionario):"
#define MSG_OBT_FUNCAO "Insira a funcao do funcionario:"
#define MSG_OBT_ESTCIVIL "Insira o estado civil do funcionario(1-Solteiro/2-Casado/3-Viuvo):"
#define MSG_FUNC_LIST "Opção de listar Funcionarios escolhida.\n"
#define MSG_OBT_VALOR_HORA "Insira o valor que o funcionario irá receber a hora:"
#define MSG_OBT_VALOR_SUB "Insira o valor que o funcionario irá receber de subsidio:"
#define MSG_EDIT_COD "Deseja editar o codigo do funcionario(S/N)?"
#define MSG_EDIT_NOME "Deseja editar o Nome do funcionario(S/N)?"
#define MSG_EDIT_DATA_NASC "Deseja editar a data de nascimento do funcionario(S/N)?"
#define MSG_EDIT_DATA_ENTR "Deseja editar a data de entrada do funcionario(S/N)?"
#define MSG_EDIT_TEL "Deseja editar o numero de telemovel do funcionario(S/N)?"
#define MSG_EDIT_DEP "Deseja editar o numero de dependentes do funcionario(S/N)?"
#define MSG_EDIT_VAL_HORA "Deseja editar quanto o funcionario recebe por hora(S/N)?"
#define MSG_EDIT_VAL_SUB "Deseja editar quanto o funcionario recebe do subsidio de alimentação(S/N)?"
#define MSG_EDIT_CARGO "Deseja editar o cargo na sua função do funcionario(S/N)?"
#define MSG_EDIT_FUNCAO "Deseja editar a funcao do funcionario(S/N)?"
#define MSG_EDIT_ESTCIV "Deseja editar o estado civil do funcionario(S/N)?"
#define MSG_EDIT_ATIVO "O funcionario ainda está ativo(S/N)?"
#define PERG_ESTCIV_TITULAR "Apenas este funcionario trabalha no casamento(S/N)? "
#define MSG_EDIT_ATIVO_DATA "Insira a data de saida do funcionario:\n"

    //Mensagens de Erro   
#define MSG_FUNC_N_CARR "Ficheiro %s sem funcionarios.\n"    
#define MSG_PERG_FUNC_GUARDAR "Deseja Guardar os funcionarios em ficheiro(S/N)?"
#define ERR_FILE_FUNC "Tipo de ficheiro invalido(.csv/.txt/.bin)!"
#define ERR_CALC_IDADE "A data de nascimento do funcionario %d está incorreta\n"
#define ERR_CALC_ANOS_SERVIÇO "A data de nascimento do funcionario %d está incorreta\n"
#define ERR_VAZIA_LIST "Sem funcionarios para listar.\n"
#define ERR_VAZIA_GUARDAR "Sem funcionarios para guardar no ficheiro %s.\n"
#define ERR_EXISTE "Funcionario já existe.\n"
#define ERR_N_EXISTE "Funcionario não existe.\n"
#define ERR_FILE_FUNC_N_EXISTE "O ficheiro %s nao existe\n"
#define ERR_REMOV "Funcionario ja foi removido.\n"
#define ERR_DATA_ENTR "Idade Insuficiente\n"
#define ERR_DATA_SAIDA "A data de entrada tem de ser menor que a data de saida\n"
#define VAL_INV "Informação inserida invalida!\n"   

    //Constantes
#define MAX_CARG 3
#define MIN_CARG 1
#define MAX_ESTCIV 3
#define MIN_ESTCIV 1
#define MIN_DEP 0
#define MAX_DEP 20
#define MAX_COD 9999
#define MIN_COD 0
#define MIN_TEL 900000000
#define MAX_TEL 999999999
#define MAX_STRING 100
#define MIN_ANO 1900
#define MAX_ANO 2021
#define MIN_MES 1
#define MAX_MES 12
#define MIN_DIA 0
#define MAX_DIA 31
#define MAX_VAL 99999
#define MIN_VAL 0
#define IDADE_MINIMA 15

    /**
     * Enumeração relativa aos cargos gerais
     */
    typedef enum {
        Chefe = 1, Administrador = 2, Funcionario = 3
    } Cargo;

    /**
     * Enumeração de bool
     */
    typedef enum bool {
        Nao_ativo, Ativo
    } Bool;

    /**
     * Enumeração relativa ao estado civil do funcionario
     */
    typedef enum estciv {
        Solteiro = 1, Casado_1 = 2, Viuvo = 3, Casado_2 = 4
    } Est_civil;
    /**
     * Estrutura de data com o dia, mes e ano
     */
    typedef struct {
        int dia, mes, ano;
    } Data;

    /**
     * Estrutura com a informação referente a cada funcionario
     */
    typedef struct {
        int cod; //Codigo
        Bool del; //Boolean de ativo/nao ativo
        Data data_nasc, data_entr, data_saida; //Datas
        float anos_servico; //Anos de serviço
        float idade; //Idade
        char nome[MAX_STRING]; //Nome
        int tel; //Numero de telemovel
        int dep; //Numero de dependentes
        float val_hor, val_sub; //Valores associadas ao salario
        Cargo cargo; //Cargo geral
        char funcao[MAX_STRING]; //Função especifica
        Est_civil est_civil; //Estado Civil
    } Func;
    /**
     * Estrutura com a quantidade de funcionarios com informação na memoria dinamica
     * e o tamanho alocado para os funcinarios e um apontador para a memoria dinamica com 
     * toda a informação de cada funcionario.
     */
    typedef struct {
        Func *func; //Apontador para a memoria dinamica com a informação de cada funcionario
        int cont; //Contador de funcionarios na memoria dinamica com informação
        int tam; //Tamanho alocado de memoria dinamica
    } Funcs;
    

    
    /**
     * Esta função tem como objetivo o calculo da idade do funcionario e dos anos de servico em anos/meses/dias
     * 
     * @param func recebe como argumento um apontador da struct de Func
     */
    void calcular_idades(Func *funcs);
    /**
     * Esta função tem como objetivo alocar mais memoria dinamica para as variaveis da struct Funcs
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     */
    void expandir_Funcs(Funcs *funcs);
    /**
     * Esta função tem como objetivo listar no monitor os funcionarios existentes e todas as suas propriedades
     * 
     * @param funcs recebe como argumento uma variavel da struct Funcs
     */
    void func_list(Funcs funcs);
    /**
     * Esta função tem como objetivo listar no ecra todos os funcionarios ativos existentes e as suas propriedades
     * 
     * @param funcs recebe como argumento uma variavel da struct Funcs
     */
    void func_list_ativo(Funcs funcs);
    /**
     * Esta função tem como proposito listar no ecra todos os funcionarios não ativos no ecra e todas as suas propriedades
     * 
     * @param funcs recebe como argumento uma variavel da struct Funcs
     */
    void func_list_n_ativo(Funcs funcs);
    /**
     * Esta função tem como objetivo a edição de um funcionario especifico alocado em memoria dinamica 
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     */
    void func_edit(Funcs *funcs);
    /**
     * Esta função tem como objetivo Adicionar um funcionario na memoria dinamica
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     */
    void func_add(Funcs *funcs);
    /**
     * Esta função tem como objetivo eliminar um funcionario especifico da struct Funcs mudando certos valores de modo a este permanecer nos ficheiros mas como inativo
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     */
    void func_remove(Funcs *funcs);
    /**
     * Esta função tem como objetivo a pesquisa com o retorno do indice do funcionario requesitado
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     * @param cod recebe como argumento um inteiro
     * @return de um inteiro do indice ou de um valor com significa boolean
     */
    int func_search(Funcs *funcs, int cod);
    /**
     * Esta função tem como objetivo verificar se os dados do nº. de telemovel estão dentro dos parametros definidos
     * 
     * @param num recebe como argumento um inteiro
     * @param err recebe como argumento um array de caracteres
     * @return de um inteiro com o valor de boolean
     */
    int ver_tel(int num, char *err);
    /**
     * Esta função tem como objetivo fazer uma verificação de data dando return de um inteiro
     * 
     * @param data_menor recebe como argumento uma variavel da struct Data
     * @param data_maior recebe como argumento uma variavel da struct Data
     * @param anos_minimos recebe como argumento um inteiro
     * @param err recebe como argumento um array de caracteres
     * @return dá return de um inteiro com valor de boolean
     */
    int ver_data(Data data_menor, Data data_maior, int anos_minimos, char *err);
    /**
     * Esta função tem como proposito carregar para a memoria dinamica as informações dos funcionarios de um ficheiro (.bin)
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     * @param file recebe como argumento um array de caracteres
     * @return de um inteiro com valor de boolean
     */
    int carregar_Funcs(Funcs *funcs, char *file);
    /**
     * Esta função tem como objetivo gravar as informações dos funcionarios alocados em memoria dinamica para um ficheiro (.bin)
     * 
     * @param funcs recebe como argumento um apontador da struct Funcs
     * @param file recebe como argumento um array de caracteres
     */
    void guardar_Funcs(Funcs *funcs, char *file);

#ifdef __cplusplus
}
#endif

#endif /* FUNCIONARIOS_H */

