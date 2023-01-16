/**
 * @file ficheiros.h
 * Projeto de LP - G51
 * @author André Eiras nº 8200587 1-C LSIRC 
 * @author José Francisco nº 8200472 1-C LEI 
 * @brief Este modulo contem todas as funções relativas a manipulação de ficheiros geral
 */
#ifndef FICHEIROS_H
#define FICHEIROS_H

#ifdef __cplusplus
extern "C" {
#endif
#define FILE_TYPE_CSV ".csv"
#define FILE_TYPE_BIN ".bin"
#define MSG_LER_FILE "Insira o destino e nome do Ficheiro onde deseja carregar(Completo/Parcial):"
#define MSG_GRAV_FILE "Insira o destino e nome do Ficheiro onde deseja gravar(Completo/Parcial):"
/**
 * Conta as linhas de um ficheiro ou seja sempre que encontra um enter ele aumenta o contador
 * 
 * @param file recebe o array de carateres do ficheiro
 * @return Retorna o contador que é numero de linhas do ficheiro
 */
int conta_linhas(char *file);
//int ver_tipo_ficheiro(char *file);


#ifdef __cplusplus
}
#endif

#endif /* FICHEIROS_H */

