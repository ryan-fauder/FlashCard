#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

/**
 * @brief Funcao que imprime todas as opções do programa
 */
void help(void);

/**
 * @brief Funcao que imprime a tela inicial do programa
 */
void home(void);
/**
 * @brief funcao que cria a pasta data, caso nao exista
 * 
 */
void init(void);

/**
 * @brief funcao que joga com as cartas atrasadas
 * 
 */
void playall(void);

/**
 * @brief carta que joga com todas as cartas atrasadas de uma colecao
 * 
 * @param string nome da colecao
 */
void playonly(char * string);

/**
 * @brief joga com todas as cartas de uma colecao
 * 
 * @param string nome da colecao
 */
void play(char * string);

/**
 * @brief Cria uma carta em uma colecao e armazena em um arquivo
 * 
 * @param name_collection nome da colecao
 */
void create_card(char * name_collection);

/**
 * @brief Edita uma carta em uma colecao e atualiza o arquivo
 * 
 * @param str nome da colecao
 */
void edit_card(char * str);
/**
 * @brief Apaga uma carta de uma colecao e atualiza o arquivo
 * 
 * @param str nome da colecao
 */
void del_card(char * str);

/**
 * @brief realiza as operacoes de abrir o arquivo dentro da pasta data
 * 
 * @param str colecao a ser aberta
 * @param format formato que sera aberto
 * @return FILE* arquivo da colecao no formato especifico
 */
FILE * open_database(char * str, char * format);

/**
 * @brief verifica se um arquivo existe e esta de acordo com o padrao de arquivo
 * 
 * @param str arquivo a ser analisado
 * @return char retorna um boolean: 1 - arquivo valido; 0 - arquivo invalido
 */
char verifyFile(char * str);

/**
 * @brief Cria uma arquivo de colecao dado o nome da colecao
 * 
 * @param name nome da colecao a ser criada
 */
void create_collection(char * name);

/**
 * @brief visualiza todas as cartas de uma colecao
 * 
 * @param name nome da colecao
 */
void view_collection(char * name);

/**
 * @brief deleta o arquivo de uma colecao
 * 
 * @param name nome da colecao que sera deletada
 */
void delete_collection(char * name);
#endif