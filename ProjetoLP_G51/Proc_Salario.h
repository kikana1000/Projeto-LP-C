/**
 * @file Proc_Salario.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Este modulo contem todas as funções relativas ao processamento de salario
 */


#ifndef PROC_SALARIO_H
#define PROC_SALARIO_H

#ifdef __cplusplus
extern "C" {
#endif


    //Mensagens Gerais
#define MSG_OBT_VALOR_BONUS_PS "Insira a porcentagem de bónus :"
#define MSG_REMOV_PS "Linha removida com sucesso.\n"
#define MSG_TAB_GUARDAR_PS "Tabela guardada com sucesso.\n"
#define MSG_CARR_PS "Tabela de salário bónus carregada com sucesso.\n"
#define MSG_CRIADO_PS "Linha adicionada à tabela de processamento de salário bónus.\n"
#define MSG_TABS_BONUS_ADD "Selecionada a opção de adicionar critérios para o processamento de bónus.\n"
#define MSG_OBT_SN_DEP "Deseja que o criterio seja aplicado a idade do funcionario(S/N)?"
#define MSG_OBT_SN_ANOSSERVICO "Deseja que o criterio seja aplicado acima um nº de anos de serviço(S/N)?"
#define MSG_OBT_SN_BONUS "Deseja fazer o calculo do mês com a tabela do bonus(S/N)?"
#define MSG_OBT_VALOR_DEP "Insira acima de que idade a que se aplica o criterio:"
#define MSG_OBT_VALOR_ANOSSERVICO "Insira o número de anos de serviço:"
#define MSG_OBT_VALOR_DIASFALTAS "Insira o número de dias de faltas:"
#define MSG_OBT_VALOR_ESTADOCIVIL "Insira o estado civil(1-Solteiro | 2- Casado | 3- Viúvo ):"
#define MSG_OBT_SN_DIASFALTAS "Deseja que o criterio seja aplicado abaixo um nº de dias de faltas(S/N)?"
#define MSG_EDIT_ESTADOCIVIL "Deseja editar o estado civil que se aplica o critério(S/N)?"
#define MSG_EDIT_ANOSSERVICO "Deseja editar a quantidade de anos de serviço à empresa que se aplica o critério(S/N)?"
#define MSG_REMOV_TAB_PS "Linha removida com sucesso.\n"
#define MSG_OBT_NLINHA_PS "Insira o número da linha que deseja remover:"
#define MSG_OBT_NLINHA_EDIT_PS "Insira o número da linha que deseja editar:"
#define MSG_EDIT_DEP_TAB_PS "Deseja editar o número de dependentes(S/N)?"
#define MSG_LINHA_ADICIONADA_PS "A linha foi adicionada\n"
#define MSG_LISTAR "Deseja listar os valores calculados relativamente a?\nEscolha uma das opções:\n1.Ano\n2.Mês\n3.Funcionario/ano\n0.Voltar ao menu anterior\n"
#define MSG_OBTER_DATA "Insira o ano e o mês do ficheiro que deseja calcular:\n"
#define MSG_OBTER_DATA_LISTAR "Insira o ano e o mês que deseja listar:\n"
#define MSG_OBTER_MES "Mês:"
#define MSG_OBTER_ONLY_ANO "Insira o ano que deseja listar:\n"
#define MSG_GUARDAR_MES "Insira o mês e o ano que deseja guardar em ficheiro!\n"
#define MSG_ANO_DESPES "Insira o ano que deseja guardar em ficheiro as depesas:\n"    
#define MSG_OBTER_ANO "Ano:"
#define MSG_MES_EXISTE "O mês ja existe na memoria,deseja apaga-lo(S/N)?"
#define MSG_SN_APG_FILE "Deseja apagar a informação no ficheiro(S/N)?"
#define MSG_LER_FILE_PROC "Insira o destino do Ficheiro dos dias trabalhados do funcionario onde deseja carregar(Completo/Parcial):"
#define MSG_FUNC_MES_FILE "Insira o destinho do ficheiro .csv:\n"
#define MSG_INFO_FUNC "%d Funcionarios carregado com informação ao mes de trabalho de %d/%d\n"
#define MSG_OBT_COD_LIST "Insira o codigo do funcionario que deseja listar:"
    
    //Mensagens de Erro
#define MSG_N_CARR_PS "Erro ao carregar tabela de salário bónus.\n"
#define VAL_INV_PS "Valor inserido inválido ou fora de limites.\n"    
#define INV_DATA_MES "Mês invalido.\n"
#define INV_DATA_ANO "Ano invalido.\n"    
#define ERR_VAZIA_GUARDAR_PS "Sem tabelas para Guardar em ficheiro.\n"    
#define ERR_FILE_N_EXISTE_BONUS "Erro ao carregar tabela de salário bónus(não existe).\n"    
#define ERR_VAZIA_LISTA_PS "Tabela vazia. \n"   
#define ERR_VAZIA_LISTA_BONUS "Tabela de bonus vazia. \n"   
#define ERR_TAB_SS "Em falta a tabela da Segurança Social!\n"
#define ERR_FUNC "Em falta a informação dos funcionarios!\n"
#define ERR_FUNC_N_ATIV "Impossivel calcular o funcionario %d pois ele não está ativo\n"
#define ERR_CRIT_EXIST "Já existe uma linha com estes criterios!\n"
#define ERR_FUNC_N_MEM "Impossivel calcular o funcionario %d pois não tem informação sobre ele!\n"
#define ERR_FILE_N_GRAV_PS "Nao conseguiu gravar a informação no ficheiro %s\n"
#define ERR_N_TAB_SS "Em falta a tabela da segurança social!\n"
#define ERR_N_TAB_IRS_SOLT "Em falta a tabela de irs de solteiro!"
#define ERR_N_TAB_IRS_CAS_1 "Em falta a tabela de irs de casado 1 titular!"
#define ERR_N_TAB_IRS_CAS_2 "Em falta a tabela de irs de casado 2 titulares!"
#define ERR_N_FUNCS "Em falta a tabela da segurança social!\n"
#define ERR_N_TAB_SS "Em falta a tabela da segurança social!\n"  
#define ERR_LISTAR_MES "Não existe informação na memoria sobre o mês %d do ano %d!\n"
#define ERR_MESES_EXIST "Apenas existe %d meses na memoria!\n"
#define ERR_MESES_FUNC_EXIST "Apenas existe informação de %d meses sobre o funcionario %d no ano %d na memoria!\n"
#define ERR_ANO_N_EXISTE "Não existe informação na memoria sobre o ano %d!\n"
#define ERR_FUNC_S_SAL_ANO "Não existe informação sobre o funcionario %d no ano %d\n"
#define ERR_MESES_0 "Nao existe meses para guardar em ficheiro!\n"
#define ERR_FILE_N_CARR_PS "Erro ao carregar a tabela das informações mensais dos funcionários do ficheiro %s (Sem funcionarios).\n"
#define ERR_FILE_N_EXISTE_PS "Ficheiro %s não existe.\n"   
#define OPC_INV_PS "Número de opção fora de limite.\n"

    //Constantes
#define MAX_FILE 100    
#define CHAR_SAIR 'S'
#define MIN_BONUS_PS 1
#define MAX_BONUS_PS 100
#define MIN_DEP_PS 18
#define MAX_DEP_PS 120
#define MIN_ANOSSERVICO_PS 1
#define MAX_ANOSSERVICO_PS 60
#define MIN_ESTADOCIVIL_PS 1
#define MAX_ESTADOCIVIL_PS 3
#define MIN_LINHA_PS 1
#define VAL_MIN_OPC_PS 0
#define VAL_MAX_OPC_PS 9
#define MIN_DIAS_FALTAS 0
#define MAX_DIAS_FALTAS 30
#define MIN_ANO_PS 1900
#define MIN_MES_PS 1
#define MAX_MES_PS 12
#define MAX_DIASTRABALHO 30
#define HORAS_DIACOMP 8
#define HORAS_MEIODIAS 4
#define PORC_EXTRA_FIMSEMANA 1.50

#include "funcionarios.h"
#include "Tabelas_IRS.h"
#include "SegSoc.h"

    /**
     * Estrutura referente a cada linha da Tabela de bonus
     */
    typedef struct {
        int idade; //A que idade (Maior) se aplica o bonus da linha
        int anosservico; //A que anos de serviço (Maior) se aplica o bonus da linha
        int diasfaltas; // A que dias de faltas se aplica o bonus da linha
        float bonus; //Bonus da linha
    } Linha_bonus;

    /**
     * Estrutura da Tabela de bonus com as variaveis de o tamanho alocado na memoria para as linhas da tabela
     * e o contador de linhas ocupadas com informação desse tamanho alocado e o apontador da a memoria dinamica para as linhas
     */
    typedef struct {
        int cont; //Contador de linhas da Tabela de bonus na memoria dinamica com informação
        int tam; //Tamanho alocado para as linhas da Tabela de bonus na memoria dinamica
        Linha_bonus *linha; //Apontador para as linhas da tabela de bonus
    } Tab_Bonus;

    /**
     * Estrutura dos valores que a empresa gastou no funcionario
     */
    typedef struct {
        float valor_segsoc_empresa, valor_total;
    } Empresa_func;

    /**
     * Estrutura dos valores relativos ao funcionario
     */
    typedef struct {
        float valor_sub_alimentacao, valor_hora, valor_bruto, valor_liquido, valor_bonus, valor_irs_funcionario, valor_segsoc_funcionario;
    } Funcionario_val;

    /**
     * Estrutura com a informação relativa ao salario/trabalho do funcionario do mês
     */
    typedef struct {
        int cod; //Codigo
        int dias_comp, dias_meio, dias_fimsemana, dias_faltas; //Dias referentes ao mês de trabalho
        int calculado; //Inteiro com significado boolean a dizer se o funcionario foi calculado ou não
        Funcionario_val func; //Estrutura dos valores referentes ao funcionario
        Empresa_func emp; //Estrutura dos valores referentes a empresa
    } Info_funcionario_mes;

    /**
     * Estrutura com a informação relativa ao que a empresa gastou no mes
     */
    typedef struct {
        float valor_bruto_total;
        float valor_segsoc_total;
        float valor_bonus_total;
        float valor_sub_total;
        float valor_total;
    } Empresa_mes;

    /**
     * Estrutura com a informação relativa ao mês
     */
    typedef struct {
        int mes; //Mes
        int ano; //Ano
        int cont; //Contador referente a quantidade de funcionarios na memoria dinamica com a informação do mês de trabalho
        int tam; //Tamanho Alocado de funcionarios na memoria dinamica 
        Empresa_mes emp_mes; //Estrutura de Valores relativos a que gastou a empresa no mes
        Info_funcionario_mes *funcionario; //Apontador para a informação dos funcionarios nesse mês
    } MES;

    /**
     * Estrutura com a informação relativa de todos os meses
     */
    typedef struct {
        int cont; //Contador referente a quantidade de meses com informação na memoria dinamica 
        int tam; //Tamanho Alocado de meses na memoria dinamica
        MES *mes; //Apontador para os meses na memoria dinamica
    } MESES_TOTAL;
    
    /**
     * Lista o maior bonus na memoria que cada funcionario na memoria pode ter direito
     * 
     * @param funcs Recebe a variavel dos funcionarios
     * @param tab Recebe a variavel da tabela bonus
     */
    void listar_func_bonus(Funcs funcs, Tab_Bonus tab);
    /**
     * Esta função tem como objetivo declarar os tipos de criterios na linha especifica apontada na struct Linha_Bonus
     * 
     * @param linha Recebe como argumento um apontador da struct Linha_Bonus
     */
    void pergs_criterio(Linha_bonus *linha);
    /**
     * Calcula as despesas que a empresa obteve nesse mes para esse funcionario
     * 
     * @param mes_total Recebe como argumento um apontador de toda a informação dos meses
     * @param mes Recebe como argumento um int referente ao mes do calculo
     * @param func Recebe como argumento um int referente ao funcionario do calculo
     */
    void calcular_depesas_emp(MESES_TOTAL *mes_total, int mes, int func);
    /**
     * Esta função verifica o tipo de caracter e compara com o valor do ficheiro e da return de um inteiro com valor boolean
     * 
     * @param file Recebe como argumento um array de caracteres
     * @param letra Recebe como argumento um char
     * @return de um inteiro com valor de boolean
     */
    int ver_char(char *file, char letra);
    /**
     * Esta função carrega do ficheiro file as informações do mês de trabalho de cada funcionario nele
     * 
     * @param Tabs Recebe como argumento um apontador para a informação relativa de cada mês
     * @param file Recebe como argumento um array de carateres
     * @return um int que diz a quantidade e funcinarios que foram carregados do ficheiro
     */
    int carregar_tab_Funcionario_Mes(MES *Tabs, char *file);
    /**
     * Esta função verifica o numero do ano e e compara com o valor do ficheiro e da return de um inteiro com valor boolean
     * 
     * @param meses_total Recebe como argumento uma variavel da struct MESES_TOTAL
     * @param ano Recebe como argumento um inteiro
     * @return de um inteiro com valor de boolean
     */
    int ver_ano_meses(MESES_TOTAL meses_total, int ano);
    /**
     * Esta função tem como objetivo verificar se algum critério é igual aos valores já implementados da struct Tab_Bonus
     * 
     * @param tabela Recebe como argumento uma variavel da struct Tab_Bonus
     * @param nlinha um valor inteiro
     * @return de um valor inteiro
     */
    int ver_criterio_bonus(Tab_Bonus tabela, int nlinha);
    /**
     * Esta função tem o objetivo de editar os valores de uma linha especifica da struct Tab_Bonus
     * 
     * @param tabs Recebe como argumento um apontador da struct Tab_Bonus
     */
    void Proc_Salario_edit_Bonus(Tab_Bonus *tabs);
    /**
     * Esta função tem como proposito remover uma linha especifica da memoria dinamica da struct Tab_Bonus
     * 
     * @param tabs Recebe como argumento um apontador da stuct Tab_Bonus
     */
    void Proc_Salario_remove_Bonus(Tab_Bonus *tabs);
    /**
     * Esta função tem como proposito guardar os dados para um ficheiro .csv
     * 
     * @param tabs Recebe como argumento uma variavel da struct Tab_Bonus
     * @param file Recebe como argumento um array de caracteres
     */
    void guardar_Proc_Salario_Bonus(Tab_Bonus tabs, char *file);
    /**
     * Esta função tem o proposito de carregar para memória dinamica os valores de um ficheiro .csv
     * 
     * @param tabs Recebe como argumento um apontador da struct Tab_Bonus
     * @param file Recebe como argumento um array de caracteres
     * @return dá return de um inteiro com significado de um boolean
     */
    int carregar_Proc_Salario_Bonus(Tab_Bonus *tabs, char *file);
    /**
     * Esta função tem como objetivo acrescentar valores na memoria dinamica da struct da tabela Tab_Bonus
     * 
     * @param tabs Recebe como argumento um apontador da struct Tab_Bonus
     */
    void Proc_Salario_Bonus_add(Tab_Bonus *tabs);
    /**
     * Esta função tem como objetivo alocar mais espaço na memória dinamica para as variáveis da struct Tab_Bonus
     * 
     * @param tabs Recebe como argumento um apontador da struct Tab_Bonus
     */
    void expandir_Proc_Salario_Bonus(Tab_Bonus *tabs);
    /**
     * Esta função tem como objetivo imprimir no ecra as tabelas Tab_Bonus
     * @param tabs Recebe como argumento uma variavel da struct Tab_Bonus
     */
    void Proc_Salario_Bonus_list(Tab_Bonus tabs);
    /**
     * Esta função tem como objetivo alocar mais espaço na memória dinamica para as variáveis da struct MESES_TOTAL
     * 
     * @param mes_total Recebe como argumento um apontador da struct MESES_TOTAL
     */
    void expandir_meses(MESES_TOTAL *mes_total);
    /**
     * Esta função verifica o numero do mes e e compara com o valor do ficheiro e da return de um inteiro com valor boolean
     * 
     * @param meses_total Recebe como argumento uma variavel da struct MESES_TOTAL
     * @param ano Recebe um valor inteiro
     * @param mes Recebe um valor inteiro
     * @return de um inteiro com valor de boolean
     */
    int ver_mes(MESES_TOTAL meses_total, int ano, int mes);
    /**
     *  Esta função tem como objetivo o carregamento de varios valores de varios ficheiros para carregamento 
     *   para memoria dinamica de varias structs seguida do calculo de salario com as taxas e valores anteriormente acedidos
     * 
     * @param func_info Recebe como argumento um apontador da struct Funcs
     * @param tab_irs Recebe como argumento um apontador da struct Tab_IRS
     * @param tab_ss Recebe como argumento um apontador da struct Tab_SS
     * @param tab_Bonus Recebe como argumento um apontador da struct Tab_Bonus
     * @param mes_total Recebe como argumento um apontador da struct MESES_TOTAL
     */
    void calculo_salario(Funcs *func_info, Tab_IRS *tab_irs, Tab_SS *tab_ss, Tab_Bonus *tab_Bonus, MESES_TOTAL *mes_total);
    /**
     * Esta função tem como objetivo o calculo das taxas de IRS a aplicar ao salario bruto de um funcionario
     * 
     * @param funcionario Recebe como argumento um apontador da struct Info_funcionario_mes
     * @param func Recebe como argumento uma variavel da struct Func
     * @param tabela Recebe como argumento um apontador da struct Tab_IRS
     */
    void calcular_Salario_Tabela_IRS(Info_funcionario_mes *funcionario, Func func, Tab_IRS *tabela);
    /**
     * Esta função tem como proposito o calculo das taxas da Segurança Social a serem aplicadas ao salario bruto de um funcionario
     * 
     * @param funcionario Recebe como argumento um apontador da struct Info_funcionario_mes
     * @param func Recebe como argumento uma variavel da struct Func
     * @param tabela Recebe como um argumento uma variavel da struct Tab_SS
     */
    void calcular_Salario_Tabela_SegSoc(Info_funcionario_mes *funcionario, Func func, Tab_SS tabela);
    /**
     * Esta função tem como objetivo o calculo do salario bruto de um funcionario
     * 
     * @param func_info Recebe como argumento uma variavel da struct Func 
     * @param func Recebe um apontador da struct Info_funcionario_mes
     */
    void calculo_bruto(Func func_info, Info_funcionario_mes *func);
    /**
     * Esta função tem como objetivo o calculo do valor bonus a ser atribuido ao funcionario
     * 
     * @param funcionario Recebe como arguemento um apontador da struct Info_funcionario_mes
     * @param func Recebe uma variavel da struct Func
     * @param tabela Recebe uma variavel da struct Tab_Bomnus
     */
    void calcular_Salario_Bonus(Info_funcionario_mes *funcionario, Func func, Tab_Bonus tabela);
    /**
     * Esta função é o menu de listar os dados dos meses calculados
     * @param mes_total Recebe como argumento uma variavel da struct MESES_TOTAL
     */
    void menu_Listar_ano_mes(MESES_TOTAL mes_total);
    /**
     * Esta função tem o proposito de carregar para memoria dinamica de o ficheiro file os salarios anteriormente calculados
     * 
     * @param mestotal Recebe um argumento do tipo apontador da struct MESES_TOTAL
     * @param file Recebe como argumento um array de caracteres
     */
    void carregar_Salario_Calculado(MESES_TOTAL *mestotal, char *file);
    /**
     * Esta função tem o objetivo de carregar para um ficheiro .csv os salarios calculados relativo a um mês em memoria dinamica
     * 
     * @param mestotal Recebe como argumento um apontador da struct MESES_TOTAL
     * @param file Recebe como argumento um array de caracteres
     */
    void guardar_Salario_Calculado(MESES_TOTAL *mestotal, char *file);
    /**
     * Esta função tem como objetivo listar o valor de cada ano já calculado
     * 
     * @param meses_total Recebe como argumento uma variavel da struct MESES_TOTAL
     */
    void Listar_ano_comp(MESES_TOTAL meses_total);
    /**
     * Esta função tem como objetivo de listar os meses já calculados
     * 
     * @param meses_total Recebe como argumento uma variavel da struct MESES_TOTAL
     */
    void Listar_mes(MESES_TOTAL meses_total);
    /**
     * Guarda as despesas do ano da empresa no ficheiro 
     * 
     * @param mestotal Recebe como argumento a variavel mestotal com a informação toda de cada mes
     * @param file Recebe como argumento um array de characteres referente ao ficheiro
     */
    void guardar_ficheiro_Despesas_ano(MESES_TOTAL mestotal, char *file);
    /**
     * Procura o cod funcionario num ano espefico de todos meses calculados e retorna a quantidade de meses calculados que ele aparece nesse mes
     * 
     * @param mes Recebe como argumento uma variavel a estrutura MESES_TOTAL 
     * @param ano Recebe como argumento um inteiro relativo ao ano
     * @param cod Recebe como argumento um inteiro relativo ao codigo do funcionario
     * @return Retorna um int que se referem a quantidade de meses
     */
    int ver_func_ano(MESES_TOTAL mes, int ano, int cod);
    /**
     * Procura o cod funcionario num ano e mes especifico de todos meses calculados e retorna o indice do funcionario
     * 
     * @param mes Recebe como argumento uma variavel a estrutura MESES_TOTAL 
     * @param ano Recebe como argumento um inteiro relativo ao ano
     * @param cod Recebe como argumento um inteiro relativo ao codigo do funcionario
     * @return Retorna um int que se refere ao indice do funcionario no mes e no ano especifico
     */
    int ver_func_ano_mes(MESES_TOTAL mesestotal, int ano, int cod, int mes);
    /**
     * Lista todos os meses calculados de um funcionario num certo mes
     * 
     * @param mestotal Recebe como argumento uma variavel a estrutura MESES_TOTAL
     */
    void Listar_funcionario_ano(MESES_TOTAL mestotal);

#ifdef __cplusplus
}
#endif

#endif /* PROC_SALARIO_H */
