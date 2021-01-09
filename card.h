#ifndef __CARD_H__
#define __CARD_H__

#include <time.h>
typedef struct tm moment;

typedef struct{
	int id;
	char front[150];
	char back[150];
	moment * last_at;
	moment * cooldown;
} card;

/**
 * @brief Funcao para liberar um card da memoria alocada
 * 
 * @param c uma card
 */
void card_free(card * c);

/**
 * @brief funcao para criar uma carta e retornar-la
 * 
 * @param id id que sera armazenado na carta
 * @param front texto armazenado na parte frontal da carta
 * @param back texto armazenado na parte traseira da carta
 * @return card* a estrutura da carta e retornada
 */
card * card_create(int id, char front[150], char back[150]);
/**
 * @brief funcao para editar os textos contidos na carta
 * 
 * @param c carta que sera editada
 * @param front novo texto frontal
 * @param back novo texto traseiro
 */
void card_edit(card * c, char front[150], char back[150]);
/**
 * @brief funcao para visualizar uma carta
 * 
 * @param c carta a ser visualizada
 */
void card_view(card * c);
/**
 * @brief funcao que realiza a leitura de uma carta e recebe um id
 * 
 * @param id 
 * @return card* retorna a carta criada
 */
card * card_scanf(int id);
/**
 * @brief Funcao que permite jogar com uma carta
 * 
 * @param c a carta que sera jogada
 */
void play_card(card * c);
/**
 * @brief funcao que realiza a impressao de um struct tm em arquivo no padrao definido
 * 
 * @param m struct tm que sera impresso
 * @param f arquivo que recebera a impressao
 */
void moment_fprint(moment * m, FILE * f);
/**
 * @brief funcao que realiza a leitura de arquivo com o padrao tm e retorna em uma struct tm
 * 
 * @param f arquivo que contem o conteudo a ser armazenado
 * @return moment* struct tm com os valores do arquivo
 */
moment * moment_fscanf(FILE * f);
/**
 * @brief realiza a leitura de arquivo com o padrao card e retorna uma card
 * 
 * @param f arquivo que contem o conteudo a ser lido
 * @return card* carta com os valores do arquivo
 */
card * card_fread(FILE * f);
/**
 * @brief funcao que realiza a impressao de uma card em arquivo no padrao definido
 * 
 * @param m card que sera impressa
 * @param f arquivo que recebera a impressao
 */
void card_fprint(card * c, FILE * f);

/**
 * @brief Funcao fibonacci que procura o proximo numero
 * 
 * @param number o valor atual na funcao fibonacci
 * @return int o proximo numero da funcao fibonacci
 */
int fibbonacci(int number);
/**
 * @brief calcula o proximo cooldown da carta
 * 
 * @param c carta que tera o cooldown recalculado
 * @param boolean contem se o valor booleano em relacao ao acerto da carta
 */
void recalc_cooldown(card * c, int boolean);
/**
* @brief 
* return 0 - para caso não esteja em cooldown
* 1 - caso esteja em cooldown
*/
char verifyCooldown(card * c);
#endif