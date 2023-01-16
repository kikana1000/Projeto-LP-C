/**
 * @file input.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * 
 * @brief Este modulo contem todas as funções relativas a inserção de informação geral
 */



#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif
    //Mensagens de Erro
#define ERRO_RETURN "Tipo de informação incorreta,voltando ao menu anterior\n"
    
    /**
     * Esta função tem como objetivo limpar o buffer do input
     */
    void cleanInputBuffer();
    /**
     * Esta função tem como objetivo obter um valor do tipo int dentro dos limites pedidos nos argumentos desta função 
     *  devolvendo apenas se este se e só se estiver dentro dos limtes e nao permite a inserção de valores diferentes do tipo int (exemplo: do tipo Char)
     * 
     * 
     * @param minValor recebe como argumento um inteiro
     * @param maxValor recebe como argumento um inteiro
     * @param msg recebe como argumento um array de caracteres
     * @param err recebe como argumento um array de caracteres
     * @return valor inteiro
     */
    int obterInt(int minValor, int maxValor, char *msg, char *err);
    /**
     * Esta função tem como objetivo obter um valor do tipo float dentro dos limites pedidos nos argumentos desta função 
     * devolvendo apenas se este se e só se estiver dentro dos limites e nao permite a inserção de valores diferentes do tipo float (exemplo: do tipo Char)
     * 
     * @param minValor recebe como argumento um inteiro
     * @param maxValor recebe como argumento um inteiro
     * @param msg recebe como argumento um array de caracteres
     * @param err recebe como argumento um array de caracteres
     * @return valor do tipo float
     */
    float obterFloat(float minValor, float maxValor, char *msg, char *err);
    /**
     * Esta função tem como objetivo obter um valor do tipo int dentro dos limites pedidos nos argumentos desta função devolvendo apenas se este se 
     * e só se estiver dentro dos limites e que permite caso seja inserido um caracter devolva um inteiro negativo que pode permitir uma verificação para voltar atrás 
     * 
     * (Não é implementado em nenhuma parte do projeto)
     * 
     * @param minValor recebe como argumento um inteiro
     * @param maxValor recebe como argumento um inteiro
     * @param msg recebe como argumento um array de caracteres
     * @param err recebe como argumento um array de caracteres
     * @return valor inteiro
     */
    int obterInt_return(int minValor, int maxValor, char *msg, char *err);
    /**
     * Esta função tem como objetivo obter um valor do tipo float dentro dos limites pedidos nos argumentos desta função devolvendo apenas se este se 
     * e só se estiver dentro dos limites e que permite caso seja inserido um caracter devolva um inteiro negativo que pode permitir uma verificação para voltar atrás 
     * 
     * (Não é implementado em nenhuma parte do projeto)
     * 
     * @param minValor recebe como argumento um inteiro
     * @param maxValor recebe como argumento um inteiro
     * @param msg recebe como argumento um array de caracteres
     * @param err recebe como argumento um array de caracteres
     * @return valor do tipo float
     */
    float obterFloat_return(float minValor, float maxValor, char *msg, char *err);
    /**
     * Esta função tem como objetivo obter um valor do tipo double dentro dos limites pedidos nos argumentos desta função 
     * devolvendo apenas se este se e só se estiver dentro dos limites
     * 
     * (Não é utilizado no projeto)
     * 
     * @param minValor recebe como argumento um inteiro
     * @param maxValor recebe como argumento um inteiro
     * @param msg recebe como argumento um array de caracteres
     * @param err recebe como argumento um array de caracteres
     * @return valor do tipo double
     */
    double obterDouble(double minValor, double maxValor, char *msg, char *err);
    /**
     * Esta função tem como objetivo obter um valor 1 ou -1 dependente da resposta do utilizador
     * 
     * @param msg recebe um array de carateres como argumento
     * @return dá return de um inteiro com significado de um boolean
     */
    int perg_s_n(char *msg);
    /**
     * Este função tem como objetivo a leitura de uma string e retirar o enter do ultimo carater
     * 
     * @param string recebe como argumento um array de caracteres
     * @param tamanho recebe como argumento um valor do tipo unsigned int
     * @param msg recebe como argumento um array de caracteres
     */
    void lerString(char *string, unsigned int tamanho, char *msg);



#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */

