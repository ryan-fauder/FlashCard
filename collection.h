#ifndef __COLLECTION_H__
#define __COLLECTION_H__
typedef struct {
	int id;
	char name[50];
	card ** vector;
	int size;
} collection;
/**
 * @brief funcao que libera a memoria de uma collection struct
 * 
 * @param c colecao que sera liberada
 */
void collection_free(collection * c);
/**
 * @brief funcao que gera um id para um carta de acordo com a colecao
 * 
 * @param c colecao qeu sera analisada
 * @return int id gerado
 */
int generate_id(collection * c);

/**
 * @brief funcao que cria uma colecao
 * 
 * @param name nome da colecao
 * @param id identificacao da colecao
 * @return collection* colecao criada
 */
collection * collection_create(char name[50], int id);

/**
 * @brief funcao que edita uma carta da colecao
 * 
 * @param c colecao a ser editada
 * @param d a nova carta
 * @param index posicao da carta que sera substituida
 */
void collection_edit_card(collection * c, card * d, int index);

/**
 * @brief funcao para impressao no terminal de uma colecao
 * 
 * @param c colecao a ser impressa
 */
void collection_print(collection * c);

/**
 * @brief funcao para adotar uma carta nova no final de uma colecao
 * 
 * @param c colecao
 * @param d carta a ser adotada
 */
void collection_append(collection * c, card * d);
/**
 * @brief funcao que apaga uma carta da colecao
 * 
 * @param c coleoca
 * @param index posicao da carta que sera apagada
 */
void collection_del_card(collection * c, int index);
/**
 * @brief funcao que joga com uma colecao
 * 
 * @param c colecao a ser jogada
 */
void collection_play(collection * c);

/**
 * @brief funcao que realiza a impressao de uma colecao em um arquivo
 * 
 * @param c colecao a ser impressa
 * @param f arquivo a receber a impressao
 */
void collection_fprint(collection * c, FILE * f);
/**
 * @brief funcao que realiza a leitura de uma colecao em um arquivo
 * 
 * @param id identifcacao da colecao
 * @param name nome da colecao
 * @param f arquivo
 * @return collection* colecao criada atraves da leitura
 */
collection * collection_fread(int id, char name[50], FILE * f);
/**
 * @brief retorna uma colecao apenas com cartas atrasadas dada uma colecao
 * 
 * @param c colecao
 * @return collection* colecao com as cartas atrasadas 
 */
collection * collection_overdue(collection * c);
/**
 * @brief realiza o calculo das cartas atrasadas de uma colecao
 * 
 * @param c colecao
 * @return int total de cartas atrasadas
 */
int collection_count_overdue(collection * c);
#endif